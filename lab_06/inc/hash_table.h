//
// Created by Ivan Bogatyrev on 2/1/2021.
//

#ifndef LAB_06_HASH_TABLE_H
#define LAB_06_HASH_TABLE_H

#include <stdbool.h>

typedef struct hash_item
{
    int val;
    bool status;
} hash_item_t;

typedef struct hash_table
{
    hash_item_t *arr;
    unsigned int len;
} hash_table_t;

unsigned int next_prime(unsigned int num);

hash_table_t *ht_init(unsigned int len);

unsigned hash_func_simple(int val, unsigned int len);

unsigned hash_func_complicated(int val, unsigned int len);

void ht_clean(hash_table_t *ht);

int ht_insert(hash_table_t *ht, const int val, unsigned (*hash_func)(int, unsigned));

void ht_print(const hash_table_t *ht);

short ht_find(hash_table_t *ht, int key, unsigned (*hash_func)(int, unsigned));

#endif //LAB_06_HASH_TABLE_H
