//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#ifndef LAB_02_TABLE_UTILS_H
#define LAB_02_TABLE_UTILS_H

short table_init(table_t *table);

short remove_item(table_t *table, int i);

void update_keys(table_t *table, const short index, const short id, const short age);

void free_table(table_t *table);

void swap_students(student_t **student_a, student_t **student_b);

#endif //LAB_02_TABLE_UTILS_H
