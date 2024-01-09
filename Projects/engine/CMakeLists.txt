file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c")
add_library(engine ${SOURCE_FILES})

target_include_directories(engine PUBLIC ../../Depends/)
target_include_directories(engine PUBLIC ./)

# depends
add_subdirectory(../../Depends/glfw/ ${CMAKE_CURRENT_BINARY_DIR}/glfw/)
add_subdirectory(../../Depends/glad/ ${CMAKE_CURRENT_BINARY_DIR}/glad/)
add_subdirectory(../../Depends/cglm/ ${CMAKE_CURRENT_BINARY_DIR}/cglm/)

target_link_libraries(engine CGLM GLFW GLAD GLU GL dl X11 m)