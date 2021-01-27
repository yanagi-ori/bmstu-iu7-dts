#include <stdio.h>
#include <stdint.h>
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
                bool addit_info;
                if (rc != 1)
                {
                    return IO_ERROR;
                }
                else if (temp == 1)
                {
                    addit_info = true;
                }
                else if (temp == 0)
                {
                    addit_info = false;
                }
                else
                {
                    fprintf(stderr, "Wrong menu item");
                    return IO_ERROR;
                }
                process(0, (void *) &queueArr1, (void *) &queueArr2, addit_info);
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
                bool addit_info;
                if (rc != 1)
                {
                    return IO_ERROR;
                }
                else if (temp == 1)
                {
                    addit_info = true;
                }
                else if (temp == 0)
                {
                    addit_info = false;
                }
                else
                {
                    fprintf(stderr, "Wrong menu item");
                    return IO_ERROR;
                }

                process(1, (void *) &queueList1, (void *) &queueList2, addit_info);
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
                uint64_t start = 0;
                uint64_t end = 0;
                uint64_t time_res = 0;
                const short iterations = 100;

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    append_arr_queue(&queueArr, (float) i);
                }
                end = tick();
                printf("Append in array: %llu ticks in average\n", (end - start) / iterations);

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    append_list_queue(&queueList, (float) i);
                }
                end = tick();
                printf("Append in list: %llu ticks in average\n", (end - start) / iterations);

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    remove_arr_queue(&queueArr);
                }
                end = tick();
                printf("Pop in array: %llu ticks in average\n", (end - start) / iterations);

                start = tick();
                for (short i = 0; i < iterations; i++)
                {
                    remove_list_queue(&queueList);
                }
                end = tick();
                printf("Pop in list: %llu ticks in average\n", (end - start) / iterations);

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
