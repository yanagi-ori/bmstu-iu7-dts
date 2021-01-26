//
// Created by Ivan Bogatyrev on 1/3/2021.
//

#include <stdlib.h>
#include <string.h>
#include "stack_array.h"
#include "errors.h"

stack_array_t *create_arr_stack(size_t size)
{
    stack_array_t *out = NULL;
    out = malloc(sizeof(stack_array_t));
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

void delete_arr_stack(stack_array_t **stack)
{
    for (int i = 0; i < (*stack)->top; i++)
    {
        free((*stack)->data[i]);
    }
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}


int resize_arr(stack_array_t **stack, size_t size)
{
    (*stack)->size *= MULTIPLIER;
    (*stack)->data = realloc((*stack)->data, (*stack)->size * size);
    if ((*stack)->data == NULL)
    {
        return STACK_OVERFLOW;
    }
    return 0;
}


int push_arr(stack_array_t **stack, char value[100])
{
    if ((*stack)->top >= (*stack)->size)
    {
        if (resize_arr(stack, sizeof(char *)) != 0)
        {
            return MEMORY_ALLOCATION_ERROR;
        }
    }
    (*stack)->data[(*stack)->top] = strdup(value);
    (*stack)->top++;
    return 0;
}

int pop_arr(stack_array_t *stack, char **element)
{
    if (stack->top == 0)
    {
        return (STACK_UNDERFLOW);
    }
    stack->top--;
    char *tmp = stack->data[stack->top];
    *element = tmp;
    return 0;
}

int current_state_arr(stack_array_t *stack)
{
    int size = stack->top;
    printf("Current state of stack: \n");
    for (int i = size - 1; i >= 0; i--)
    {
        printf("0x%s\n", stack->data[i]);
    }
    return 0;
}