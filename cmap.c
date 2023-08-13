#include <cith.h>

#define REALLOC_MERR "Failed to reallocate map"
#define ALLOC_MERR "Failed to allocate memory for map"

#define MAP_GROWTH_FACTOR 2.1
#define MAP_LOAD_FACTOR 0.7

size_t maphash(char *key) {
  // Someone smarter than me once said that this is a good number
  size_t hash = 5381;
  int c;
  while((c = *key++))
    hash = hash * 33 + c;
  return hash;
}

cres mapinit(cmap *c, int initialsize) {
  cres res = {NULL};
  c->data = calloc(initialsize, sizeof(void*));
  if (!c->data) {
    res.e = ALLOC_MERR;
    return res;
  }
  c->capacity = initialsize;
  c->size = 0;
  c->collision_index = 0;
  return res;
}

cres mapadd(cmap *c, char *key, void *value, size_t valuesize) {
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
  c->data[index_buf] = malloc(valuesize);
  memcpy(c->data[index_buf], value, valuesize);
  c->size++;
  return res;
}

