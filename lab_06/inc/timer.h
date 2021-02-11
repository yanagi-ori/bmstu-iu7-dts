//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#ifndef LAB_06_TIMER_H
#define LAB_06_TIMER_H

#include <stdint.h>
#include "bin_tree.h"
#include "hash_table.h"

typedef struct timer
{
    uint64_t start;
    uint64_t end;
} timer_t;

uint64_t tick(void);

uint64_t get_time(timer_t timer);

uint64_t tree_search_performance_test(int *arr, int len, tree_node_t *(*func)(tree_node_t *));

float tree_search_cmp_avg(int *arr, int len, tree_node_t *(*func)(tree_node_t *));

uint64_t ht_search_performance_test(hash_table_t *ht, int *arr, int len, unsigned hash_func(int, unsigned));

float ht_search_cmp_avg(hash_table_t *ht, int *arr, int len, unsigned hash_func(int, unsigned));

#endif //LAB_06_TIMER_H
