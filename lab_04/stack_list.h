//
// Created by Ivan Bogatyrev on 1/8/2021.
//

#ifndef LAB_04_STACK_LIST_H
#define LAB_04_STACK_LIST_H

#include <stdlib.h>
#include "errors.h"

typedef struct node
{
    struct node *this;
    struct node *next;
} stack_list_t;


int push_list(stack_list_t **head);

stack_list_t *pop_list(stack_list_t **head);

void free_list(stack_list_t *head);

int add_to_freed(stack_list_t **head, stack_list_t *new_item);

void find_in_freed(stack_list_t **head, stack_list_t *new_node_p);

void get_current_state_list(stack_list_t *stack, stack_list_t *freedAddresses);

#endif //LAB_04_STACK_LIST_H
