//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#include <stdlib.h>
#include "../inc/graph.h"

node_t *init_node()
{
    node_t *node = malloc(sizeof(node_t));

    node->dist = 0 - 1;
    node->visited = false;

    return node;
}

