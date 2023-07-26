#ifndef CVECTOR_H
#define CVECTOR_H

// Im getting stupid using this language
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} cvector;

void vecinit(cvector *v);

void vecpush(cvector *v, void *value);

void vecfree(cvector *v);

#endif