//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#ifndef LAB_07_GRAPH_H
#define LAB_07_GRAPH_H

#include <stdbool.h>

typedef struct node
{
    int dist;
    int weight;
    bool visited;
} node_t;
#endif //LAB_07_GRAPH_H
