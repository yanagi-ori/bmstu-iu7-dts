//
// Created by Ivan Bogatyrev on 1/25/2021.
//

#ifndef LAB_05_SERVICE_H
#define LAB_05_SERVICE_H

#include <stdbool.h>

typedef struct serviceApparatus
{
    bool isBusy;
    int passed;
    float timer;
    float process_time;
    int queue_1_amount;
    int queue_2_amount;
} service_apparatus_t;

typedef struct queue
{
    float wait_time;
    void *data;
} queue_t;

int process(int mode, void *data1, void *data2);

float float_rand(float min, float max);

#endif //LAB_05_SERVICE_H
