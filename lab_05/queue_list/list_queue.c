//
// Created by Ivan Bogatyrev on 1/27/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "list_queue.h"
#include "../inc/errors.h"

node_t *init_node(float data)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
    {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void init_list_queue(queue_list_t *queueList)
{
    queueList->begin = 0;
    queueList->end = 0;
    queueList->upcoming = (float) 0.;
    queueList->got = 0;
    queueList->head = malloc(sizeof(node_t *));
    *queueList->head = NULL;
}


short append_list_queue(queue_list_t *queueList, float data)
{
    node_t *node = init_node(data);

    node_t *temp_node = *queueList->head;
    if (temp_node)
    {
        while (temp_node->next != NULL)
        {
            temp_node = temp_node->next;
        }
        temp_node->next = node;
    }
    else
    {
        *queueList->head = node;
    }
    queueList->end++;
    return 0;
}

float remove_list_queue(queue_list_t *queueList)
{
    if ((*queueList->head) == NULL)
    {
        return QUEUE_UNDERFLOW;
    }
    node_t *node;
    node = (*queueList->head)->next;
    free(*queueList->head);
    *queueList->head = node;
    queueList->end--;
    return 0;
}


void get_added_queue_list(queue_list_t *queueList, short queue_num)
{
    node_t *node = *queueList->head;

    while (node->next != NULL)
    {
        node = node->next;
    }
    printf("added to queue %d: 0x%p\n", queue_num, node);
}

void get_deleted_queue_list(queue_list_t *queueList, short queue_num)
{
    printf("freed from queue %d: 0x%p\n", queue_num, *queueList->head);
}
