# C IS TO HARD - CITH

Cith is a library that contains some simple datatypes that are common in higher level languages

It also offers the option to disable parts of the library. This makes it **blazingly** lightweight.

### Use the library

To use the library, copy it into your projects folder,
then add following lines to your **CMakeLists.txt**

```c
set(CITH_BUILD_VECTOR ON CACHE BOOL "")
set(CITH_BUILD_STRINGS ON CACHE BOOL "")

add_subdirectory(cith)

target_link_libraries(cith)
```

In your C files you can then just include the components

```c
#include <cith/vector.h>
#include <cith/strings.h>
```