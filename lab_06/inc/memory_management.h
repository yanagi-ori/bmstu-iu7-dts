//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#ifndef LAB_06_MEMORY_MANAGEMENT_H
#define LAB_06_MEMORY_MANAGEMENT_H

#include "bin_tree.h"

int *create_dyn_array(int len);

int resize_array(int **array, int *new_len);

void free_tree(tree_node_t *tree);

#endif //LAB_06_MEMORY_MANAGEMENT_H
