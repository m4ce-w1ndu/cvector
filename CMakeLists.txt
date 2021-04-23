cmake_minimum_required(VERSION 3.10)
project(cvector C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "-Wall -g -O0")
set(CMAKE_C_FLAGS_RELEASE "-Os -fpic")

include_directories(src/include)

add_subdirectory(src)
add_subdirectory(examples)
