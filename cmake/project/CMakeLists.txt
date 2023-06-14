#set cmake minimum required version, project name and languages
cmake_minimum_required(VERSION 3.10)
project(testprj C CXX)


#set source directory of this project
set(PRJ_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)


#information of CPU architecture
message(STATUS "CPU_ARCH: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message("")

#information of operation system
message(STATUS ${CMAKE_HOST_SYSTEM})
if (UNIX)
    set(system "UNIX-like")
elseif(APPLE)
    set(system "macOS")
elseif(WIN32)
    set(system "windows")
else()
    message(FATAL_ERROR "Operation system not recognized, only support unix apple and windows.")
endif()
message(STATUS "OS: " ${system})
message("")

#information of compilation toolchain
message(STATUS "CMAKE_C_COMPILER:  " ${CMAKE_C_COMPILER} " " ${CMAKE_C_COMPILER_ID} ":" ${CMAKE_C_COMPILER_VERSION} " " ${CMAKE_C_STANDARD})
message(STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} " " ${CMAKE_CXX_COMPILER_ID} ":" ${CMAKE_CXX_COMPILER_VERSION} " " ${CMAKE_CXX_STANDARD})
message(STATUS "CMAKE_AR: " ${CMAKE_AR})
message(STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB})
message(STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND})
message(STATUS "CMAKE_VERSION: " ${CMAKE_VERSION})
message(STATUS "CMAKE_GENERATOR: " ${CMAKE_GENERATOR})
message(STATUS "CMAKE_BUILD_TOOL: " ${CMAKE_BUILD_TOOL})

message(STATUS "CMAKE_SHARED_LIBRARY_PREFIX: " ${CMAKE_SHARED_LIBRARY_PREFIX})
message(STATUS "CMAKE_SHARED_LIBRARY_SUFFIX: " ${CMAKE_SHARED_LIBRARY_SUFFIX})
message(STATUS "CMAKE_STATIC_LIBRARY_PREFIX: " ${CMAKE_STATIC_LIBRARY_PREFIX})
message(STATUS "CMAKE_STATIC_LIBRARY_SUFFIX: " ${CMAKE_STATIC_LIBRARY_SUFFIX})

message(STATUS "CMAKE_FIND_LIBRARY_PREFIXES" ${CMAKE_FIND_LIBRARY_PREFIXES})
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
message(STATUS "CMAKE_FIND_LIBRARY_SUFFIXES" ${CMAKE_FIND_LIBRARY_SUFFIXES})

message(STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME})
message(STATUS "CMAKE_PROJECT_VERSION: " ${CMAKE_PROJECT_VERSION})
message(STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})
message(STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR})
message("")

#detect gsl library
set(gsl_path FALSE CACHE PATH "gsl package directory")
set(gsl_include_path FALSE CACHE PATH "gsl include direcoty")
set(gsl_lib_path FALSE CACHE PATH "gsl lib directory")
if (gsl_path)
    set(gsl_include_dir ${gsl_path}/include)
    set(gsl_lib_dir ${gsl_path}/lib)
    message(STATUS "Set gsl head files: " ${gsl_include_dir})
    message(STATUS "Set gsl lib files: " ${gsl_lib_dir})
elseif (gsl_include_path AND gsl_lib_path)
    set(gsl_include_dir ${gsl_include_path})
    set(gsl_lib_dir ${gsl_lib_path})
    message(STATUS "Set gsl head files: " ${gsl_include_dir})
    message(STATUS "Set gsl lib files: " ${gsl_lib_dir})
else()
    find_path(gsl_include_dir gsl/gsl_sf_bessel.h  ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES} ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
    find_library(gsl_lib_dir gsl ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES} ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES})
    if (gsl_include_dir AND gsl_lib_dir)
        get_filename_component(gsl_lib_dir ${gsl_lib_dir} DIRECTORY)
        message(STATUS "Find gsl head files: " ${gsl_include_dir})
        message(STATUS "Find gls lib files: " ${gsl_lib_dir})
    else ()
        message(SEND_ERROR "Not find gsl head files and libs.")
        message(SEND_ERROR "please specific them by gsl_dir or gsl_include_dir and gls_lib_dir")
        return()
    endif()
endif()


#detect testlib
set(testlib_path FALSE CACHE PATH "")
set(testlib_include_path FALSE CACHE PATH "")
set(testlib_lib_path FALSE CACHE PATH "")
if (testlib_path)
    set(testlib_include_dir ${testlib_path}/include)
    set(testlib_lib_dir ${testlib_path}/lib)
elseif (testlib_include_path AND testlib_lib_path)
    set(testlib_include_dir ${testlib_include_path})
    set(testlib_lib_dir ${testlib_lib_path})
else()
    find_path(testlib_include_dir multi.h ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES} ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
    find_library(testlib_lib_dir multi ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES} ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES})
    if (testlib_include_dir AND testlib_lib_dir)
        get_filename_component(testlib_lib_dir ${testlib_lib_dir} DIRECTORY)
        message(STATUS "testlib head files: " ${testlib_include_dir})
        message(STATUS "testlib lib files: " ${testlib_lib_dir})
    else()
        message(FATAL_ERROR "not found testlib")
    endif()
endif()


#add function_sub directory as subdirectory and make a lib
add_subdirectory(function_sub)


#Main executable
add_executable(test ${PRJ_SOURCE_DIR}/main.c ${PRJ_SOURCE_DIR}/add.c)


#build under different arch, system and compiler.
if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
    if (system STREQUAL "UNIX-like")
        message(STATUS "build for x86_64 UNIX-like")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            #compile and link
            target_compile_options(test PRIVATE "-O0")
            target_include_directories(test PRIVATE ${gsl_include_dir} PRIVATE ${testlib_include_dir})
            target_link_directories(test PRIVATE ${gsl_lib_dir} PRIVATE ${testlib_lib_dir})
            target_link_libraries(test -Wl,--start-group gsl.a gslcblas.a -Wl,--end-group multi.a sub m)

        elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        endif()
    elseif (system STREQUAL "macOS")
    elseif(system STREQUAL "windows")
    endif()
elseif (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64")
    message(" ")
else()
    message("Only x86_64 and aarch64 CPU was supported")
endif()


#installation
install(TARGETS test DESTINATION ${CMAKE_BINARY_DIR}/bin RUNTIME_DEPENDENCY_SET)
