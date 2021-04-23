add_library(${CMAKE_PROJECT_NAME}-lib vector.c include/vector.h)
target_link_libraries(${CMAKE_PROJECT_NAME}-lib m)
