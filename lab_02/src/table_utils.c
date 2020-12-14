//
// Created by Ivan Bogatyrev on 12/14/2020.
//
#include "../inc/errors.h"
#include "../inc/structures.h"
#include "../inc/table_utils.h"

void table_init(table_t *const table, student_t *const students_arr, keys_t *const keys_arr)
{
    table->students = students_arr;
    table->keys = keys_arr;
    table->size = 0;
}