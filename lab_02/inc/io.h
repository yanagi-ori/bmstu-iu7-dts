//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#ifndef LAB_02_IO_H
#define LAB_02_IO_H

#include <stdint.h>


short menu(short int *action);

short load_file(table_t *table);

short append_student(table_t *table);

void print_table(const table_t table, bool keys);

short delete_students(table_t *table);

void print_table_keys(const table_t table);

void print_sorts_vs_results(uint64_t total_ticks, short sort_type, short table_type);

#endif //LAB_02_IO_H
