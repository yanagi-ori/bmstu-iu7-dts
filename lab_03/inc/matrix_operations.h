//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#ifndef LAB_03_MATRIX_OPERATIONS_H
#define LAB_03_MATRIX_OPERATIONS_H

void transpose(matrix_t *matrix);

node_t *get_by_pos(const linked_list_t *list, int pos);

void change_by_pos(node_t *node, const linked_list_t *list, int pos);

void multiplication(matrix_t *matrix, matrix_t *vector, matrix_t *result);

void sparce_multiplication(sparse_matrix_t *matrix, matrix_t *vector, sparse_matrix_t *result);

#endif //LAB_03_MATRIX_OPERATIONS_H
