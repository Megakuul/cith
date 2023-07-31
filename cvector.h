#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cresult.h>

typedef struct {
  void **data;
  size_t capacity;
  size_t size;
} cvector;

CRESULT(cvector)
  
void vecinit(cvector *v);

cres vecpush(cvector *v, void *value, size_t size);

cres_void_ptr vecget(cvector *v, size_t i);

cres vecdel(cvector *v, size_t i);

cres vecshrink(cvector *v);

void vecfree(cvector *v);

#endif
