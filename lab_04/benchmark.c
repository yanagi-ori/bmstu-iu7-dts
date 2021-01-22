//
// Created by Ivan Bogatyrev on 1/22/2021.
//

#include <time.h>
#include <math.h>
#include "stack_list.h"
#include "stack_array.h"
#include "benchmark.h"

int push_list_comp(stack_list_t **head)
{
    stack_list_t *tmp = malloc(sizeof(stack_list_t));
    if (tmp == NULL)
    {
        puts("STACK OVERFLOW!");
        return STACK_OVERFLOW;
    }
    tmp->next = *head;
    tmp->this = NULL;
    *head = tmp;
    return 0;
}


int pop_list_comp(stack_list_t **head)
{
    stack_list_t *out;
    if ((*head) == NULL)
    {
        puts("STACK UNDERFLOW!");
        return STACK_UNDERFLOW;
    }
    out = *head;
    *head = (*head)->next;
    free(out);
    return 0;
}

void calculate_eff(int size, int k)
{
    int rc;
    time_t start, end;
    stack_list_t *list = NULL;
    stack_array_t *arr = create_arr_stack(sizeof(int));
    int end_t = (int) pow(10, k);
    start = clock();
    for (int j = 0; j < end_t; j++)
    {
        for (int i = 0; i < size; i++)
        {
            rc = push_arr(&arr, 1);
            if (rc != 0)
            {
                printf("ERROR WHILE INIT OF COMPARE %d\n", rc);
                return;
            }
        }
        for (int i = 0; i < size; i++)
        {
            int element = 0;
            rc = pop_arr(arr, &element);
            if (rc != 0)
            {
                printf("ERROR WHILE INIT OF COMPARE");
                return;
            }
        }
    }
    end = clock();
    double time_res1 = ((double) (end - start) / CLOCKS_PER_SEC);
    start = clock();
    for (int j = 0; j < end_t; j++)
    {
        for (int i = 0; i < size; i++)
        {
            push_list_comp(&list);
        }

        for (int i = 0; i < size; i++)
        {
            pop_list_comp(&list);
        }
    }
    end = clock();
    double time_res2 = ((double) (end - start) / CLOCKS_PER_SEC);
    size_t size_arr = size * sizeof(int) + sizeof(int);
    size_t size_list = size * sizeof(stack_list_t);
    printf("%7d |       %4.2lfE-%d sec       |       %4.2lfE-%d sec    |", size, time_res1, k, time_res2, k);
    printf("          %4.2lf%%        |     %8I64d       |    %8I64d       |                     %I64d%%|\n",
           100 - time_res1 * 100 / time_res2,
           size_arr, size_list, 100 - size_arr * 100 / size_list);
}

void benchmark()
{
    puts("Processing time is time for push and time for pop");
    puts("   SIZE |     ARRAY STACK TIME    |    LIST STACK TIME   | ARRAY STACK EFFICIENCY "
         "| ARRAY STACK MEMORY | LIST STACK MEMORY | ARRAY MEMORY EFFICIENCY|");
    puts("-------------------------------------------------------------------------------"
         "----------------------------------------------------------------------");
    calculate_eff(10, 6);
    calculate_eff(50, 6);
    calculate_eff(100, 5);
    calculate_eff(500, 5);
    calculate_eff(1000, 4);
    calculate_eff(5000, 4);
    calculate_eff(10000, 3);
    calculate_eff(100000, 2);
}