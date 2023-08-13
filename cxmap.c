#include <cith.h>

#define REALLOC_MERR "Failed to reallocate xmap"
#define ALLOC_MERR "Failed to allocate memory for xmap"

#define MAP_GROWTH_FACTOR 2.1

cres xmapinit(cxmap *c, int initialsize, int poolsize) {
  cres res = {NULL};
  c->data = calloc(initialsize, sizeof(void*));
  if (!c->data) {
    res.e = ALLOC_MERR;
    return res;
  }
  c->capacity = initialsize;
  c->size = 0;

  poolinit(&c->pool, poolsize);
  return res;
}

cres xmapadd(cxmap *c, char *key, void *value, size_t valuesize) {
  cres res = {NULL};
  if (c->capacity < c->size + 1) {
    c->capacity = (c->capacity + 1) * MAP_GROWTH_FACTOR;
    c->data = realloc(c->data, c->capacity * sizeof(void*));
    if (!c->data) {
      res.e = REALLOC_MERR;
      return res;
    }
  }
  size_t index = maphash(key) % c->capacity;
  size_t index_buf = index;
  int op = 1;
  while (c->data[index_buf] != NULL) {
    op = index_buf+1>c->capacity ? -1 : op;
    index_buf = index_buf + op;
  }
  c->data[index_buf] = poolalloc(&c->pool, valuesize).r;
  memcpy(c->data[index_buf], value, valuesize);
  c->size++;
  return res;
}

