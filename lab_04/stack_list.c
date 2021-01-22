//
// Created by Ivan Bogatyrev on 1/8/2021.
//


#include <stdio.h>
#include <stdbool.h>
#include "stack_list.h"

int push_list(stack_list_t **head)
{
    stack_list_t *tmp = malloc(sizeof(stack_list_t));
    if (tmp == NULL)
    {
        return STACK_OVERFLOW;
    }
    tmp->next = *head;
    tmp->this = tmp;
    *head = tmp;
    return 0;
}

int add_to_freed(stack_list_t **head, stack_list_t *new_item)
{
    stack_list_t *tmp = malloc(sizeof(stack_list_t));
    if (tmp == NULL)
    {
        return STACK_OVERFLOW;
    }
    tmp->next = *head;
    tmp->this = new_item->this;
    *head = tmp;

    return 0;
}

void find_in_freed(stack_list_t **head, stack_list_t *new_node_p)
{
    stack_list_t *temp = *head;
    if (temp && temp->this == new_node_p->this)
    {
        *head = temp->next;
        stack_list_t *tmp = temp;
        temp = temp->next;
        free(tmp);
    }
    while (temp && temp->next)
    {
        if (new_node_p->this == temp->next->this)
        {
            stack_list_t *tmp = temp->next->next;
            free(temp->next);
            temp->next = tmp;
            return;
        }
        temp = temp->next;
    }
}

stack_list_t *pop_list(stack_list_t **head)
{
    stack_list_t *out;
    if ((*head) == NULL)
    {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}


size_t get_size_list(const stack_list_t *head)
{
    size_t size = 0;
    while (head)
    {
        size++;
        head = head->next;
    }
    return size;
}

void print_stack_list(stack_list_t *head)
{
    stack_list_t *temp = head;
    bool flag = false;
    while (temp)
    {
        flag = true;
        printf("0x%p\n", temp->this);
        temp = temp->next;
    }

    if (!flag)
    {
        printf("The list is empty\n");
    }
}

void get_current_state_list(stack_list_t *stack, stack_list_t *freedAddresses)
{
    printf("Current state of stack: \n");
    print_stack_list(stack);

    printf("\nList of freed addresses: \n");
    print_stack_list(freedAddresses);
}


void free_list(stack_list_t *head)
{
    while (head)
    {
        stack_list_t *next = head->next;
        free(head);
        head = next;
    }
}