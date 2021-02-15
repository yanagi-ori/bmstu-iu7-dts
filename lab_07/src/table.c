//
// Created by Ivan Bogatyrev on 2/15/2021.
//

#include <stdio.h>
#include "../inc/table.h"

int fillCell(int **table, int from, int to, int weight, int num)
{
    if (from > num || to > num)
    {
        return -1;
    }

    table[from][to] = weight;
    table[to][from] = weight;

    return 0;
}

void printTable(int **table, int num)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}