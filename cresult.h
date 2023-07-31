#ifndef CRESULT_H
#define CRESULT_H


#define CRESULT(T)				\
  typedef struct {				\
    char* e;					\
    T r;					\
  } cres_##T;

#define CRESULT_PTR(T)				\
  typedef struct {				\
    char* e;					\
    T* r;					\
  } cres_##T_ptr;


typedef struct {
  char* e;
  void* r;
} cres_void_ptr;
  
typedef struct {
  char* e;
} cres;


#endif
