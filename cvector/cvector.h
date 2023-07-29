#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void **data;
  size_t capacity;
  size_t size;
} cvector;

void vecinit(cvector *v);

char* vecpush(cvector *v, void *value, size_t size);

void* vecget(cvector *v, size_t i);

char* vecdel(cvector *v, size_t i);

char* vecshrink(cvector *v);

void vecfree(cvector *v);

#endif
