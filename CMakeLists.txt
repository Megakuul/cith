cmake_minimum_required(VERSION 3.17)
project(cith C)

file(GLOB SOURCE "*.c")

add_library(cith ${SOURCE})
target_include_directories(cith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
