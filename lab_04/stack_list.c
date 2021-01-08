//
// Created by Ivan Bogatyrev on 1/8/2021.
//


#include "stack_list.h"

void push_list(list_stack_t **head, int value)
{
    list_stack_t *tmp = malloc(sizeof(list_stack_t));
    if (tmp == NULL)
    {
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}


list_stack_t *pop_list(list_stack_t **head)
{
    list_stack_t *out;
    if ((*head) == NULL)
    {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}


size_t get_size_list(const list_stack_t *head)
{
    size_t size = 0;
    while (head)
    {
        size++;
        head = head->next;
    }
    return size;
}