//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include "../inc/structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/matrix_utils.h"
#include "../inc/memory_manager.h"
#include "../inc/matrix_operations.h"

void init_vector(sparse_matrix_t *vector, const int size)
{
    vector->columns = size;
    vector->rows = 1;
}

short create_sparse_matrix(sparse_matrix_t *sparse_matrix, int *a, int *ja, linked_list_t *list)
{

    if (sparse_matrix->rows != 1)
    {
        short rc;
        if ((rc = create_liked_list(sparse_matrix->columns, list)))
        {
            free_linked_list(list);
            return rc;
        }
    }
    else
    {
        list->head = NULL;
    }

    sparse_matrix->A = a;
    sparse_matrix->JA = ja;
    sparse_matrix->IA = *list;

    return 0;
}

void random_filling(matrix_t *const std_matrix, const int maxsize)
{
    srand(time(NULL));

    for (int i = 0; i < maxsize; i++)
    {
        int irand = 0;
        int jrand = 0;
        do
        {
            irand = rand() % std_matrix->rows;
            jrand = rand() % std_matrix->columns;
        } while (std_matrix->matrix[irand][jrand] != 0);

        std_matrix->matrix[irand][jrand] = rand() % 100 + 1;
    }
}

void convert_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix)
{
    int sparse_index = 0;

    for (int i = 0; i < matrix->rows; i++)
    {
        if (sparse_matrix->IA.head != NULL)
        {
            node_t *temp_node = get_by_pos(&sparse_matrix->IA, i);
            temp_node->start_row_ind = sparse_index;
            change_by_pos(temp_node, &sparse_matrix->IA, i);
        }

        for (int j = 0; j < matrix->columns; j++)
        {
            if (matrix->matrix[i][j] != 0)
            {
                sparse_matrix->A[sparse_index] = matrix->matrix[i][j];
                sparse_matrix->JA[sparse_index] = j;
                sparse_index++;
            }
        }
    }

    sparse_matrix->curr_size = sparse_index;
}