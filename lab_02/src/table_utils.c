//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#include "../inc/errors.h"
#include <stdlib.h>
#include "../inc/structures.h"
#include "../inc/table_utils.h"

short table_init(table_t *table)
{
    table->students = malloc(sizeof(student_t *) * 1);
    table->keys = malloc(sizeof(keys_t *) * 1);
    table->size = 0;

    if (table->students == NULL || table->keys == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    return 0;
}