#include <stdio.h>
#include <stdint.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/table.h"
#include "../inc/memory_management.h"
#include "../inc/timer.h"


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
        return rc;
    }
    else
    {
        printf("Data was loaded\n");
        printTable(table, num);
    }
    fclose(file);

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

    printf("Input the maximum length: ");
    int limit;
    rc = scanf("%d", &limit);
    if (rc != 1)
    {
        fprintf(stderr, "Invalid input. No valid number was got");
        return INPUT_ERROR;
    }
    else if (limit < 0)
    {
        fprintf(stderr, "Invalid input. The max len could not be negative");
        return INPUT_ERROR;
    }
    else if (limit == 0)
    {
        fprintf(stderr, "Warning. A maximum of zero means that only the starting point is available,"
                        "and the algorithm would not be executed.\n");
    }
    else
    {
        uint64_t start = tick();
        dijkstra(table, array, num);
        uint64_t end = tick();
        printf("Dijkstra algorithm was processed in %lu CPU ticks\n", end - start);

        file = fopen("graph.txt", "w");
        graph_to_jpeg(file, table, array, "Ooops", num, limit);
        printArray(array, num);
        fclose(file);
    }


    freeMatrix(table);
    freeArray(array, num);

    return 0;
}
