add_library(${CMAKE_PROJECT_NAME} vector.c include/vector.h)
target_link_libraries(${CMAKE_PROJECT_NAME} m)
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(FILES include/vector.h DESTINATION include)
