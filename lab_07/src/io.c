//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#include <stdio.h>
#include "../inc/io.h"
#include "../inc/graph.h"
#include "../inc/memory_management.h"

unsigned long get_file_size(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return size;
}

node_t **fileRead(FILE *file)
{
    if (!file)
    {
        fprintf(file, "Could not access the file. Shutting down");
        return NULL;
    }

    int num;
    int rc = fscanf(file, "%d", &num);
    if (rc != 1)
    {
        fprintf(stderr, "Could not get the num of nodes. Shutting down");
        return NULL;
    }

    node_t **table = create_matrix(num, num);
    if (!table)
    {
        fprintf(stderr, "Couldn't create the table. Shutting down...");
        return NULL;
    }

    while (true)
    {
        int from, to, weight;
        int res = fscanf(file, "%d %d %d", &from, &to, &weight);

        if (res == EOF)
        {
            break;
        }

        if (res != 3)
        {
            fprintf(stderr, "Ошибка ввода.\n");
            free_matrix(table);
            return NULL;
        }

    }

    return table;
}