//
// Created by Ivan Bogatyrev on 2/14/2021.
//

#ifndef LAB_07_MEMORY_MANAGEMENT_H
#define LAB_07_MEMORY_MANAGEMENT_H

int **createMatrix(int rows, int cols);

void freeMatrix(int **matrix);

void initTable(int **table, int size);

node_t **createArray(int num);

void freeArray(node_t **array, int num);

#endif //LAB_07_MEMORY_MANAGEMENT_H
