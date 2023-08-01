#ifndef CSTRINGS_H
#define CSTRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cvector.h>
#include <cresult.h>

/* 
   Size and capacity are not intendet to use,
   they contain the null terminator.
   To get the size of the string use strlen(s->str);
*/

typedef struct {
  char* str;
  // Includes Null Terminator
  size_t size;
  // Includes Null Terminator
  size_t capacity;
} cstring;

CRESULT_PTR(cstring);
CRESULT(cstring);
CVECTOR(cstring);
CRESULT(cvector_cstring_ptr);

void strinit(cstring *s, const char* new_str);

cres strset(cstring *s, const char* new_str);

cres stradd(cstring *s, const char* add_str);

cres_cstring strslice(cstring *s, size_t start, size_t end);

cres_cvector_cstring_ptr strsplit(cstring *s, const char split_char);

void strfit(cstring *s);

cres strcap(cstring *s, size_t new_cap);

void strfree(cstring *s);

#endif
