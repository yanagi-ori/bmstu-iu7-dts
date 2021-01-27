#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/service.h"
#include "../queue_arr/array_queue.h"
#include "../queue_list/list_queue.h"

int main()
{
    printf("LAB 5. QUEUES");

    printf("Choose the type of queues: \n"
           "1. Array;\n"
           "2. Linked list.\n");

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
