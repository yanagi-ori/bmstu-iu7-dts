//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include "../inc/structures.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/io.h"
#include "../inc/errors.h"

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