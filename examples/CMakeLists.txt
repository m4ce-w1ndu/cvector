add_executable(${CMAKE_PROJECT_NAME}-e1 example1.c)
add_executable(${CMAKE_PROJECT_NAME}-push_back vpb.c)

target_link_libraries(${CMAKE_PROJECT_NAME}-e1 ${CMAKE_PROJECT_NAME}-lib)
target_link_libraries(${CMAKE_PROJECT_NAME}-push_back ${CMAKE_PROJECT_NAME}-lib)
