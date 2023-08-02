#ifndef CITH_H
#define CITH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CRESULT ----------------------------------- CRESULT */

#define CRESULT_GEN(T)				\
  typedef struct {				\
    char* e;					\
    T r;					\
  } cres_##T;

#define CRESULT_PTR_GEN(T)			\
  typedef struct {				\
    char* e;					\
    T* r;					\
  } cres_##T##_ptr;


typedef struct {
  char* e;
  void* r;
} cres_void_ptr;
  
typedef struct {
  char* e;
} cres;

/* CRESULT ----------------------------------- CRESULT */


/* CVEC ----------------------------------- CVEC */

typedef struct {
  void **data;
  size_t capacity;
  size_t size;
} cvec;

CRESULT_GEN(cvec);

void vecinit(cvec *v);

cres vecpush(cvec *v, void *value, size_t size);

cres vecdel(cvec *v, size_t i);

cres vecshrink(cvec *v);

cres_void_ptr vecget(cvec *v,size_t i);

void vecfree(cvec *v);

/* CVEC ----------------------------------- CVEC */


/* CSTRING ----------------------------------- CSTRING */

typedef struct {
  char* str;
  // Includes Null Terminator
  size_t size;
  size_t capacity;
} cstring;

CRESULT_GEN(cstring);

void strinit(cstring *s, const char* new_str);

cres strset(cstring *s, const char* new_str);

cres stradd(cstring *s, const char* add_str);

cres_cstring strslice(cstring *s, size_t start, size_t end);

cres_cvec strsplit(cstring *s, const char split_char);

void strfit(cstring *s);

cres strcap(cstring *s, size_t new_cap);

void strfree(cstring *s);

/* CSTRING ----------------------------------- CSTRING */

#endif
