//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include "../inc/structures.h"
#include <stdlib.h>
#include "../inc/errors.h"
#include "../inc/memory_manager.h"

short create_matrix(matrix_t *matrix, const int rows, const int columns)
{
    matrix->matrix = malloc(rows * sizeof(int *));

    if (!matrix->matrix)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    int *data = calloc(rows * columns, sizeof(int));
    if (!data)
    {
        free(matrix->matrix);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < rows; i++)
    {
        matrix->matrix[i] = data + i * columns;
    }

    matrix->rows = rows;
    matrix->columns = columns;

    return 0;
}

void free_matrix(int **matrix)
{
    free(matrix[0]);
    free(matrix);
    matrix = NULL;
}


short create_array(int **new_array, int size, int **memory_manager_list, int *memory_manager_len)
{
    *new_array = malloc(sizeof(int) * size);
    if (*new_array == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    memory_manager_list[*memory_manager_len] = *new_array;
    *memory_manager_len += 1;

    return 0;
}

void free_memory_manager(int **memory_manager_list, int memory_manager_len)
{
    for (int i = 0; i < memory_manager_len; i++)
    {
        free(memory_manager_list[i]);
    }
    free(memory_manager_list);
}


short create_liked_list(int size, linked_list_t *list)
{
    list->head = NULL;

    for (int i = 0; i < size; i++)
    {
        node_t *curr_element = malloc(sizeof(node_t));

        if (curr_element == NULL)
        {
            return MEMORY_ALLOCATION_ERROR;
        }

        curr_element->next_element_ptr = list->head;
        curr_element->start_row_ind = -1;
        list->head = curr_element;
    }

    return 0;
}

void free_linked_list(linked_list_t *list)
{
    node_t *curr, *temp;
    curr = list->head;

    while (curr->next_element_ptr != NULL)
    {
        temp = curr->next_element_ptr;
        free(curr);
        curr = temp;
    }

    free(temp);
}