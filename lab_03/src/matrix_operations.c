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
