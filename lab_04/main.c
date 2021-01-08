#include <stdio.h>
#include "io.h"
#include "errors.h"

int main()
{
    {
        printf("Types & Data Structures. Lab 4\n\nMenu:\n");
        printf("1. Array stack_array\n");
        printf("2. Linked List stack_array\n");
    }
    int tmp;
    int rc = scanf("%d", &tmp);
    if (rc == 1)
    {
        rc = 0;
        switch (tmp)
        {
            case 1:
                rc = array_stack_process(); //todo: done, check?
                break;
            case 2:
                rc = list_stack_process();
                break;
            default:
                fprintf(stderr, "Wrong menu item was entered\n");
                return IO_MENU_ITEM;
        }
        if (rc != 0)
        {
            printf("Entered number in incorrect format\n");
            return IO_ELEMENT;
        }
    }

    return 0;
}
