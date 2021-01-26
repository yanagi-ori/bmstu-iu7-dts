#include <stdio.h>
#include "io.h"
#include "errors.h"
#include "benchmark.h"

int main()
{
    {
        printf("Types & Data Structures. Lab 4\n\nMenu:\n");
        printf("1. Array stack_array\n");
        printf("2. Linked List stack_array\n");
        printf("3. Efficiency comparison\n");
    }
    int tmp;
    int rc = scanf("%d", &tmp);
    if (rc == 1)
    {
        switch (tmp)
        {
            case 1:
                rc = array_stack_process();
                break;
            case 2:
                rc = list_stack_process();
                break;
            case 3:
                benchmark();
                rc = 0;
                break;
            default:
                fprintf(stderr, "Wrong menu item was entered\n");
                rc = IO_MENU_ITEM;
        }
        if (rc == STACK_OVERFLOW)
        {
            fprintf(stderr, "STACK OVERFLOW");
        }
        if (rc == STACK_UNDERFLOW)
        {
            fprintf(stderr, "STACK UNDERFLOW");
        }
        if (rc == MEMORY_ALLOCATION_ERROR)
        {
            fprintf(stderr, "Memory allocation error");
        }
    }
    else
    {
        printf("Entered number in incorrect format\n");
        rc = IO_ELEMENT;
    }

    return rc;
}
