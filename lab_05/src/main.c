#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/errors.h"
#include "../inc/service.h"
#include "../queue_arr/array_queue.h"
#include "../queue_list/list_queue.h"
#include "../inc/timer.h"

int main()
{
    printf("LAB 5. QUEUES\n");

    printf("Choose the type of queues: \n"
           "1. Array;\n"
           "2. Linked list;\n"
           "3. performance test.\n");

    int rc, item;
    struct timespec start_time_s, end_time_s;

    rc = scanf("%d", &item);
    if (rc == 1)
    {

        switch (item)
        {
            case 1:
            {
                queue_arr_t queueArr1;
                init_arr_queue(&queueArr1);
                queue_arr_t queueArr2;
                init_arr_queue(&queueArr2);
                printf("Set the visibility of the freed addresses: \n0 - No; 1 - Yes\n");
                int temp;
                rc = scanf("%d", &temp);
                bool additional_info;
                if (rc != 1)
                {
                    return IO_ERROR;
                }
                else if (temp == 1)
                {
                    additional_info = true;
                }
                else if (temp == 0)
                {
                    additional_info = false;
                }
                else
                {
                    fprintf(stderr, "Wrong menu item");
                    return IO_ERROR;
                }
                START_MEASURING()
                rc = process(0, (void *) &queueArr1, (void *) &queueArr2, additional_info);
                if (rc == QUEUE_UNDERFLOW)
                {
                    fprintf(stderr, "Underflow happened");
                }
                else if (rc == QUEUE_OVERFLOW)
                {
                    fprintf(stderr, "Overflow happened");
                }
                END_MEASURING()
                SHOW_TIME("Program execution time: ");
                break;
            }
            case 2:
            {
                queue_list_t queueList1;
                queue_list_t queueList2;
                init_list_queue(&queueList1);
                init_list_queue(&queueList2);

                printf("Set the visibility of the freed addresses: \n0 - No; 1 - Yes\n");
                int temp;
                rc = scanf("%d", &temp);
                bool additional_info;
                if (rc != 1)
                {
                    return IO_ERROR;
                }
                else if (temp == 1)
                {
                    additional_info = true;
                }
                else if (temp == 0)
                {
                    additional_info = false;
                }
                else
                {
                    fprintf(stderr, "Wrong menu item");
                    return IO_ERROR;
                }
                START_MEASURING()
                rc = process(1, (void *) &queueList1, (void *) &queueList2, additional_info);
                if (rc == QUEUE_UNDERFLOW)
                {
                    fprintf(stderr, "Underflow happened");
                }
                else if (rc == QUEUE_OVERFLOW)
                {
                    fprintf(stderr, "Overflow happened");
                }
                END_MEASURING()

                SHOW_TIME("Program execution time: ");
                free_list(*queueList1.head);
                free_list(*queueList2.head);
                break;
            }
            case 3:
            {
                queue_arr_t queueArr;
                init_arr_queue(&queueArr);
                queue_list_t queueList;
                init_list_queue(&queueList);
                uint64_t start;
                uint64_t end;
                const short iterations = 1000;

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    append_arr_queue(&queueArr, (float) i);
                }
                end = tick();
                printf("Append in array: %lu ticks in average\n", (end - start) / iterations);

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    append_list_queue(&queueList, (float) i);
                }
                end = tick();
                printf("Append in list: %lu ticks in average\n", (end - start) / iterations);

                printf("Size of array realization %zu Bytes in average\n",
                       sizeof(queueArr) / 1000);
                printf("Size of list realization %zu Bytes in average\n",
                       sizeof(queueList) + 999 * (sizeof(node_t)) / 1000);

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    remove_arr_queue(&queueArr);
                }
                end = tick();
                printf("Pop in array: %lu ticks in average\n", (end - start) / iterations);

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    remove_list_queue(&queueList);
                }
                end = tick();
                printf("Pop in list: %lu ticks in average\n", (end - start) / iterations);

                free_list(*queueList.head);

                break;
            }
            default:
                fprintf(stderr, "Wrong menu item was entered.");
                return IO_ERROR;
        }
    }
    else
    {
        fprintf(stderr, "Wrong menu item was entered.");
        return IO_ERROR;
    }

    return 0;
}
