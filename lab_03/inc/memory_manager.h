//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#ifndef LAB_03_MEMORY_MANAGER_H
#define LAB_03_MEMORY_MANAGER_H

short create_matrix(matrix_t *matrix, const int rows, const int columns);

void free_matrix(int **matrix);

short create_array(int **new_array, int size, int **memory_manager_list, int *memory_manager_len);

void free_memory_manager(int **memory_manager_list, int memory_manager_len);

short create_liked_list(int size, linked_list_t *list);

void free_linked_list(linked_list_t *list);

#endif //LAB_03_MEMORY_MANAGER_H
