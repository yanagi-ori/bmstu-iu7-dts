#include <stdio.h>
#include <stdbool.h>
#include "../inc/structures.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/matrix_utils.h"

int main()
{
    printf("LAB_03\n\n"
           "This program multiplies a row linked_list by a matrix, processing them\n"
           "\ta) Using algorithms for processing sparse matrices.\n"
           "\tb) Using standard matrix processing algorithms.\n\n"
           "The sparse matrix is stored in two arrays and one linked_list:\n"
           "\t- A is an array of nonzero elements\n "
           "\t- JA is an array of column numbers for each element of A\n"
           "\t-linked_list JA, which contains the index of each first element of the next row in arrays A and JA. "
           "Would you like to enter the matrix values yourself? [Y/n] ");

    short rc;
    bool manual_input = 0;
    rc = get_input_mode(&manual_input);
    if (rc == IO_ERROR_INPUT_FROM_KEYBOARD)
    {
        fprintf(stderr, "Incorrect input.\n");
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }

    sparse_matrix_t sparse_matrix, sparse_vector, sparse_result;
    std_matrix_t std_matrix, std_vector, std_result;
    linked_list_t matrix_list, vector_list, result_list;

    rc = get_matrix_sizes(&sparse_matrix, &sparse_vector);
    if (rc == IO_ERROR_INPUT_FROM_KEYBOARD)
    {
        fprintf(stderr, "Incorrect input format.\n");
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (rc == IO_INVALID_ROWS_NUMBER)
    {
        fprintf(stderr, "Incorrect rows number.\n");
        return IO_INVALID_ROWS_NUMBER;
    }
    if (rc == IO_INVALID_COLUMNS_NUMBER)
    {
        fprintf(stderr, "Incorrect columns number.\n");
        return IO_INVALID_COLUMNS_NUMBER;
    }
    if (rc == IO_ELEMENTS_LIMIT)
    {
        fprintf(stderr, "The limit of the number of non-zero elements in the matrix has been exceeded");
        return IO_ELEMENTS_LIMIT;
    }

    init_vector(&sparse_vector, sparse_matrix.rows);
    init_vector(&sparse_result, sparse_matrix.columns);


    return 0;
}

