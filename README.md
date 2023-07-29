# C IS TO HARD - CITH

Cith is a library that contains some simple datatypes that are common in higher level languages

It also offers the option to disable parts of the library. This makes it **blazingly** lightweight.

### Use the library

To use the library, copy it into your projects folder,
then add following lines to your **CMakeLists.txt**

```cmake
set(CITH_BUILD_VECTOR ON CACHE BOOL "")
set(CITH_BUILD_STRINGS ON CACHE BOOL "")

add_subdirectory(cith)

target_link_libraries(cith)
```

In your C files you can then just include the components

```c
#include <cvector.h>
#include <cstrings.h>
```

### CVector example

```c
#include <stdio.h>
#include <stdlib.h>
#include <cvector.h>
#include <string.h>

int main(void) {
  cvector myvec;
  vecinit(&myvec);


  for (size_t i = 0; i < 1000; i++) {
    int len = snprintf(NULL, 0, "I got %zu eggs", i);
    char str[len+1];

    sprintf(str, "I got %zu eggs", i);
    char* err = vecpush(&myvec, str, len+1);
    if (err!=NULL) {
      printf("Error: %s\n", err);
    }
  }

  char* res = vecget(&myvec, 2000);
  if (res!=NULL) {
    printf("%s\n", (char *)vecget(&myvec, 2000));
  }

  for (size_t i = 0; i < myvec.size; i++) {
    printf("%s\n", (char *)vecget(&myvec, i));
  }

  vecdel(&myvec, 2);
  vecdel(&myvec, 5);
  vecdel(&myvec, 8);

  printf("NR of allocated ptrs %zu\n", myvec.capacity);

  char* err = vecshrink(&myvec);
  if (err!=NULL) {
    printf("Error: %s\n", err);
    return 1;
  }
  printf("NR of allocated ptrs after cleanup %zu\n", myvec.capacity);

  vecfree(&myvec);
  return 0;
}

```