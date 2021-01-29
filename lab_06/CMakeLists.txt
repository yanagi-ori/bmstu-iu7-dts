cmake_minimum_required(VERSION 3.17)
project(lab_06 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_06 src/main.c inc/errors.h src/io.c inc/io.h src/memory_management.c inc/memory_management.h src/timer.c inc/timer.h)