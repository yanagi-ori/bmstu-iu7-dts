//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#ifndef LAB_03_MATRIX_UTILS_H
#define LAB_03_MATRIX_UTILS_H

void init_vector(sparse_matrix_t *vector, int size);

short create_sparse_matrix(sparse_matrix_t *sparse_matrix, int *a, int *ja, linked_list_t *list);

void random_filling(matrix_t *std_matrix, int maxsize);

void convert_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix);

#endif //LAB_03_MATRIX_UTILS_H
