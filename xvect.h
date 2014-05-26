#ifndef XVECT_H__
#define XVECT_H__

/*
 * Copyright (c) 2014 by Yuichi Nishiwaki <yuichi@idylls.jp>
 */

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct xvect {
  char *data;
  size_t size, capa, width;
} xvect;

static inline void xv_init(xvect *, size_t);
static inline void xv_destroy(xvect *);

static inline size_t xv_size(xvect *);

static inline void xv_reserve(xvect *, size_t);
static inline void xv_shrink(xvect *, size_t);

static inline void *xv_get(xvect *, size_t);
static inline void xv_set(xvect *, size_t, void *);

static inline void xv_push(xvect *, void *);
static inline void *xv_pop(xvect *);

static inline void xv_splice(xvect *, size_t, ptrdiff_t);
static inline void xv_insert(xvect *, size_t, void *);

static inline void
xv_init(xvect *x, size_t width)
{
  x->data = NULL;
  x->size = 0;
  x->capa = 0;
  x->width = width;
}

static inline void
xv_destroy(xvect *x)
{
  free(x->data);
}

static inline size_t
xv_size(xvect *x)
{
  return x->size;
}

static inline void
xv_adjust_(xvect *x, size_t newcapa)
{
  x->data = realloc(x->data, newcapa * x->width);
  x->capa = newcapa;
  x->size = x->capa < x->size ? x->capa : x->size;
}

static inline void
xv_reserve(xvect *x, size_t mincapa)
{
  if (x->capa < mincapa) {
    xv_adjust_(x, mincapa);
  }
}

static inline void
xv_shrink(xvect *x, size_t maxcapa)
{
  if (x->capa > maxcapa) {
    xv_adjust_(x, maxcapa);
  }
}

static inline void *
xv_get(xvect *x, size_t i)
{
  return x->data + i * x->width;
}

static inline void
xv_set(xvect *x, size_t i, void *src)
{
  memcpy(xv_get(x, i), src, x->width);
}

static inline void
xv_push(xvect *x, void *src)
{
  if (x->capa <= x->size + 1) {
    xv_reserve(x, x->size * 2 + 1);
  }
  xv_set(x, x->size++, src);
}

static inline void *
xv_pop(xvect *x)
{
  return xv_get(x, --x->size);
}

static inline void
xv_splice(xvect *x, size_t i, ptrdiff_t c)
{
  xv_reserve(x, x->size - c);
  memmove(xv_get(x, i), xv_get(x, i + c), (x->size - i - c) * x->width);
  x->size -= c;
}

static inline void
xv_insert(xvect *x, size_t i, void *src)
{
  xv_splice(x, i, -1);
  xv_set(x, i, src);
}

#if defined(__cplusplus)
}
#endif

#endif
