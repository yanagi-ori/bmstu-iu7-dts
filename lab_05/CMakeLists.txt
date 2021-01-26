cmake_minimum_required(VERSION 3.17)
project(lab_05 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_05 src/main.c src/service.c inc/service.h inc/errors.h queue_arr/array_queue.c queue_arr/array_queue.h inc/main.h)