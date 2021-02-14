//
// Created by Ivan Bogatyrev on 2/14/2021.
//

#include <stdlib.h>
#include "../inc/graph.h"
#include "../inc/memory_management.h"

node_t **create_matrix(int rows, int cols)
{
    node_t **pointers, *data;

    if (rows <= 0 || cols <= 0)
    {
        return NULL;
    }

    pointers = malloc(rows * sizeof(int *));
    if (!pointers)
    {
        return NULL;
    }

    data = malloc(rows * cols * sizeof(int));
    if (!data)
    {
        free(pointers);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        pointers[i] = data + i * cols;
    }

    return pointers;
}

void free_matrix(node_t **matrix)
{
    free(matrix[0]);
    free(matrix);
}