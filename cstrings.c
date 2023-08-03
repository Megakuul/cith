#define REALLOC_SERR "Failed to reallocate string"
#define SIZE_SERR "START cannot be higher then END of slice"
#define OUTOFBOUNDS_SERR "START or END is out of string bound"
#define STR_GROWTH_FACTOR 1.6

#include <cith.h>

void strinit(cstring *s, const char* new_str) {
  s->str = NULL;
  s->size = 0;
  s->capacity = 0;

  if (new_str != NULL) {
    strset(s, new_str);
  }		    
}

cres strset(cstring *s, const char* new_str) {
  cres res = {NULL};
  size_t new_size = strlen(new_str) + 1;
  size_t new_capacity = new_size * STR_GROWTH_FACTOR;
  if (s->capacity < new_capacity) {
    s->str = realloc(s->str, new_capacity * sizeof(char));
    if (!s->str) {
      res.e = REALLOC_SERR;
      return res;
    }
    s->capacity = new_capacity;
  }
  strcpy(s->str, new_str);
  s->size = new_size;
  return res;
}

cres strsetc(cstring *s, const char new_char) {
  cres res = {NULL};
  size_t new_size = 2;
  size_t new_capacity = new_size * STR_GROWTH_FACTOR;
  if (s->capacity < new_capacity) {
    s->str = realloc(s->str, new_capacity * sizeof(char));
    if (!s->str) {
      res.e = REALLOC_SERR;
      return res;
    }
    s->capacity = new_capacity;
  }
  s->str[0] = new_char;
  s->str[1] = '\0';
  s->size = new_size;
  return res;
}

cres stradd(cstring *s, const char* add_str) {
  cres res = {NULL};
  // If string is empty it will add space for nullterminator
  size_t nullter = s->size == 0 ? 1 : 0;
  size_t new_size = strlen(add_str) + s->size + nullter;
  size_t new_capacity = new_size * STR_GROWTH_FACTOR;
  if (s->capacity < new_capacity) {
    s->str = realloc(s->str, new_capacity * sizeof(char));
    if (!s->str) {
      res.e = REALLOC_SERR;
      return res;
    }
    s->capacity = new_capacity;
  }
  strcpy(&s->str[s->size - nullter], add_str);
  s->size = new_size;
  return res;
}

cres straddc(cstring *s, const char add_char) {
  cres res = {NULL};
  size_t nullter = s->size == 0 ? 1 : 0;
  size_t new_size = 1 + s->size + nullter;
  size_t new_capacity = new_size * STR_GROWTH_FACTOR;
  if (s->capacity < new_capacity) {
    s->str = realloc(s->str, new_capacity * sizeof(char));
    if (!s->str) {
      res.e = REALLOC_SERR;
      return res;
    }
    s->capacity = new_capacity;
  }
  s->str[s->size-nullter] = add_char;
  s->str[s->size-nullter+1] = '\0';
  s->size = new_size;
  return res;
}

cres_cstring strslice(cstring *s, size_t start, size_t end) {
  cres_cstring res = {NULL, NULL};
  cstring strbuf;
  strinit(&strbuf, NULL);
  if (start >= end) {
    strfree(&strbuf);
    res.e = SIZE_SERR;
    return res;
  }
  if (end >= s->size-1 || start < 0) {
    strfree(&strbuf);
    res.e = OUTOFBOUNDS_SERR;
    return res;
  }
  strcap(&strbuf, end-start + 1);
  strncpy(strbuf.str, &s->str[start], end-start);
  res.r = strbuf;
  return res;
}


cres_cvec strsplit(cstring *s, const char split_char) {
  cres_cvec res = {NULL, NULL};
  cvec vecbuf;
  vecinit(&vecbuf);

  size_t last_slice = 0;
  for (size_t i = 0; i < s->size; i++) {
    if (s->str[i] == split_char || s->str[i] == '\0') {
      size_t slice_size = i-last_slice +1;
      
      if (slice_size < 2) {
	last_slice = i+1;
	continue;
      }

      cstring slice_buf;
      strinit(&slice_buf, NULL);

      /* TODO:
	 The following process could be optimized by implementing a custom
	 strncpy function for cstring to handle automatic capacity change and 
	 also resizing (strfit).
       */
      strcap(&slice_buf, slice_size);
      
      strncpy(slice_buf.str, &s->str[last_slice], i-last_slice);
      slice_buf.str[slice_size-1] = '\0';
      
      strfit(&slice_buf);
      cres push_res = vecpush(&vecbuf, &slice_buf, sizeof(slice_buf));
      if (push_res.e != NULL) {
	vecfree(&vecbuf);
	strfree(&slice_buf);
	res.e = push_res.e;
	return res;
      }
      last_slice = i+1;
      i++;
    }
  }
  res.r = vecbuf;
  return res;
}

cres strcap(cstring *s, size_t new_cap) {
  cres res = {NULL};
  if (new_cap == s->capacity) {
    return res;
  }
  s->str = realloc(s->str, new_cap * sizeof(char));
  if (!s->str) {
    res.e = REALLOC_SERR;
    return res;
  }
  s->capacity = new_cap;
  if (s->capacity < s->size) {
    s->size = s->capacity;
  }
  return res;
}

void strfit(cstring *s) {
  if (s->str != NULL) {
    s->size = strlen(s->str) + 1;
  } else {
    s->size = 0;
  }
}

cres strshrink(cstring *s) {
  cres res = {NULL};
  if (s->capacity == s->size) {
    return res;
  }
  s->str = realloc(s->str, s->capacity * sizeof(char));
  if (!s->str) {
    res.e = REALLOC_SERR;
    return res;
  }
  s->capacity = s->size;
  return res;
}

void strfree(cstring *s) {
  free(s->str);
  s->str = NULL;
  s->size = 0;
  s->capacity = 0;
}
