//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include "../inc/structures.h"
#include <stdio.h>
#include "../inc/matrix_utils.h"
#include "../inc/memory_manager.h"

void init_vector(sparse_matrix_t *vector, const int size)
{
    vector->columns = size;
    vector->rows = 1;
}

short create_sparse_matrix(sparse_matrix_t *sparse_matrix, int *a, int *ja, linked_list_t *list)
{
    short rc;

    if (sparse_matrix->rows != 1)
    {
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