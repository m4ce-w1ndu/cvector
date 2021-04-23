add_executable(${CMAKE_PROJECT_NAME}-darray dynarray_usage.c)
add_executable(${CMAKE_PROJECT_NAME}-push_back vector_push_back.c)

target_link_libraries(${CMAKE_PROJECT_NAME}-darray ${CMAKE_PROJECT_NAME}-lib)
target_link_libraries(${CMAKE_PROJECT_NAME}-push_back ${CMAKE_PROJECT_NAME}-lib)
