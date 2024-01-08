cmake_minimum_required(VERSION 3.17)

project(Solitare)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.c" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(Solitare PUBLIC src/)

# depends
add_subdirectory(Depends/glfw/)
add_subdirectory(Depends/glad/)
add_subdirectory(Depends/cglm/)
target_include_directories(Solitare PUBLIC Depends/)

target_link_libraries(${PROJECT_NAME} CGLM GLFW GLAD GLU GL dl X11 m)