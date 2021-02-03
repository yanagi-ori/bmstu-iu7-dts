//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include <stdlib.h>
#include "../inc/memory_management.h"
#include "../inc/errors.h"

int *create_dyn_array(int len)
{
    int *temp_array = malloc(sizeof(int) * len);
    return temp_array;
}

int resize_array(int **array, int *new_len)
{
    *new_len *= 2;
    int *temp_array = realloc(*array, sizeof(int) * (*new_len));
    if (temp_array == NULL)
    {
        free(*array);
        return MEMORY_ALLOCATION_ERROR;
    }
    *array = temp_array;
    return 0;
}

