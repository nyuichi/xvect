# xvect - super tiny extensible (and polymorphic) vector

- written in pure C99
- all components are in single header file

# Usage

```c
typedef struct xvect xvect;

static inline void xv_init(xvect *, size_t);
static inline void xv_destroy(xvect *);

static inline size_t xv_size(xvect *);
static inline void xv_reserve(xvect *, size_t);

static inline void *xv_get(xvect *, size_t);
static inline void xv_set(xvect *, size_t, void *);

static inline void xv_push(xvect *, void *);
static inline void *xv_peek(xvect *);
static inline void *xv_pop(xvect *);

static inline void xv_splice(xvect *, size_t, size_t);
```

# License

This software is licensed under the 2-clause BSD license. See LICENSE for details.

# Auther

Yuichi Nishiwaki (yuichi@idylls.jp)
