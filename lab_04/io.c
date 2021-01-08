//
// Created by Ivan Bogatyrev on 1/8/2021.
//

#include "io.h"
#include "stack_array.h"
#include "stack_list.h"

void print_menu()
{
    printf("1. Push new element;\n");
    printf("2. Pop element\n");
    printf("3. Current state of the stack\n");
    printf("0. Stop program\n");
}

int array_stack_process()
{
    stack_t *stack = create_array_stack(sizeof(char) * 17);
    if (stack == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    printf("Stack was successfully created.\n");

    char element[17];
    int tmp = -1;
    while (tmp != 0)
    {
        int rc = scanf("%d", &tmp);
        if (rc == 1)
        {
            switch (tmp)
            {
                case 1:
                    printf("Enter the memory address: \n");
                    rc = scanf("%16s", element);
                    if (rc != 1)
                    {
                        return IO_ELEMENT;
                    }
                    push_array(stack, element);
                case 2:
                    pop_array(stack, element);
                    printf("%s", element);
                case 3:
                    //todo: current state
                case 0:
                    delete_array_stack(&stack);
                    break;
                default:
                    delete_array_stack(&stack);
                    return IO_MENU_ITEM;
            }
        }
        else
        {
            return IO_MENU_ITEM;
        }
    }

    return 0;
}

int list_stack_process()
{

    return 0;
}