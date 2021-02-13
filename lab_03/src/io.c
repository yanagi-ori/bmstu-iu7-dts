//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include "../inc/structures.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/io.h"
#include "../inc/errors.h"
#include "../inc/matrix_utils.h"
#include "../inc/matrix_operations.h"

#define MAX_INT 2147483646

short get_input_mode(bool *manual_input)
{
    char *buffer = malloc(sizeof(char) * 101);
    if (scanf("%100s", buffer) != 1)
    {
        free(buffer);
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (buffer[0] == 'y' || buffer[0] == 'Y')
    {
        *manual_input = true;
    }
    else if (buffer[0] == 'n' || buffer[0] == 'N')
    {
        *manual_input = false;
    }
    else
    {
        free(buffer);
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }

    free(buffer);
    return 0;
}

short get_matrix_sizes(sparse_matrix_t *matrix, sparse_matrix_t *vector)
{
    printf("Enter amount of columns and columns in the matrix (2 - 10.000): \n");
    if (scanf("%d%d", &matrix->rows, &matrix->columns) != 2)
    {
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (matrix->rows < 2 || matrix->rows > 10000)
    {
        return IO_INVALID_ROWS_NUMBER;
    }
    if (matrix->columns < 2 || matrix->columns > 10000)
    {
        return IO_INVALID_COLUMNS_NUMBER;
    }

    int cur_size;
    printf("Enter a number of nonzero elements in the matrix: \n");
    if (scanf("%10d", &cur_size) != 1)
    {
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (cur_size > MAX_INT)
    {
        return IO_ELEMENTS_LIMIT;
    }

    long long size = matrix->rows * matrix->columns;
    if (cur_size < 1 || cur_size > size)
    {
        return IO_ELEMENTS_LIMIT;
    }
    matrix->curr_size = cur_size;

    printf("Enter a number of elements in the row vector: \n");
    if (scanf("%10d", &cur_size) != 1)
    {
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (cur_size < 1 || cur_size > matrix->rows)
    {
        return IO_ELEMENTS_LIMIT;
    }
    vector->curr_size = cur_size;

    return 0;
}


short matrix_manual_input(matrix_t *matrix, const int size)
{
    for (int i = 0; i < size; i++)
    {
        int numb, row, column;

        printf("Enter a nonzero item of matrix: \n");
        if (scanf("%d", &numb) != 1)
        {
            return IO_ERROR_INPUT_FROM_KEYBOARD;
        }

        printf("Enter the number of row and column of this item (starting from 0): \n");
        if (scanf("%d%d", &row, &column) != 2)
        {
            return IO_ERROR_INPUT_FROM_KEYBOARD;
        }

        if (row < 0 || row >= matrix->rows)
        {
            return IO_INVALID_ROWS_NUMBER;
        }

        if (column < 0 || column >= matrix->columns)
        {
            return IO_INVALID_COLUMNS_NUMBER;
        }

        matrix->matrix[row][column] = numb;
    }

    return 0;
}

short vector_manual_filling(matrix_t *matrix, const int size)
{
    int numb, column;

    for (int i = 0; i < size; i++)
    {
        printf("Enter a nonzero item of row vector: \n");
        if (scanf("%d", &numb) != 1)
        {
            return IO_ERROR_INPUT_FROM_KEYBOARD;
        }

        printf("Enter the number of the item's row (starting from 0): \n");
        if (scanf("%d", &column) != 1)
        {
            return IO_ERROR_INPUT_FROM_KEYBOARD;
        }

        if (column < 0 || column >= matrix->columns)
        {
            return IO_INVALID_COLUMNS_NUMBER;
        }

        matrix->matrix[0][column] = numb;
    }

    return 0;
}


short matrix_filling(matrix_t *matrix, sparse_matrix_t *sparse_matrix, const bool manual_input)
{
    if (manual_input == true)
    {
        short rc;
        if (sparse_matrix->rows == 1)
        {
            rc = vector_manual_filling(matrix, sparse_matrix->curr_size);
        }
        else
        {
            rc = matrix_manual_input(matrix, sparse_matrix->curr_size);
            transpose(matrix);
            sparse_matrix->rows = matrix->rows;
            sparse_matrix->columns = matrix->columns;
        }

        if (rc != 0)
        {
            return rc;
        }
    }
    else
    {
        random_filling(matrix, sparse_matrix->curr_size);
    }

    convert_matrix(matrix, sparse_matrix);

    return 0;
}

short source_output(matrix_t matrix, matrix_t vector, int width, int height)
{
    if (matrix.columns > width || matrix.rows > height)
    {
        return IO_OUTPUT;
    }
    printf("################################################################################\n");
    printf("\n\nVector\n");
    for (int i = 0; i < vector.columns; i++)
    {
        printf("%4d ", vector.matrix[0][i]);
    }

    printf("\n\nMatrix\n");
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.columns; j++)
        {
            printf("%4d ", matrix.matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    return 0;
}

short standard_matrix_result_output(matrix_t matrix, int width)
{
    if (matrix.columns > width)
    {
        return IO_OUTPUT;
    }

    puts("Result of multiplication by usual way: ");
    for (int i = 0; i < matrix.columns; i++)
    {
        printf("%d ", matrix.matrix[0][i]);
    }
    return 0;
}

short sparse_matrix_result_output(sparse_matrix_t matrix, int width)
{
    if (matrix.curr_size == 0)
    {
        return SPARSE_MATRIX_IS_EMPTY;
    }

    if (matrix.curr_size > width)
    {
        return IO_OUTPUT;
    }

    puts("\n\nSparse vector A:");

    for (int i = 0; i < matrix.curr_size; i++)
    {
        printf("%4d ", matrix.A[i]);
    }

    puts("\n\nArray of column indices JA: ");

    for (int i = 0; i < matrix.curr_size; i++)
    {
        printf("%4d ", matrix.JA[i]);
    }
    return 0;
}

void compare_results(matrix_t std_matrix, sparse_matrix_t sparse_matrix,
                     int64_t std_start, int64_t std_end, int64_t sparse_end, int curr_size)
{
    double one_percent = (double) (std_matrix.rows) * std_matrix.columns / 100;
    double amount = sparse_matrix.curr_size / one_percent;

    printf("\n\nMatrix %d x %d. Fullness (approximate): %.1lf%% / 100%%\n",
           std_matrix.rows, std_matrix.columns, amount);
    printf("\nNormal multiplication time: %Ild ticks\nSparse matrix multiplication time: %Ild ticks\n",
           std_end - std_start, sparse_end - std_end);
    printf("\nMemory footprint:\nRegular matrix (one):% zu\nSparse matrix (one):% zu\n",
           sizeof(int) * std_matrix.rows * std_matrix.columns,
           2 * sizeof(int) * curr_size + sizeof(node_t) * std_matrix.columns);
}