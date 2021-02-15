//
// Created by Ivan Bogatyrev on 2/14/2021.
//

#include <stdlib.h>
#include "../inc/graph.h"
#include "../inc/memory_management.h"

void initTable(int **table, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            table[i][j] = 0;
        }
    }
}

int **createMatrix(int rows, int cols)
{
    int **pointers, *data;

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

void freeMatrix(int **matrix)
{
    free(matrix[0]);
    free(matrix);
}

node_t **createArray(int num)
{
    node_t **temp = malloc(sizeof(node_t *) * num);
    for (int i = 0; i < num; i++)
    {
        temp[i] = init_node();
    }

    return temp;
}