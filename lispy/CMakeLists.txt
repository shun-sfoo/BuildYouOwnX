cmake_minimum_required(VERSION 3.14)

project(csapp LANGUAGES C)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.c)
target_link_libraries(main edit)
