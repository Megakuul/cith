cmake_minimum_required(VERSION 3.17)
project(cith C)

option(CITH_BUILD_VECTOR "Build cith vector component" ON)
option(CITH_BUILD_STRINGS "Build cith strings component" ON)

if (CITH_BUILD_VECTOR)
    add_subdirectory(cvector)
endif()

if (CITH_BUILD_STR)
    add_subdirectory(cstrings)
endif()

add_library(cith INTERFACE)
target_include_directories(cith INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cith INTERFACE cvector cstrings)