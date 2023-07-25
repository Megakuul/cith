#ifndef VECTOR_H
#define VECTOR_H

// Im getting stupid using this language
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} vector;

void vecinit(vector *v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vecpush(vector *v, void *value) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;
    }
}

#endif