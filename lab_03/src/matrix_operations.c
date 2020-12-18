//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include <stdio.h>
#include "../inc/structures.h"
#include "../inc/matrix_operations.h"
#include "../inc/memory_manager.h"

static void transpose_matrix(matrix_t *matrix, matrix_t *new_matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            *(*(new_matrix->matrix + j) + i) = *(*(matrix->matrix + i) + j);
        }
    }
}

void transpose(matrix_t *matrix)
{
    matrix_t new_matrix_temp;

    create_matrix(&new_matrix_temp, matrix->columns, matrix->rows);
    transpose_matrix(matrix, &new_matrix_temp);

    free_matrix(matrix->matrix);
    *matrix = new_matrix_temp;
}

node_t *get_by_pos(const linked_list_t *list, const int pos)
{
    node_t *temp_node = list->head;

    for (int i = 0; i < pos; i++)
    {
        if (temp_node->next_element_ptr == NULL)
        {
            return temp_node;
        }

        temp_node = temp_node->next_element_ptr;
    }

    return temp_node;
}

void change_by_pos(node_t *node, const linked_list_t *list, const int pos)
{
    node_t *temp_node = get_by_pos(list, pos);
    *temp_node = *node;
}


void multiplication(matrix_t *matrix, matrix_t *vector, matrix_t *result)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            result->matrix[0][i] += matrix->matrix[i][j] * vector->matrix[0][j];
        }
    }
}

void apply(sparse_matrix_t *result, int sum, int index)
{
    result->A[result->curr_size] = sum;
    result->JA[result->curr_size] = index;
    result->curr_size++;
}

void sparce_multiplication(sparse_matrix_t *matrix, matrix_t *vector, sparse_matrix_t *result)
{

    node_t *temp_node = get_by_pos(&matrix->IA, 0);
    node_t *temp_next_node = NULL;
    result->curr_size = 0;
    int curr_sum;

    for (int i = 0; i < matrix->rows - 1; i++)
    {
        temp_next_node = temp_node->next_element_ptr;
        curr_sum = 0;

        for (int j = temp_node->start_column_ind; j < temp_next_node->start_column_ind; j++)
        {
            curr_sum += matrix->A[j] * vector->matrix[0][matrix->JA[j]];
        }

        if (curr_sum != 0)
        {
            apply(result, curr_sum, i);
        }

        temp_node = temp_next_node;
    }

    curr_sum = 0;
    for (int i = temp_node->start_column_ind; i < matrix->curr_size; i++)
    {
        curr_sum += matrix->A[i] * vector->matrix[0][matrix->JA[i]];
    }

    if (curr_sum != 0)
    {
        apply(result, curr_sum, matrix->rows - 1);
    }
}