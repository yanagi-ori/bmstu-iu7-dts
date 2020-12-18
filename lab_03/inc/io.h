//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#ifndef LAB_03_IO_H
#define LAB_03_IO_H

short get_input_mode(bool *manual_input);

short get_matrix_sizes(sparse_matrix_t *matrix, sparse_matrix_t *vector);

short matrix_filling(matrix_t *matrix, sparse_matrix_t *sparse_matrix, bool manual_input);

short source_output(matrix_t matrix, matrix_t vector, int width, int height);

short standard_matrix_result_output(matrix_t matrix, int width);

short sparse_matrix_result_output(sparse_matrix_t matrix, int width);

void compare_results(matrix_t std_matrix, sparse_matrix_t sparse_matrix,
                     int64_t std_start, int64_t std_end, int64_t sparse_end, int curr_size);

#endif //LAB_03_IO_H
