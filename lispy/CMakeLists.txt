cmake_minimum_required(VERSION 3.14)

project(lispy LANGUAGES C)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(mpc)

add_executable(lispy main.c)
target_link_libraries(lispy edit mpc)

