file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c")
add_library(engine ${SOURCE_FILES})

target_include_directories(engine PUBLIC ../../Depends/)
target_include_directories(engine PUBLIC Depends/)
target_include_directories(engine PUBLIC ./)

# depends
add_subdirectory(Depends/glad/)
add_subdirectory(Depends/glfw/)

target_link_libraries(engine CGLM GLFW GLAD GL dl X11 m)