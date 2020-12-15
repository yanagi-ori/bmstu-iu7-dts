//
// Created by Ivan Bogatyrev on 12/15/2020.
//

#ifndef LAB_02_SORT_H
#define LAB_02_SORT_H

#include "structures.h"

int comparator_keys(const void *val1, const void *val2);

int comparator_table(const void *val1, const void *val2);

short qs_vs_bubble(table_t *const table);

#endif //LAB_02_SORT_H
