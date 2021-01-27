//
// Created by Ivan Bogatyrev on 1/25/2021.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "../inc/service.h"
#include "../inc/main.h"
#include "../queue_arr/array_queue.h"


float float_rand(float min, float max)
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    //printf("scale %f \n", scale);
    return min + scale * (max - min);      /* [min, max] */
}


void init_service_apparatus(service_apparatus_t *serviceApparatus)
{
    serviceApparatus->isBusy = false;
    serviceApparatus->passed = 0;
    serviceApparatus->timer = (float) 0.;
    serviceApparatus->process_time = (float) -1;
    serviceApparatus->queue_1_passed = 0;
    serviceApparatus->queue_2_passed = 0;
    serviceApparatus->q1_len_sum = 0;
    serviceApparatus->q2_len_sum = 0;
    serviceApparatus->measurements = 0;
}

void next_step(float *a, float *b, service_apparatus_t *apparatus)
{
    if (apparatus->process_time > 0)
    {
        float min = *a;

        if (*b < min)
        {
            min = *b;
        }
        if (apparatus->process_time < min)
        {
            min = apparatus->process_time;
        }

        *a -= min;
        *b -= min;
        apparatus->process_time -= min;
        apparatus->timer += min;
    }

    else
    {
        if (*a < *b)
        {
            apparatus->timer += *a;
            *b -= *a;
            *a -= *a;
        }
        else
        {
            apparatus->timer += *b;
            *a -= *b;
            *b -= *b;
        }
    }
}

void get_samples(service_apparatus_t *serviceApparatus, int len1, int len2)
{
    serviceApparatus->q1_len_sum += len1;
    serviceApparatus->q2_len_sum += len2;
    serviceApparatus->measurements++;
}

float get_average(service_apparatus_t serviceApparatus, int queue)
{
    if (queue == 0)
    {
        return ((float) serviceApparatus.q1_len_sum / (float) serviceApparatus.measurements);
    }
    else if (queue == 1)
    {
        return ((float) serviceApparatus.q2_len_sum / (float) serviceApparatus.measurements);
    }
    else
    {
        return -1;
    }
}

int process(int mode, void *data1, void *data2)
{
    srand(time(NULL));
    if (mode == 0)
    {
        queue_arr_t *queue1 = (queue_arr_t *) data1;
        queue_arr_t *queue2 = (queue_arr_t *) data2;

        service_apparatus_t serviceApparatus;
        init_service_apparatus(&serviceApparatus);

        queue1->upcoming = float_rand(T1_MIN, T1_MAX);
        queue2->upcoming = float_rand(T2_MIN, T2_MAX);

        short rule;
        if (queue1->upcoming > queue2->upcoming)
        {
            rule = 1;
        }
        else
        {
            rule = 0;
        }

        while (serviceApparatus.queue_1_passed < 1000)
        {
            next_step(&queue1->upcoming, &queue2->upcoming, &serviceApparatus);
            if (queue1->upcoming == 0)
            {
                queue1->got++;
                append_arr_queue(queue1, float_rand(T3_MIN, T3_MAX));
                get_samples(&serviceApparatus, queue1->end - queue1->begin, queue2->end - queue2->begin);
                queue1->upcoming = float_rand(T1_MIN, T1_MAX);
            }
            if (queue2->upcoming == 0)
            {
                queue2->got++;
                append_arr_queue(queue2, float_rand(T4_MIN, T4_MAX));
                get_samples(&serviceApparatus, queue1->end - queue1->begin, queue2->end - queue2->begin);
                queue2->upcoming = float_rand(T2_MIN, T2_MAX);
            }
            if (serviceApparatus.process_time == 0)
            {
                serviceApparatus.isBusy = false;
                serviceApparatus.passed++;
            }
            if (!serviceApparatus.isBusy)
            {
                if (rule == 0)
                {
                    if ((queue1->begin != queue1->end))
                    {
                        serviceApparatus.process_time = remove_arr_queue(queue1);
                        get_samples(&serviceApparatus, queue1->end - queue1->begin, queue2->end - queue2->begin);
                        serviceApparatus.isBusy = true;
                        serviceApparatus.queue_1_passed++;

                    }
                    else if (queue2->begin != queue2->end)
                    {
                        rule = 1;
                        serviceApparatus.process_time = remove_arr_queue(queue2);
                        get_samples(&serviceApparatus, queue1->end - queue1->begin, queue2->end - queue2->begin);
                        serviceApparatus.isBusy = true;
                        serviceApparatus.queue_2_passed++;
                    }
                    else
                    {
                        serviceApparatus.process_time = -1;
                    }
                }
                else
                {
                    if ((queue2->begin != queue2->end))
                    {
                        serviceApparatus.process_time = remove_arr_queue(queue2);
                        get_samples(&serviceApparatus, queue1->end - queue1->begin, queue2->end - queue2->begin);
                        serviceApparatus.isBusy = true;
                        serviceApparatus.queue_2_passed++;

                    }
                    else if (queue1->begin != queue1->end)
                    {
                        rule = 0;
                        serviceApparatus.process_time = remove_arr_queue(queue1);
                        get_samples(&serviceApparatus, queue1->end - queue1->begin, queue2->end - queue2->begin);
                        serviceApparatus.isBusy = true;
                        serviceApparatus.queue_1_passed++;
                    }
                    else
                    {
                        serviceApparatus.process_time = -1;
                    }
                }
            }
            if (serviceApparatus.passed % 100 == 0 && serviceApparatus.passed > 0)
            {
                printf(
                        "----------------------------------------------------\n"
                        "Passed tickets: \t\t%d\n"
                        "Passed tickets from 1 queue: \t%d\n"
                        "Current queue 1 length: \t%d\n"
                        "Current queue 2 length: \t%d\n"
                        "Average queue 1 length: \t%lf\n"
                        "Average queue 2 length: \t%lf\n"
                        "----------------------------------------------------\n",
                        serviceApparatus.passed,
                        serviceApparatus.queue_1_passed,
                        queue1->end - queue1->begin,
                        queue2->end - queue2->begin,
                        get_average(serviceApparatus, 0),
                        get_average(serviceApparatus, 1)
                );
            }
        }

        printf(
                "Total simulation time: \t%lf\n"
                "Requests from 1st queue received: \t%d\n"
                "Requests from 1st queue processed: \t%d\n"
                "Requests from 2nd queue received: \t%d\n"
                "Requests from 2nd queue processed: \t%d\n",
                serviceApparatus.timer,
                queue1->got,
                serviceApparatus.queue_1_passed,
                queue2->got,
                serviceApparatus.queue_2_passed
        );


        /*
        printf("%d %d\n", queue1->got, queue2->got);
        printf("%lf %d %d\n",
               serviceApparatus.timer, serviceApparatus.queue_1_passed, serviceApparatus.queue_2_passed);

        for (int i = queue1->begin; i < queue1->end; i++)
        {
            printf("%lf ", queue1->queue[i]);
        }
        printf("\n");
        for (int i = queue2->begin; i < queue2->end; i++)
        {
            printf("%lf ", queue2->queue[i]);
        }
        */
    }


    return 0;
}



