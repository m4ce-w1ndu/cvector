add_library(cvector vector.c include/vector.h)

if (NOT MSVC)
    target_link_libraries(cvector m)
endif()

install(TARGETS cvector DESTINATION lib)
install(FILES include/vector.h DESTINATION include)
