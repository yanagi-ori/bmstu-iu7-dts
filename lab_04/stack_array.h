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
    void *data;
    size_t size;
    size_t top;
} stack_t;

stack_t *create_array_stack(size_t size);

void delete_array_stack(stack_t **stack);

int resize_array(stack_t *stack, size_t size);

void push_array(stack_t *stack, char *value);

void pop_array(stack_t *stack, char *element);

#endif //LAB_04_STACK_ARRAY_H
