cmake_minimum_required(VERSION 3.10)
project(cvector C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_DEBUG "-Wall -g -O0 -fPIC -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "-Os -fPIC")

include_directories(src/include)

add_subdirectory(src)
add_subdirectory(examples)
