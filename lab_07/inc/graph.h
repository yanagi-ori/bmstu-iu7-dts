//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#ifndef LAB_07_GRAPH_H
#define LAB_07_GRAPH_H

#include <stdbool.h>

typedef struct node
{
    unsigned dist;
    bool visited;
} node_t;

node_t *init_node();

#endif //LAB_07_GRAPH_H
