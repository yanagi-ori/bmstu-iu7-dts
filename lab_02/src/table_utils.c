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

void free_student(student_t *student)
{
    if (student->surname)
    {
        free(student->surname);
    }
    if (student->name)
    {
        free(student->name);
    }
    if (!student->is_dormitory)
    {
        free(student->address.house.street);
    }
    free(student);
}

void free_table(table_t *table)
{
    for (int i = 0; i < table->size; i++)
    {
        free_student(table->students[i]);
    }
    table->size = 0;
}

void swap_students(student_t **student_a, student_t **student_b)
{
    student_t *temp = *student_a;
    *student_a = *student_b;
    *student_b = temp;
}

void swap_keys(keys_t *key_a, keys_t *key_b)
{
    keys_t temp = *key_a;
    *key_a = *key_b;
    *key_b = temp;
}

short remove_item(table_t *table, int i)
{
    for (int j = i + 1; j < table->size + 1; j++)
    {
        swap_students(&table->students[j - 1], &table->students[j]);
        swap_keys(&table->keys[j - 1], &table->keys[j]);
    }
    table->size--;

    return 0;
}

void update_keys(table_t *table, const short index, const short id, const short age)
{
    table->keys[index].id = id;
    table->keys[index].age = age;
}

void update_all_keys(table_t *table)
{
    for (short i = 0; i < table->size; i++)
    {
        update_keys(table, i, i, table->students[i]->age);
    }
}
