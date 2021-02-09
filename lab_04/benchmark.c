//
// Created by Ivan Bogatyrev on 1/22/2021.
//
#include <stdint.h>
#include <inttypes.h>
#include "benchmark.h"
#include <stdio.h>
#include <math.h>
#include "stack_list.h"
#include "stack_array.h"


uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r" (high), "=r" (low)
    ::"%rax", "%rbx", "%rcx", "%rdx"
    );

    uint64_t ticks = ((uint64_t) high << 32) | low;

    return ticks;
}


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

void calculate_eff(int size)
{
    int rc;
    uint64_t start, end;
    stack_list_t *list = NULL;
    stack_array_t *arr = create_arr_stack(sizeof(char *));
    int end_t = 10;
    start = tick();
    for (int j = 0; j < end_t; j++)
    {
        for (int i = 0; i < size; i++)
        {
            rc = push_arr(&arr, "1");
            if (rc != 0)
            {
                printf("ERROR WHILE INIT OF COMPARE %d\n", rc);
                return;
            }
        }
        for (int i = 0; i < size; i++)
        {
            char *element;
            rc = pop_arr(arr, &element);
            if (rc != 0)
            {
                printf("ERROR WHILE INIT OF COMPARE");
                return;
            }
        }
    }
    end = tick();
    uint64_t time_res1 = (end - start);
    start = tick();
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
    end = tick();
    uint64_t time_res2 = (end - start);
    size_t size_arr = arr->size * sizeof(char *) + sizeof(size_t) * 2;
    size_t size_list = size * sizeof(stack_list_t);
    printf("%7d | %20"PRId64 " | %17"PRId64 " |", size, time_res1, time_res2);
    printf(" %21"PRId64 "%% |     %8I64d       |    %8I64d       | %22I64d%% |\n",
           100 - time_res1 * 100 / time_res2,
           size_arr, size_list, 100 - size_arr * 100 / size_list);
}

void benchmark()
{
    puts("Processing time is time for push and time for pop");
    puts("   SIZE |    ARRAY STACK TICKS |  LIST STACK TICKS | ARRAY STACK EFFICIENCY "
         "| ARRAY STACK MEMORY | LIST STACK MEMORY | ARRAY MEMORY EFFICIENCY |");
    puts("----------------------------------------------------------------------------------"
         "--------------------------------------------------------------");
    calculate_eff(1);
    calculate_eff(10);
    calculate_eff(40);
    calculate_eff(41);
    calculate_eff(50);
    calculate_eff(60);
    calculate_eff(70);
    calculate_eff(79);
    calculate_eff(81);
    calculate_eff(100);
    calculate_eff(500);
    calculate_eff(1000);
    calculate_eff(5000);
    calculate_eff(10000);
    calculate_eff(100000);
}