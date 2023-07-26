#include <stdio.h>
#include <stdlib.h>
#include <cvector.h>

void vecinit(cvector *v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vecpush(cvector *v, void *value) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;
    }
}

void vecfree(cvector *v) {
    free(v);
}