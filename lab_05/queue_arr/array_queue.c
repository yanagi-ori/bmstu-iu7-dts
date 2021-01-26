//
// Created by Ivan Bogatyrev on 1/25/2021.
//

#include <stdio.h>
#include "array_queue.h"
#include "../inc/errors.h"

void init_arr_queue(queue_arr_t *temp_queue)
{
    temp_queue->begin = 0;
    temp_queue->end = 0;
    temp_queue->upcoming = (float) 0.;
    temp_queue->got = 0;
}

short append_arr_queue(queue_arr_t *temp_queue, float temp_time)
{
    if (temp_queue->end < QUEUE_MAX_SIZE - 1)
    {
        temp_queue->queue[temp_queue->end++] = temp_time;
    }
    else
    {
        printf("Queue overflow\n");
        return QUEUE_OVERFLOW;
    }
}

float remove_arr_queue(queue_arr_t *temp_queue)
{
    float temp = temp_queue->queue[0];
    if (temp_queue->begin == temp_queue->end)
    {
        fprintf(stderr, "Queue underflow\n");
        return QUEUE_UNDERFLOW;
    }
    for (int h = temp_queue->begin; h < temp_queue->end; h++)
    {
        temp_queue->queue[h] = temp_queue->queue[h + 1];
    }
    temp_queue->end -= 1;
    return temp;
}