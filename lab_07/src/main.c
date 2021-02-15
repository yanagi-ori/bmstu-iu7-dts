#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/table.h"

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

    int rc = fileRead(file, &array, &table, &num);

    if (rc != 0)
    {
        printf("%d\n", rc);
    }
    else
    {
        printf("Data was loaded\n");
        printTable(table, num);
    }

    fclose(file);

    return 0;
}
