#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/service.h"
#include "../queue_arr/array_queue.h"

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

                process(0, (void *) &queueArr1, (void *) &queueArr2);
                break;
            }
            case 2:
                break;
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
