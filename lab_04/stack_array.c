//
// Created by Ivan Bogatyrev on 1/3/2021.
//

#include <stdlib.h>
#include <string.h>
#include "stack_array.h"
#include "errors.h"

stack_t *create_arr_stack(size_t size)
{
    stack_t *out = NULL;
    out = malloc(sizeof(stack_t));
    if (out == NULL)
    {
        return NULL;
    }
    out->size = INIT_SIZE;
    out->data = malloc(out->size * size);
    if (out->data == NULL)
    {
        free(out);
        return NULL;
    }
    out->top = 0;
    return out;
}

void delete_arr_stack(stack_t **stack)
{
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}


int resize_arr(stack_t *stack, size_t size)
{
    stack->size *= MULTIPLIER;
    stack->data = realloc(stack->data, stack->size * size);
    if (stack->data == NULL)
    {
        return STACK_OVERFLOW;
    }
    return 0;
}


void push_arr(stack_t *stack, const int *value)
{
    if (stack->top >= stack->size)
    {
        resize_arr(stack, sizeof(int));
    }
    stack->data[stack->top] = *value;
    stack->top++;
}

void pop_arr(stack_t *stack, int *element)
{
    if (stack->top == 0)
    {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    int tmp = stack->data[stack->top];
    *element = tmp;
}

int current_state_arr(stack_t *stack)
{
    int size = stack->top;
    printf("Current state of stack: \n");
    for (int i = size - 1; i >= 0; i--)
    {
        printf("0x%x\n", stack->data[i]);
    }
    return 0;
}