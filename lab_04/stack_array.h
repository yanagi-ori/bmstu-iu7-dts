//
// Created by Ivan Bogatyrev on 1/3/2021.
//

#ifndef LAB_04_STACK_ARRAY_H
#define LAB_04_STACK_ARRAY_H

#include <stdio.h>

#define INIT_SIZE 5
#define MULTIPLIER 2

typedef struct stack_array
{
    size_t size;
    size_t top;
    int *data;
} stack_array_t;

stack_array_t *create_arr_stack(size_t size);

void delete_arr_stack(stack_array_t **stack);

int resize_arr(stack_array_t **stack, size_t size);

int push_arr(stack_array_t **stack, int value);

int pop_arr(stack_array_t *stack, int *element);

int current_state_arr(stack_array_t *stack);

#endif //LAB_04_STACK_ARRAY_H
