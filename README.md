# C IS TO HARD - CITH

Cith is a library that contains some simple datatypes that are common in higher level languages

### Use the library

To use the library, copy it into your projects folder,
then add following lines to your **CMakeLists.txt**

```cmake
file(GLOB CITH_SOURCES "cith/*.c")
set(CITH_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/cith)

add_executable(... ${CITH_SOURCES})
# or add_library(... ${CITH_SOURCES})

target_include_directories(... ${CITH_INCLUDES})
```
The library is just built with your build-tool, I think the easiest way is just to directly compile it (as the library is so small that it is most likely statically linked anyway).

Cith implements some "pseudo-generic" types, as C does not natively support templates, generic types are generated with X-Macros. That means that you need to add the types you need, for this create a **cithconf.h** file (or whatever you want to call it) and make sure to link it somewhere in your code.

(As it is not really clean I already removed it from the vector)

If you want to implement custom CRESULT types you can add it like this to the file:

```c
#include <cith.h>
// Add CRES char
CRESULT(char) // That generates the type: cres_char
// Add CRES char*
CRESULT_PTR(char) // That generates the type: cres_char_ptr
```

**IMPORTANT** unfortunaly Macro-Cascading is not possible in C, this is why there is no lock guard. In clear that means that the compiler will fail if a X-Macro is invoked twice.

Following type implementations are already used from the cith library itself. Do not add them to your cithconf file:

```c
CRESULT(cstring);
CRESULT(cvec);
```

### Documentation

#### CRESULT

CRES is a component that introduces a Error-Pattern. A CRES Object contains a *error* propertie and a *result* propertie.
Error ressembles a string (char_ptr) that contains a error message and NULL if everything went well. You can access it by using the *.e* propertie on the result.
Result is the actual return of the function, there are 4 different implementations for the result:
 - cres_{type} 	     returns a type 	     (generate it with CRESULT({type})
 - cres_{type}_ptr   returns a type_ptr      (generate it with CRESULT_PTR({type})
 - cres_void_ptr     returns a void_ptr	     (does not need to be generated)
 - cres		     does not have a result  (does not need to be generated)

In action that looks like this:

Example 1
```c
cres dosomething() {
     cres res = {NULL};

     char* myptr = malloc(10);
     if (!myptr) {
     	res.e = "Failed to allocate Memory";
	return res;
     }
     free(myptr);
     return res;
}

cres ds = dosomething();
if (ds.e != NULL) {
   fprintf(stderr, "ERROR: %s\n", ds.e);
   exit(1);
}
```

Example 2
```c
/*
  Make sure that char_ptr is defined as CRESULT in the cithconf.h
  with CRESULT_PTR(char);
*/
cres_char_ptr dosomething() {
     cres_char_ptr res = {NULL, NULL};

     char* myptr = malloc(10);
     if (!myptr) {
     	res.e = "Failed to allocate Memory";
	return res;
     }
     res.r = myptr;
     return res;
}

cres_char_ptr ds = dosomething();
if (ds.e != NULL) {
   fprintf(stderr, "ERROR: %s\n", ds.e);
   exit(1);
}

printf("SUCCESS: %s\n", ds.r);
```


#### CSTRING

CSTRING is a component that build a dynamic string. It is basically just a wrapper around a char* pointer. The difference is that you can use its built in functions to dynamically manipulate the string without always reallocating its memory.

**IMPORTANT**: The size propertie on the cstring object is the size of the memory allocated NOT the string lenght (it also contains the '\0' terminator). To get the string lenght use strlen(mycstring.str).

It implements following functions:

**strinit**

This function is used to initialize the string and can be used like this:

```c
cstring mystr;
strinit(&mystr, "initial string");
```

Use NULL as new_str on the strinit function to initialize an empty string.

**strset**

This function is used to set a value to the string and can be used like this:

```c
cres res = strset(&mystr, "New string");
if (res!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}
```

**stradd**

This function is used to append a string to the string and can be used like this:

```c
cres res = stradd(&mystr, " im a suffix");
if (res!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}
```

**strslice**

This function is used to get a slice of the string and can be used like this:

```c
cres_cstring myslice = strslice(&mystr, 1, 6);
if (myslice.e!=NULL) {
   fprintf(stderr, "Error: %s\n", myslice.e);
   exit(1);
}
printf("Success: %s\n", myslice.r.str);
```

**strsplit**

This function is used to split the string and can be used like this:

```c
cres_cvec mylist = strsplit(&mystr, ';');
if (mylist.e != NULL) {
   fprintf(stderr, "Error: %s\n", mylist.e);
   exit(1);
}
for (int i = 0; i < mylist.r.size; i++) {
  void* ptr = vecget(&mylist.r, i).r;
    
  cstring* newstr = (cstring*)ptr;
  printf("Found: %s\n", newstr->str);
}
```

**strcap**

This function is used to reset the capacity of the string and can be used like this:

```c
cres res = strcap(&mystr, 20);
if (res!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}
```

If the string is shorter then the cap it will just cut of the string

**strfit**

This function is used to set the strings size to the actual lenght (+1) of the string. Can be used if e.g. '\0' where written to the end of the string.

```c
// if string looks like this "Hallo Grüessech\0\0\0\0" the size is 19
cres res = strfit(&mystr);
if (res!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}

// Now the size is 16
```


**strshrink**

This function is used to shrink the capacity of the string to the size of the string.
Usually capacity is allocated exponentially (to reduce reallocs), if you want to
remove the extra space of the capacity you can shrink it like:


```c
// cap is 1024 and size is 754
cres res = strshrink(&mystr);
if (res!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}

// Now the cap and size is 754
```

**strfree**

This function is used to free the bytes allocated and to reset the string object.


```c
strfree(&mystr);
```


#### CVECTOR

CVector is a dynamic array of void pointers that point to heap allocated memory.
Will do the docs tomorrow im tired
