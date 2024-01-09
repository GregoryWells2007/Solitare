cmake_minimum_required(VERSION 3.17)

project(Solitare)

# project wide depends
add_subdirectory(Depends/cglm/)

# projects
add_subdirectory(Projects/game/)
add_subdirectory(Projects/engine/)