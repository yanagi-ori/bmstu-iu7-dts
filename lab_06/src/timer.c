//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include "../inc/bin_tree.h"
#include "../inc/timer.h"
#include <stdint.h>

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t) high << 32) | low;

    return ticks;
}

uint64_t get_time(timer_t timer)
{
    return timer.end - timer.start;
}

uint64_t tree_search_performance_test(tree_node_t *tree, int *arr, int len)
{
    uint64_t start = tick();

    for (int i = 0; i < len; i++)
    {
        tree_find(tree, arr[i]);
    }

    uint64_t end = tick();

    return (end - start) / len;
}

float tree_search_cmp_avg(tree_node_t *tree, int *arr, int len)
{
    int cmps = 0;
    for (int i = 0; i < len; i++)
    {
        cmps += tree_find_cmp(tree, arr[i]);
    }
    return (float) cmps / (float )len;
}