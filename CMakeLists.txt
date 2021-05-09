cmake_minimum_required(VERSION 3.10)
project(cvector C)

set(CMAKE_C_STANDARD 99)

# MSVC Static Multi Threaded Debug
if (MSVC)
	add_compile_options(
		$<$<CONFIG:>:/MT>
		$<$<CONFIG:Debug>:/MTd>
		$<$<CONFIG:Release>:/MT>
	)
	set(CMAKE_CXX_FLAGS_DEBUG "/TC /Wall /Od")
	set(CMAKE_CXX_FLAGS_RELEASE "/TC /02")
else()
    set(CMAKE_C_FLAGS_DEBUG "-Wall -g -O0 -fPIC")
    set(CMAKE_C_FLAGS_RELEASE "-Os -fPIC")
endif()

include_directories(src/include)

add_subdirectory(src)
add_subdirectory(examples)
