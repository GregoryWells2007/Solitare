add_library(CGLM ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcglm.a)
target_link_libraries(CGLM ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcglm.a)

set_target_properties(CGLM PROPERTIES LINKER_LANGUAGE C)
target_include_directories(CGLM PUBLIC include/)