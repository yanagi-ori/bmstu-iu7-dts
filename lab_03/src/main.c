#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/structures.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/matrix_utils.h"
#include "../inc/memory_manager.h"
#include "../inc/benchmark.h"
#include "../inc/matrix_operations.h"

#define WIDTH 80

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
           "Would you like to enter the matrix values yourself? [Y/n] \n");

    short rc;
    bool manual_input = 0;
    rc = get_input_mode(&manual_input);
    if (rc == IO_ERROR_INPUT_FROM_KEYBOARD)
    {
        fprintf(stderr, "Incorrect input.\n");
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }

    // sparse matrix initialization
    sparse_matrix_t sparse_matrix, sparse_vector, sparse_result;

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
        fprintf(stderr, "The limit of the number of non-zero elements in the matrix has been exceeded\n");
        return IO_ELEMENTS_LIMIT;
    }

    init_vector(&sparse_vector, sparse_matrix.rows);
    init_vector(&sparse_result, sparse_matrix.columns);

    // standard matrix initialization
    matrix_t std_matrix, std_vector, std_result;

    rc = create_matrix(&std_matrix, sparse_matrix.rows, sparse_matrix.columns);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        fprintf(stderr, "Memory allocation error (std matrix creation). \n");
        return MEMORY_ALLOCATION_ERROR;
    }
    rc = create_matrix(&std_vector, sparse_vector.rows, sparse_vector.columns);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_matrix(std_matrix.matrix);
        fprintf(stderr, "Memory allocation error (std vector creation).\n");
        return MEMORY_ALLOCATION_ERROR;
    }
    rc = create_matrix(&std_result, sparse_result.rows, sparse_result.columns);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_matrix(std_matrix.matrix);
        free_matrix(std_vector.matrix);
        fprintf(stderr, "Memory allocation error (std result creation).\n");
    }

    int **memory_manager_list = malloc(sizeof(int *) * 6);
    int memory_manager_len = 0;

    int *a_matrix, *ja_matrix, *ja_vector, *ja_result, *a_vector, *a_result;
    rc = create_array(&a_matrix, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
    if (rc == 0)
    {
        rc = create_array(&ja_matrix, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
        if (rc == 0)
        {
            rc = create_array(&ja_vector, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
            if (rc == 0)
            {
                rc = create_array(&ja_result, sparse_matrix.columns, memory_manager_list, &memory_manager_len);
                if (rc == 0)
                {
                    rc = create_array(&a_vector, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
                    if (rc == 0)
                    {
                        rc = create_array(&a_result, sparse_matrix.columns, memory_manager_list, &memory_manager_len);
                    }
                }
            }
        }
    }
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_memory_manager(memory_manager_list, memory_manager_len);
        free_matrix(std_matrix.matrix);
        free_matrix(std_vector.matrix);
        free_matrix(std_result.matrix);
        fprintf(stderr, "Memory allocation error.\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    linked_list_t matrix_list, vector_list, result_list;
    rc = create_sparse_matrix(&sparse_matrix, a_matrix, ja_matrix, &matrix_list);
    if (rc == 0)
    {
        rc = create_sparse_matrix(&sparse_vector, a_vector, ja_vector, &vector_list);
        if (rc == 0)
        {
            rc = create_sparse_matrix(&sparse_result, a_result, ja_result, &result_list);
        }
    }
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_memory_manager(memory_manager_list, memory_manager_len);
        free_matrix(std_matrix.matrix);
        free_matrix(std_vector.matrix);
        free_matrix(std_result.matrix);
        fprintf(stderr, "Memory allocation error.\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    rc = matrix_filling(&std_matrix, &sparse_matrix, manual_input);
    if (rc == 0)
    {
        rc = matrix_filling(&std_vector, &sparse_vector, manual_input);
    }
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

    uint64_t start = tick();
    multiplication(&std_matrix, &std_vector, &std_result);
    int64_t std_end = tick();
    sparce_multiplication(&sparse_matrix, &std_vector, &sparse_result);
    int64_t end = tick();

    transpose(&std_matrix);
    rc = source_output(std_matrix, std_vector, 40, 40);
    if (rc == IO_OUTPUT)
    {
        printf("The source matrices are too big to be show.\n");
    }

    rc = standard_matrix_result_output(std_result, WIDTH);
    if (rc == IO_OUTPUT)
    {
        printf("The result of calculations of a regular matrix will not be displayed on the screen, "
               "since it contains more than %d elements.\n", WIDTH);
    }

    rc = sparse_matrix_result_output(sparse_result, WIDTH);
    if (rc == IO_OUTPUT)
    {
        printf("The result of calculations of a regular matrix will not be displayed on the screen, "
               "since it contains more than %d elements.\n", WIDTH);
    }
    if (rc == SPARSE_MATRIX_IS_EMPTY)
    {
        printf("\nThe result sparse matrix is empty\n");
    }

    compare_results(std_matrix, sparse_matrix, start, std_end, end, sparse_matrix.curr_size);

    return 0;
}

