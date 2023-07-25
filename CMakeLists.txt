cmake_minimum_required(VERSION 3.17)
project(cith C)

option(CITH_BUILD_VECTOR "Build cith vector component" ON)
option(CITH_BUILD_STRINGS "Build cith strings component" ON)

if (CITH_BUILD_VECTOR)
    add_subdirectory(vector)
endif()

if (CITH_BUILD_STR)
    add_subdirectory(strings)
endif()

add_library(cith ${SOURCES})
target_include_directories(cith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})