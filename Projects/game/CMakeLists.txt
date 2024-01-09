file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c")
add_executable(game ${SOURCE_FILES})
target_include_directories(game PUBLIC ../engine/)
target_include_directories(game PUBLIC ./)

target_link_libraries(game engine CGLM)

add_custom_command(TARGET game POST_BUILD
   COMMAND mv game ../../Solitare
)