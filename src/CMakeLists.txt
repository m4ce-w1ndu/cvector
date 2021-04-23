add_library(${CMAKE_PROJECT_NAME}-lib vector.c include/vector.h)
target_link_libraries(${CMAKE_PROJECT_NAME}-lib m)
install(TARGETS ${CMAKE_PROJECT_NAME}-lib DESTINATION lib)
install(FILES include/vector.h DESTINATION include)
