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
    int *data;
    size_t size;
    size_t top;
} stack_t;

stack_t *create_arr_stack(size_t size);

void delete_arr_stack(stack_t **stack);

int resize_arr(stack_t *stack, size_t size);

void push_arr(stack_t *stack, const int *value);

void pop_arr(stack_t *stack, int *element);

int current_state_arr(stack_t *stack);

#endif //LAB_04_STACK_ARRAY_H
