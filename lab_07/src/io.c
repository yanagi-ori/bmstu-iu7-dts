//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#include <stdio.h>
#include "../inc/io.h"
#include "../inc/graph.h"
#include "../inc/memory_management.h"
#include "../inc/errors.h"
#include "../inc/table.h"

unsigned long getFileSize(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return size;
}

int fileRead(FILE *file, int ***table, int *num)
{
    if (!file)
    {
        fprintf(file, "Could not access the file. Shutting down");
        return IO_ERROR;
    }

    *num = 0;
    int rc = fscanf(file, "%d", num);
    if (rc != 1)
    {
        fprintf(stderr, "Could not get the num of nodes. Shutting down");
        return INPUT_ERROR;
    }

    *table = createMatrix(*num, *num);
    if (!(*table))
    {
        fprintf(stderr, "Couldn't create the table. Shutting down...");
        return MEMORY_MANAGEMENT_ERROR;
    }

    initTable(*table, *num);


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
            fprintf(stderr, "Input error.\n");
            freeMatrix(*table);
            return INPUT_ERROR;
        }

        if (weight <= 0)
        {
            fprintf(stderr, "Input error. Weight couldn't be less or equal to zero.\n");
            freeMatrix(*table);
            return INPUT_ERROR;
        }

        if (fillCell(*table, from, to, weight, *num) == -1)
        {
            fprintf(stderr, "Input error.");
            freeMatrix(*table);
            return INPUT_ERROR;
        }

    }

    return 0;
}