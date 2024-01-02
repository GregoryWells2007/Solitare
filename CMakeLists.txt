cmake_minimum_required(VERSION 3.17)

project(SolitareAI)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.c" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(SolitareAI PUBLIC src/)

add_subdirectory(Depends/glfw/)
add_subdirectory(Depends/glad/)

target_link_libraries(${PROJECT_NAME} GLFW GLAD GLU GL dl X11 m)