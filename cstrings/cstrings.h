#ifndef CSTRINGS_H
#define CSTRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cvector.h>

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

void strinit(cstring *s);

char* strset(cstring *s, const char* new_str);

char* stradd(cstring *s, const char* add_str);

cvector strsplit(cstring *s, const char split_char);

char* strcap(cstring *s, size_t new_cap);

void strfree(cstring *s);

#endif
