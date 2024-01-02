add_library(GLFW include/GLFW/glfw3.h include/GLFW/glfw3native.h ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(GLFW ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a)

set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE C)
target_include_directories(GLFW PUBLIC include/)