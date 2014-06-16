#include <stdio.h>
#include <assert.h>
#include "../xvect.h"

void
test_rear(xvect *x)
{
  int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  size_t i, j;

  puts("* testing push/pop ...");

  for (i = 0; i < (sizeof a / sizeof(int)); ++i) {
    xv_push(x, a + i);
  }

  assert(*(int *)xv_get(x, 0) == 0);
  assert(*(int *)xv_get(x, 2) == 2);
  assert(*(int *)xv_get(x, 3) == 3);

  xv_set(x, 3, a + 1);

  assert(*(int *)xv_get(x, 3) == 1);

  xv_set(x, 3, a + 3);

  for (i = 0; i < (sizeof a / sizeof(int)); ++i) {
    j = (sizeof a / sizeof(int)) - 1 - i;
    assert(*(int *)xv_pop(x) == a[j]);
    assert(xv_size(x) == j);
  }

  puts(" => OK");
}

void
test_front(xvect *x)
{
  int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  size_t i, j;

  puts("* testing shift/unshift ...");

  for (i = 0; i < (sizeof a / sizeof(int)); ++i) {
    xv_unshift(x, a + (sizeof a / sizeof(int)) - 1 - i);
  }

  assert(*(int *)xv_get(x, 0) == 0);
  assert(*(int *)xv_get(x, 2) == 2);
  assert(*(int *)xv_get(x, 3) == 3);

  for (i = 0; i < (sizeof a / sizeof(int)); ++i) {
    j = (sizeof a / sizeof(int)) - 1 - i;
    assert(*(int *)xv_shift(x) == a[i]);
    assert(xv_size(x) == j);
  }

  puts(" => OK");
}

void
test_middle(xvect *x)
{
  int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  const int b[] = { 0, 1, 2, 7, 8, 9 };
  size_t i;

  puts("* testing insert/splice ...");

  for (i = 0; i < (sizeof a / sizeof(int)); i += 2) {
    xv_push(x, a + i);
  }

  assert(xv_size(x) == 5);

  xv_insert(x, 1, a + 1);
  xv_insert(x, 3, a + 3);
  xv_insert(x, 5, a + 5);
  xv_insert(x, 7, a + 7);
  xv_insert(x, 9, a + 9);

  assert(xv_size(x) == 10);

  for (i = 0; i < (sizeof a / sizeof(int)); ++i) {
    assert(*(int *)xv_get(x, i) == (int)i);
  }

  xv_splice(x, 3, 4);

  assert(xv_size(x) == 6);

  for (i = 0; i < (sizeof b / sizeof(int)); ++i) {
    assert(*(int *)xv_get(x, i) == b[i]);
  }

  puts(" => OK");
}

int
main(int argc, char *argv[])
{
  xvect x;

  puts("---- xvect test started ----");

  xv_init(&x, sizeof(int));

  test_rear(&x);
  test_front(&x);
  test_middle(&x);

  puts("---- xhash test successfully finished ----");

  return 0;
}
