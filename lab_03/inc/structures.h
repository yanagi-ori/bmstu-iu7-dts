//
// Created by Ivan Bogatyrev on 12/17/2020.
//

#ifndef LAB_03_STRUCTURES_H
#define LAB_03_STRUCTURES_H

// linked_list structures
typedef struct node
{
    int start_row_ind;
    struct node *next_element_ptr;
} node_t;

typedef struct linked_list
{
    node_t *head;
} linked_list_t;

// matrix structures
typedef struct sparse_matrix
{
    int rows;
    int columns;
    long int curr_size;

    int *A;
    int *JA;
    linked_list_t IA;
} sparse_matrix_t;

typedef struct matrix
{
    int **matrix;
    int rows;
    int columns;
} matrix_t;

#endif //LAB_03_STRUCTURES_H
