add_library(sub sub.c sub.h)
target_include_directories(sub INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
