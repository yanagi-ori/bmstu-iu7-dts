//
// Created by Ivan Bogatyrev on 2/1/2021.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/hash_table.h"
#include "../inc/errors.h"

int is_prime(int num)
{
    if (num < 2)
    {
        return 0;
    }

    if (num % 2 == 0)
    {
        return 0;
    }

    for (int i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

unsigned int next_prime(unsigned int num)
{
    unsigned int new = num;

    while (is_prime((int) new) == 0)
    {
        new++;
    }

    return new;
}

hash_table_t *ht_init(unsigned int len)
{
    hash_table_t *ht = malloc(sizeof(hash_table_t));

    if (ht == NULL)
    {
        return NULL;
    }

    ht->arr = calloc(1, sizeof(hash_item_t) * len);
    if (ht->arr == NULL)
    {
        free(ht);
        return NULL;
    }

    ht->len = len;

    //printf("Memory allocated: %zu\n", sizeof(hash_item_t) * len + sizeof(hash_table_t));

    return ht;
}

unsigned hash_func_simple(int val, unsigned int len)
{
    unsigned int new = val;

    return new % len;
}

unsigned hash_func_complicated(int val, unsigned int len)
{
    int key = abs(val);
    unsigned N = len;
    double A = 0.618033;
    int h = N * fmod(key * A, 1);
    return h % len;
}

void ht_clean(hash_table_t *ht)
{
    if (ht)
    {
        if (ht->arr)
        {
            free(ht->arr);
        }

        free(ht);
    }
}

int find_free_element(hash_table_t *ht, unsigned *ind, int *i, int val)
{
    while (*ind < ht->len && ht->arr[*ind].status && ht->arr[*ind].val != val)
    {
        (*ind)++;
        (*i)++;
    }
    if (*ind >= ht->len)
    {
        return HASH_END;
    }
    else
    {
        return 0;
    }
}


int ht_insert(hash_table_t *ht, const int val, unsigned (*hash_func)(int, unsigned))
{
    int res;

    if (hash_func == NULL)
    {
        return INVALID_HASH_FUNC;
    }

    unsigned ind = hash_func(val, ht->len);

    //printf("hash[%d] = %d (%d)\n", ind, ht->arr[ind].val, val);

    if (ht->arr[ind].val == val)
    {
        //ht->arr[ind].status = true;
        ht->arr[ind].status = false;
        return 0;
    }
    int coll = 0;

    if (find_free_element(ht, &ind, &coll, val) != 0)
    {
        return HASH_END;
    }


    ht->arr[ind].val = val;
    ht->arr[ind].status = true;
    ht->arr[ind].deleted = false;

    res = coll;


    return res;
}

void ht_print(const hash_table_t *ht)
{
    printf("+-----------+------------------+\n");
    printf("|     hash   |      data       |\n");
    for (int i = 0; i < ht->len; i++)
    {
        if (ht->arr[i].status && !ht->arr[i].deleted)
        {
            printf("+-----------+------------------+\n");
            printf("|%7d    |  %7d         |\n", i, ht->arr[i].val);
        }
    }
    printf("+-----------+------------------+\n");
}

int find_element(hash_table_t *ht, unsigned *ind, short *cmps, int key)
{
    while ((*ind) < ht->len && (*cmps)++ >= 0)
    {
        (*ind)++;
        if (ht->arr[*ind].val == key && ht->arr[*ind].deleted == false)
        {
            break;
        }
    }
    if (*ind == ht->len - 1)
    {
        return NOT_FOUND;
    }
    else
    {
        return 0;
    }
}

short ht_find(hash_table_t *ht, int key, unsigned (*hash_func)(int, unsigned))
{
    if (hash_func == NULL)
    {
        return INVALID_HASH_FUNC;
    }

    unsigned ind = hash_func(key, ht->len);
    if (ht->arr[ind].val == key && ht->arr[ind].status && !ht->arr[ind].deleted)
    {
        ht->arr[ind].deleted = true;
        return 1;
    }
    else
    {
        short cmps = 0;
        int rc = find_element(ht, &ind, &cmps, key);
        if (rc == NOT_FOUND)
        {
            return NOT_FOUND;
        }
        if (ht->arr[ind].val == key && ht->arr[ind].status && !ht->arr->deleted)
        {
            ht->arr[ind].deleted = true;
            return ++cmps;
        }
        else
        {
            return NOT_FOUND;
        }
    }
}
