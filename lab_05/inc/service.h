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
    int queue_1_passed;
    int queue_2_passed;
    int q1_len_sum;
    int q2_len_sum;
    int measurements;
} service_apparatus_t;

int process(int mode, void *queue1, void *data2, bool additional_output);

float float_rand(float min, float max);

#endif //LAB_05_SERVICE_H
