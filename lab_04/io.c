//
// Created by Ivan Bogatyrev on 1/8/2021.
//

#include "io.h"
#include "stack_array.h"
#include "stack_list.h"

void print_menu()
{
    printf("\n1. Push new element;\n");
    printf("2. Pop element\n");
    printf("3. Current state of the stack\n");
    printf("0. Stop program\n");
}

int array_stack_process()
{
    stack_t *stack = create_arr_stack(sizeof(int));
    if (stack == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    printf("Stack was successfully created.\n");

    int element = 0;
    int tmp = -1;
    while (tmp != 0)
    {
        print_menu();
        int rc = scanf("%d", &tmp);
        if (rc == 1)
        {
            switch (tmp)
            {
                case 1:
                    printf("Enter the memory address: \n");
                    rc = scanf("%x", &element);
                    if (rc != 1)
                    {
                        return IO_ELEMENT;
                    }
                    push_arr(stack, &element);
                    break;
                case 2:
                    pop_arr(stack, &element);
                    printf("0x%x", element);
                    break;
                case 3:
                    current_state_arr(stack);
                    break;
                case 0:
                    delete_arr_stack(&stack);
                    break;
                default:
                    delete_arr_stack(&stack);
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