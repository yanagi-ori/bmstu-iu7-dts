#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"

int main(int argc, char **argv)
{
    printf("Lab 06. Graphs & Hash-Tables.\n");
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments");
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Invalid file");
        return IO_ERROR;
    }

    int *arr;
    int file_len = data_extract(file, &arr);
    if (file_len == EMPTY_FILE)
    {
        fprintf(stderr, "The file is empty");
        return EMPTY_FILE;
    }
    if (file_len == MEMORY_ALLOCATION_ERROR)
    {
        fprintf(stderr, "Memory allocation error");
    }
    if (file_len == INVALID_FILE)
    {
        fprintf(stderr, "Could not read the file to the end");
    }




    return 0;
}
