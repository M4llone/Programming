cmake_minimum_required(VERSION 3.10)

project(RGR_interpreter C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")


add_executable(brainfuck main.c function_bf.c)
add_executable(test_runner test_bf.c function_bf.c)

target_link_libraries(test_runner cmocka)