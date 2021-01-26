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
    stack_array_t *stack = create_arr_stack(sizeof(char *));
    if (stack == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    printf("Stack was successfully created.\n");

    int element = 0;
    int tmp = -1;
    int rc = 0;
    char address[100];
    char *temp_address = NULL;

    while (tmp != 0)
    {
        print_menu();
        scanf("%d", &tmp);

        switch (tmp)
        {
            case 1:
                printf("Enter the memory address: \n");
                rc = scanf("%99s", address);
                if (rc != 1)
                {
                    return IO_ELEMENT;
                }
                push_arr(&stack, address);
                break;
            case 2:
                rc = pop_arr(stack, &temp_address);
                if (rc != 0)
                {
                    return rc;
                }
                printf("0x%s\n", temp_address);
                free(temp_address);
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

    return 0;
}

int list_stack_process()
{
    stack_list_t *stack = NULL;
    stack_list_t *node;
    stack_list_t *head = NULL;
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
                    rc = push_list(&stack);
                    if (rc != 0)
                    {
                        return rc;
                    }
                    find_in_freed(&head, stack);
                    break;
                case 2:
                    node = pop_list(&stack);
                    printf("0x%p\n", node->this);
                    add_to_freed(&head, node);
                    free(node);
                    break;
                case 3:
                    get_current_state_list(stack, head);
                    break;
                case 0:
                    free_list(stack);
                    free_list(head);
                    break;
                default:
                    free_list(stack);
                    free_list(head);
                    return IO_MENU_ITEM;
            }
        }
    }

    return 0;
}