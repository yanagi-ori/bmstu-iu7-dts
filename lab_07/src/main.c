#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/table.h"
#include "../inc/memory_management.h"


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments\n");
        return WRONG_ARGUMENTS;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Couldn't read the file");
        return IO_ERROR;
    }

    if (getFileSize(file) <= 0)
    {
        fprintf(stderr, "The file is empty");
        return IO_ERROR;
    }

    int **table;
    node_t **array;
    int num;

    int rc = fileRead(file, &table, &num);

    if (rc != 0)
    {
        printf("%d\n", rc);
    }
    else
    {
        printf("Data was loaded\n");
        printTable(table, num);
    }

    array = createArray(num);
    printArray(array, num);

    printf("-------------------------------------------\n\n");


    printf("Input begin index:\n");
    int begin_index = 0;
    rc = fscanf(stdin, "%d", &begin_index);
    if (rc != 1)
    {
        fprintf(stderr, "Invalid input");
        return INPUT_ERROR;
    }
    else
    {
        array[begin_index]->dist = 0;
    }

    dijkstra(table, array, num);

    printArray(array, num);

    freeMatrix(table);
    freeArray(array, num);
    fclose(file);

    return 0;
}