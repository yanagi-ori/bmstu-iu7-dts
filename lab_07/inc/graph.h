//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#ifndef LAB_07_GRAPH_H
#define LAB_07_GRAPH_H

#include <stdbool.h>

typedef struct node
{
    int dist;
    bool visited;
} node_t;

node_t *initNode();

void printArray(node_t **array, int num);

int dijkstra(int **table, node_t **array, int num);

#endif //LAB_07_GRAPH_H
