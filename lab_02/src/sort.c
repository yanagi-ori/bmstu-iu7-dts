//
// Created by Ivan Bogatyrev on 12/15/2020.
//

#include "../inc/structures.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/sort.h"
#include "../inc/io.h"
#include "../inc/table_utils.h"

int comparator_keys(const void *val1, const void *val2)
{
    return ((keys_t *) (val1))->age - ((keys_t *) (val2))->age;
}

int comparator_table(const void *val1, const void *val2)
{
    return ((student_t *) (val1))->age - ((student_t *) (val2))->age;
}

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

static void swap(bool table, void *val1, void *val2)
{
    if (table)
    {
        student_t *temp = *(student_t **) val1;
        *(student_t **) val1 = *(student_t **) (val2);
        *(student_t **) val2 = temp;
    }
    else
    {
        keys_t temp = *(keys_t *) val1;
        *(keys_t *) val1 = *(keys_t *) (val2);
        *(keys_t *) val2 = temp;
    }
}


void bubble_sort_table(student_t **students_array, int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (students_array[j - 1]->age > students_array[j]->age)
            {
                student_t *temp_student = students_array[j];
                students_array[j] = students_array[j - 1];
                students_array[j - 1] = temp_student;
            }
        }
    }
}

void bubble_sort_keys(keys_t *keys_array, int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (keys_array[j - 1].age > keys_array[j].age)
            {
                keys_t temp_key = keys_array[j];
                keys_array[j] = keys_array[j - 1];
                keys_array[j - 1] = temp_key;
            }
        }
    }
}

short qs_vs_bubble(table_t *const table)
{
    uint64_t start, end, end1, end2, end3, start1, start2, start3;

    printf("\nSorting table of %d keys\n", table->size);

    start = tick();
    qsort(table->students, table->size, sizeof(student_t *), comparator_table);
    end = tick();
    print_sorts_vs_results(end - start, 1, 1);

    start1 = tick();
    qsort(table->keys, table->size, sizeof(keys_t), comparator_keys);
    end1 = tick();
    print_sorts_vs_results(end1 - start1, 1, 0);

    load_file(table);

    start2 = tick();
    bubble_sort_table(table->students, table->size);
    end2 = tick();
    print_sorts_vs_results(end2 - start2, 0, 1);

    start3 = tick();
    bubble_sort_keys(table->keys, table->size);
    end3 = tick();
    print_sorts_vs_results(end3 - start3, 0, 0);

    printf("\n%lu - keys array size (in bytes)\n", sizeof(*(table->keys)) * table->size);
    printf("\n%lu - array size (in bytes)\n", sizeof(student_t) * table->size);

    return 0;
}