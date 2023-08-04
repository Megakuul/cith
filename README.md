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
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}
```

To a single character you can use it exactly the same way, but with *strsetc* name and a char as second argument;

**stradd**

This function is used to append a string to the string and can be used like this:

```c
cres res = stradd(&mystr, " im a suffix");
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}
```

To append a single character you can use it exactly the same way, but with *straddc* name and a char as second argument;

**csprintf**

This function is used to format a string and can be used like this:

```c
cres_cstring res = csprintf("Lets format a %s and a int [%i]", "string", 187);
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}

printf("Formated: %s\n", res.r.str);
// Important the res is a cstring, remember to free it
strfree(&res.r);
```

If you want to use it by using a cstring buffer, you can do this aswell with *strcsprintf*, this function does exactly the same, buf takes a cstring as first argument and does return a raw cres.

**strslice**

This function is used to get a slice of the string and can be used like this:

```c
cres_cstring myslice = strslice(&mystr, 1, 6);
if (myslice.e!=NULL) {
   fprintf(stderr, "Error: %s\n", myslice.e);
   exit(1);
}
printf("Success: %s\n", myslice.r.str);
// Important the slice is a cstring, remember to free it
strfree(&myslice.r);
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

// Remember that the char* from the listelements is not deallocated with vecfree
// For this you can use *vecfreef* with *strfree*
vecfreef(&mylist.r, (vecfreefunc)strfree);
```

**strcap**

This function is used to reset the capacity of the string and can be used like this:

```c
cres res = strcap(&mystr, 20);
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
}
```

If the string is shorter then the cap it will just cut of the string

**strfit**

This function is used to set the strings size to the actual lenght (+1) of the string. Can be used if e.g. '\0' where written to the end of the string.

```c
// if string looks like this "Hallo Grüessech\0\0\0\0" the size is 19
cres res = strfit(&mystr);
if (res.e!=NULL) {
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
if (res.e!=NULL) {
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

**vecinit**

This function is used to initialize a vector and is used like:

```c
cvec myvec;
vecinit(&myvec);
```

**vecpush**

This function is used to push a value at the end of the array and is used like this

```c
// Strings
char* name = "Karlo";
cres res = vecpush(&myvec, name, strlen(name) + 1);
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
   exit(1);
}

// CStrings
cstring first_name = "Kater";
cres res = vecpush(&myvec, &first_name, sizeof(first_name));
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
   exit(1);
}

// Other types like integer
int age = 54;
cres res = vecpush(&myvec, &age, sizeof(age));
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
   exit(1);
}

// The vector looks now like this
/*
The Vector now looks something like this:
Whereas 111 ressembles the myvec.data attribute.

Stack
|ptr	|value
 111	 777
 112	 187
 113	 999

Heap (anywhere)
|ptr	 |value
 187	  first_name
 777	  'K'
 778	  'a'
 779	  'r'
 780	  'l'
 781	  'o'
 782	  '\0'
 999	  54
*/
```

*Important* the variable that is provided to the vecpush function (e.g. age or first_name) is copied to the heap, so if the local variable like age/first_name is deallocated, it will still be present.

**vecdel**

This function deletes a value out of the vector and moves the other vector pointers to the left. You can use it like this

```c
cres res = vecdel(&myvec, 2);
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
   exit(1);
}

/*
Important: The vector will deallocate its heap memory, but if you allocated a pointer to other memory (like a cstring does),
you also need to deallocate this object.
*/
```

**vecshrink**

This function will shrink the vectors capacity to the vectors size, you can use it like

```c
cres res = vecshrink(&myvec);
if (res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", res.e);
   exit(1);
}
```

**vecget**

This function will safely getting a value of the vector without risking to access memory you its not supposed to access. You can use it like this

```c
cres_void_ptr value_res = vecget(&myvec, 2);
if (value_res.e!=NULL) {
   fprintf(stderr, "Error: %s\n", value_res.e);
   exit(1);
}

// Usually you will need to cast the value to its datatype
printf("Value found: %i\n", (int)value_res.r);

// Vecget is in this example the same as myvec.data[2] but if the value is out of bound it will return a *out of bound error* instead of accessing unexpected memory.
```

**vecfree**

This function will free the vector and all of its allocated heap memory, use it like this

```c
vecfree(&myvec);
```

**vecfreef**

This function will free the vector and all of its allocated heap memory, in addition you can provide a function that will be executed on every memory block before deallocation, you can use it like

```c
vecfreef(&myvec, (vecfreefunc)strfree);
```

It takes a function with following type as second argument
```c
typedef void (*vecfreefunc)(void*);
```
The function takes one argument (void*) that is the current item.

A typicall usecase is when you have a cstring vector, on this vector you also need to free every single cstring from the vector. To do so, you can just use strfree and cast it to vecfreefunc.