#define REALLOC_VERR "Failed to reallocate vector"
#define ALLOC_VERR "Failed to allocate new element"
#define IOOR_VERR "Index is out of range"
#define OUTOFBOUNDS_VERR "Element is out of Bound"

#include <cvector.h>

void vecinit(cvector *v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

cres vecpush(cvector *v, void *value, size_t valsize) {
  cres res = {NULL};
  if (v->size == v->capacity) {
    v->capacity = v->capacity == 0 ? 1 : v->capacity*2;
    v->data = realloc(v->data, v->capacity * sizeof(void *));
    if (!v->data) {
      res.e = REALLOC_VERR;
      return res;
    }
  }
  v->data[v->size] = malloc(valsize);
  if (!v->data[v->size]) {
    res.e = ALLOC_VERR;
    return res;
  }
  memcpy(v->data[v->size], value, valsize);
  v->size++;
  return res;
}

cres vecdel(cvector *v, size_t i) {
  cres res = {NULL};
  if (i >= v->size) {
    res.e = IOOR_VERR;
    return res;
  }
  free(v->data[i]);
  for (size_t j = i; j < v->size -1; j++) {
    v->data[j] = v->data[j+1];
  }

  v->size--;
  return res;
}

cres vecshrink(cvector *v) {
  cres res = {NULL};
  if (v->size == v->capacity) {
    return res;
  }

  v->capacity = v->size;

  v->data = realloc(v->data, v->capacity * sizeof(void *));
  if (!v->data) {
    res.e = REALLOC_VERR;
    return res;
  }
  return res;
}

cres_void_ptr vecget(cvector *v, size_t i) {
  cres_void_ptr res = {NULL, NULL};
  if (v->size >= i) {
    res.r = v->data[i];
    return res;
  } else {
    res.e = OUTOFBOUNDS_VERR;
    return res;
  }
}

void vecfree(cvector *v) {
  for (size_t i = 0; i < v->size; ++i) {
    free(v->data[i]);
  }
  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}
