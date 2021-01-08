//
// Created by Ivan Bogatyrev on 1/3/2021.
//

#include <stdlib.h>
#include <string.h>
#include "stack_array.h"
#include "errors.h"

stack_t *create_array_stack(size_t size)
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

void delete_array_stack(stack_t **stack)
{
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}


int resize_array(stack_t *stack, size_t size)
{
    stack->size *= MULTIPLIER;
    stack->data = realloc(stack->data, stack->size * size);
    if (stack->data == NULL)
    {
        return STACK_OVERFLOW;
    }
    return 0;
}


void push_array(stack_t *stack, char *value)
{
    if (stack->top >= stack->size)
    {
        resize_array(stack, sizeof(char) * 17);
    }

    strcpy(&stack->data[stack->top], value);
    stack->top++;
}

void pop_array(stack_t *stack, char *element)
{
    if (stack->top == 0)
    {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    strcpy(element, &stack->data[stack->top]);
}


void implode_array(stack_t *stack, size_t type)
{
    stack->size = stack->top;
    stack->data = realloc(stack->data, stack->size * type);
}

