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

void printArray(node_t **array, int num)
{
    printf("\n");
    for (int i = 0; i < num; i++)
    {
        printf("%d %d\n", array[i]->visited, array[i]->dist);
    }
}

int dijkstra(int **table, node_t **array, int num)
{
    int temp;
    int min_index = INT_MAX;
    int min;
    do
    {
        min_index = INT_MAX;
        min = INT_MAX;

        for (int i = 0; i < num; i++)
        {
            if ((array[i]->visited == false) && (array[i]->dist < min))
            {
                min = array[i]->dist;
                min_index = i;
            }
        }

        if (min_index != INT_MAX)
        {
            for (int i = 0; i < num; i++)
            {
                if (table[min_index][i] > 0)
                {
                    temp = min + table[min_index][i];
                    if (temp < array[i]->dist)
                    {
                        array[i]->dist = temp;
                    }
                }
            }
            array[min_index]->visited = true;
        }
    } while (min_index < INT_MAX);

    return 0;
}


void graph_to_jpeg(FILE *file, int **table, node_t **array, char *name, int num, int limit)
{
    int temp = 0;
    fprintf(file, "digraph %s {\n", name);
    //fprintf(file, "edge [dir=\"both\"];\n");
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (array[i]->dist <= limit && array[j]->dist <= limit && table[i][j] > 0 && array[i]->dist + table[i][j]
                                                                                         <= array[j]->dist)
            {
                fprintf(file, "%d -> %d [label=%d];\n", i, j, table[i][j]);
            }
        }
    }

    fprintf(file, "}\n");
}
