#include <cith.h>

#define REALLOC_MERR "Failed to reallocate map"
#define ALLOC_MERR "Failed to allocate memory for map"

#define MAP_GROWTH_FACTOR 2.1

size_t maphash(char *key, int capacity) {
  // Someone smarter than me once said that this is a good number
  size_t hash = 5381;
  int c;
  while((c = *key++))
    hash = hash * 33 + c;
  return hash % capacity;
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
  size_t index = maphash(key, c->capacity);
  while (c->data[index] != NULL) {
    index = (index+1) % c->capacity;
  }
  c->data[index] = malloc(valuesize);
  memcpy(c->data[index], value, valuesize);
  c->size++;
}
