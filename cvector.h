#ifndef CVECTOR_H
#define CVECTOR_H

#define REALLOC_VERR "Failed to reallocate vector"
#define ALLOC_VERR "Failed to allocate new element"
#define IOOR_VERR "Index is out of range"
#define OUTOFBOUNDS_VERR "Element is out of Bound"
#define AUTO_SIZE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cresult.h>

#define CVECTOR(T)						\
  typedef struct {						\
    T **data;							\
    size_t capacity;						\
    size_t size;						\
  } cvector_##T##_ptr;						\
								\
 void vecinit_##T##_ptr(cvector_##T##_ptr *v) {			\
  v->data = NULL;						\
    v->size = 0;						\
    v->capacity = 0;						\
 }								\
       								\
 cres vecpush_##T##_ptr(cvector_##T##_ptr *v, T *value, size_t size) {	\
   cres res = {NULL};							\
   if (v->size == v->capacity) {					\
     v->capacity = v->capacity == 0 ? 1 : v->capacity*2;		\
     v->data = realloc(v->data, v->capacity * sizeof(T*));		\
     if (!v->data) {							\
       res.e = REALLOC_VERR;						\
       return res;							\
     }									\
   }									\
   if (size==AUTO_SIZE)							\
     size=sizeof(*value);						\
     									\
   v->data[v->size] = malloc(size);					\
   if (!v->data[v->size]) {						\
     res.e = ALLOC_VERR;						\
     return res;							\
   }									\
   memcpy(v->data[v->size], value, size);				\
   v->size++;								\
   return res;								\
 }									\
 									\
 cres vecdel_##T##_ptr(cvector_##T##_ptr *v, size_t i) {	\
   cres res = {NULL};						\
   if (i >= v->size) {						\
     res.e = IOOR_VERR;						\
     return res;						\
   }								\
   free(v->data[i]);						\
   for (size_t j = i; j < v->size -1; j++) {			\
     v->data[j] = v->data[j+1];					\
   }								\
   								\
   v->size--;							\
   return res;							\
 }								\
 								\
 cres vecshrink_##T##_ptr(cvector_##T##_ptr *v) {		\
   cres res = {NULL};				       		\
   if (v->size == v->capacity) {	       			\
     return res;						\
   }			       					\
   								\
   v->capacity = v->size;					\
  								\
   v->data = realloc(v->data, v->capacity * sizeof(void *));	\
   if (!v->data) {					       	\
     res.e = REALLOC_VERR;			       		\
     return res;						\
   }				       				\
   return res;		       					\
 }		       						\
 	       							\
 cres_##T##_ptr vecget_##T##_ptr(cvector_##T##_ptr *v,size_t i) {	\
   cres_##T##_ptr res = {NULL, NULL};					\
   if (v->size >= i) {							\
     res.r = v->data[i];						\
     return res;							\
   } else {								\
     res.e = OUTOFBOUNDS_VERR;						\
     return res;							\
   }									\
 }									\
 									\
 void vecfree_##T##_ptr(cvector_##T##_ptr *v) {				\
   for (size_t i = 0; i < v->size; ++i) {				\
     free(v->data[i]);							\
   }									\
   free(v->data);							\
   v->data = NULL;							\
   v->size = 0;								\
   v->capacity = 0;							\
 }

#endif
