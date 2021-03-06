//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include "../inc/bin_tree.h"
#include "../inc/hash_table.h"
#include "../inc/timer.h"
#include "../inc/errors.h"
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

uint64_t tree_search_performance_test(int *arr, int len, tree_node_t *(*func)(tree_node_t *))
{
    bool deleted = false;
    uint64_t total = 0;
    for (int i = 0; i < len; i++)
    {
        tree_node_t *bin_tree = NULL;
        timer_t timer;
        timer.start = tick();
        for (int j = 0; j < len; j++)
        {
            if (tree_find(bin_tree, arr[j]) == NULL)
            {
                bin_tree = tree_insert(bin_tree, arr[j], func);
            }
        }

        uint64_t start = tick();

        int cmp = 1;

        tree_delete_cmp(bin_tree, arr[i], &cmp, &deleted);

        uint64_t end = tick();

        total += end - start;

    }

    return (total) / len;
}

float tree_search_cmp_avg(int *arr, int len, tree_node_t *(*func)(tree_node_t *))
{
    bool deleted = false;
    int cmps = 0;
    for (int i = 0; i < len; i++)
    {
        tree_node_t *bin_tree = NULL;
        timer_t timer;
        timer.start = tick();
        for (int j = 0; j < len; j++)
        {
            if (tree_find(bin_tree, arr[j]) == NULL)
            {
                bin_tree = tree_insert(bin_tree, arr[j], func);
            }
        }

        int temp = 1;

        tree_delete_cmp(bin_tree, arr[i], &temp, &deleted);

        cmps += temp;
    }

    return (float) cmps / (float) len;
}

uint64_t htDelPerformanceTest(int *arr, int len, unsigned int (*hash_func)(int, unsigned int))
{
    uint64_t total = 0;

    for (int i = 0; i < len; i++)
    {
        hash_table_t *table = ht_init(len);
        for (int j = 0; j < len; j++)
        {
            int tmp_coll = ht_insert(table, arr[j], hash_func_simple);
            if (tmp_coll == HASH_END)
            {
                return HASH_END;
            }
        }

        uint64_t start = tick();

        ht_find(table, arr[i], hash_func);

        uint64_t end = tick();

        total += end - start;
        ht_clean(table);
    }

    return (total) / len;
}

float htDelCmpAvg(int *arr, int len, unsigned int (*hash_func)(int, unsigned int))
{
    int cmps = 0;
    for (int i = 0; i < len; i++)
    {
        hash_table_t *table = ht_init(len);
        for (int j = 0; j < len; j++)
        {
            ht_insert(table, arr[j], hash_func_simple);
        }

        int temp = ht_find(table, arr[i], hash_func);
        if (temp > 0)
        {
            cmps += temp;
        }

        ht_clean(table);
    }

    return (float) cmps / (float) len;
}