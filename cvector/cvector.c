#define REALLOC_VERR "Failed to reallocate vector"
#define ALLOC_VERR "Failed to allocate new element"
#define IOOR_VERR "Index is out of range"

#include <stdio.h>
#include <stdlib.h>
#include <cvector.h>
#include <string.h>

void vecinit(cvector *v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

char* vecpush(cvector *v, void *value, size_t valsize) {
  if (v->size == v->capacity) {
    v->capacity = v->capacity == 0 ? 1 : v->capacity*2;
    v->data = realloc(v->data, v->capacity * sizeof(void *));
    if (!v->data) {
      return REALLOC_VERR;
    }
  }
  v->data[v->size] = malloc(valsize);
  if (!v->data[v->size]) {
    return ALLOC_VERR;
  }
  memcpy(v->data[v->size], value, valsize);
  v->size++;
  return NULL;
}

char* vecdel(cvector *v, size_t i) {
  if (i >= v->size) {
    return IOOR_VERR;
  }
  free(v->data[i]);
  for (size_t j = i; j < v->size -1; j++) {
    v->data[j] = v->data[j+1];
  }

  v->size--;
  return NULL;
}

char* vecshrink(cvector *v) {
  if (v->size == v->capacity) {
    return NULL;
  }

  v->capacity = v->size;

  v->data = realloc(v->data, v->capacity * sizeof(void *));
  if (!v->data) {
    return REALLOC_VERR;
  }
  return NULL;
}

void* vecget(cvector *v, size_t i) {
  if (v->size >= i) {
    return v->data[i];
  } else {
    return NULL;
  }
}

void vecfree(cvector *v) {
  for (size_t i = 0; i < v->size; ++i) {
    free(v->data[i]);
  }
  free(v->data);
}
