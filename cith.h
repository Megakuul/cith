#ifndef CITH_H
#define CITH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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

typedef void (*vecfreefunc)(void*);
void vecfreef(cvec *v, vecfreefunc func);

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

cres strsetc(cstring *s, const char new_char);

cres stradd(cstring *s, const char* add_str);

cres straddc(cstring *s, const char add_char);

cres strcsprintf(cstring *s, const char *format, ...);

cres_cstring csprintf(const char *format, ...);

cres_cstring strslice(cstring *s, size_t start, size_t end);

cres_cvec strsplit(cstring *s, const char split_char);

void strfit(cstring *s);

cres strcap(cstring *s, size_t new_cap);

void strfree(cstring *s);

/* CSTRING ----------------------------------- CSTRING */


/* CMAP ----------------------------------------- CMAP */

typedef struct {
  void **data;
  int capacity;
  int size;
  int collision_index;
} cmap;

size_t maphash(char*key);

cres mapinit(cmap*c, int initialsize);

cres mapadd(cmap*c, char*key, void*value, size_t valuesize);


/* CMAP ----------------------------------------- CMAP */

/* CPALLOC ----------------------------------------- CPALLOC */

typedef struct {
  int size;
  void *ptr;
} cblock;

typedef struct {
  int poolsize;
  cvec *free_list;
  void *data;
  cpool *nextpool;
} cpool;

/* CPALLOC ----------------------------------------- CPALLOC */

#endif
