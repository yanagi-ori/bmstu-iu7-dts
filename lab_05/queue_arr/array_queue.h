//
// Created by Ivan Bogatyrev on 1/25/2021.
//

#ifndef LAB_05_ARRAY_QUEUE_H
#define LAB_05_ARRAY_QUEUE_H

#include "../inc/main.h"


typedef struct queue_arr
{
    float upcoming;
    int begin, end;
    float queue[QUEUE_MAX_SIZE];
    int got;
} queue_arr_t;

void init_arr_queue(queue_arr_t *temp_queue);

short append_arr_queue(queue_arr_t *temp_queue, float temp_time);

float remove_arr_queue(queue_arr_t *temp_queue);

#endif //LAB_05_ARRAY_QUEUE_H
