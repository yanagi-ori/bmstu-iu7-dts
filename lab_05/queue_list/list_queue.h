//
// Created by Ivan Bogatyrev on 1/27/2021.
//

#ifndef LAB_05_LIST_QUEUE_H
#define LAB_05_LIST_QUEUE_H

typedef struct node
{
    float data;
    struct node *next;
} node_t;

typedef struct queue_list
{
    float upcoming;
    int begin, end;
    node_t **head;
    int got;
} queue_list_t;

void init_list_queue(queue_list_t *queueList);

short append_list_queue(queue_list_t *queueList, float data);

float remove_list_queue(queue_list_t *queueList);

void get_added_queue_list(queue_list_t *queueArr, short queue_num);

void get_deleted_queue_list(queue_list_t *queueArr, short queue_num);


#endif //LAB_05_LIST_QUEUE_H
