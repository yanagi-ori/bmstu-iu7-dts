cmake_minimum_required(VERSION 3.17)
project(lab_07 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_07 src/main.c inc/errors.h src/io.c inc/io.h src/graph.c inc/graph.h "src/memory_management.c" "inc/memory_management.h" src/table.c inc/table.h)