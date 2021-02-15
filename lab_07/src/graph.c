//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../inc/graph.h"

node_t *initNode()
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->dist = INT_MAX;
        node->visited = false;
    }

    return node;
}

