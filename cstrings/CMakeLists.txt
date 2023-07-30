add_library(cstrings cstrings.c)
target_include_directories(cstrings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cstrings PUBLIC cvector)
