//
// Created by Ivan Bogatyrev on 12/18/2020.
//

#include "../inc/structures.h"
#include "../inc/errors.h"
#include "../inc/matrix_utils.h"

void init_vector(sparse_matrix_t *vector, const int size)
{
    vector->columns = size;
    vector->rows = 1;
}