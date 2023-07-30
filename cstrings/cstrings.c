#define REALLOC_SERR "Failed to reallocate string"
#define STR_GROWTH_FACTOR 1.6


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstrings.h>
#include <cvector.h>

void strinit(cstring *s) {
  s->str = NULL;
  s->size = 0;
  s->capacity = 0;
}

char* strset(cstring *s, const char* new_str) {
  size_t new_size = strlen(new_str) * STR_GROWTH_FACTOR + 1;
  if (s->capacity < new_size) {
    s->str = realloc(s->str, new_size * sizeof(char));
    if (!s->str) {
      return REALLOC_SERR;
    }
    s->capacity = new_size;
  }
  strcpy(s->str, new_str);
  s->size = new_size;
  return NULL;
}

char* stradd(cstring *s, const char* add_str) {
  // If string is empty it will add space for nullterminator
  size_t nullter = s->size == 0 ? 1 : 0;
  size_t new_size = (strlen(add_str) + s->size) * STR_GROWTH_FACTOR + nullter;
  if (s->capacity < new_size) {
    s->str = realloc(s->str, new_size * sizeof(char));
    if (!s->str) {
      return REALLOC_SERR;
    }
    s->capacity = new_size;
  }
  strcpy(&s->str[s->size - nullter], add_str);
  s->size = new_size;
  return NULL;
}

cvector strsplit(cstring *s, const char split_char) {
  cvector vecbuf;
  vecinit(&vecbuf);

  size_t last_slice = 0;
  for (size_t i = 0; i < s->size; i++) {
    if (s->str[i] == split_char || s->str[i] == '\0') {
      size_t slice_size = i-last_slice +1;
      char slice_buf[slice_size];
      strncpy(slice_buf, &s->str[last_slice], i-last_slice);
      slice_buf[slice_size-1] = '\0';
      
      vecpush(&vecbuf, slice_buf, slice_size);
      last_slice = i+1;
      i++;
    }
  }
  return vecbuf;
}

char* strcap(cstring *s, size_t new_cap) {
  if (new_cap == s->capacity) {
    return NULL;
  }
  s->str = realloc(s->str, new_cap * sizeof(char));
  if (!s->str) {
    return REALLOC_SERR; 
  }
  s->capacity = new_cap;
  if (s->capacity < s->size) {
    s->size = s->capacity;
  }
  return NULL;
}

char* strshrink(cstring *s) {
  if (s->capacity == s->size) {
    return NULL;
  }
  s->str = realloc(s->str, s->capacity * sizeof(char));
  if (!s->str) {
    return REALLOC_SERR;
  }
  s->capacity = s->size;
  return NULL;
}

void strfree(cstring *s) {
  free(s->str);
  s->str = NULL;
  s->size = 0;
  s->capacity = 0;
}
