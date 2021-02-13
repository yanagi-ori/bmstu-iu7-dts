#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"

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

    if (get_file_size(file) <= 0)
    {
        fprintf(stderr, "The file is empty");
        return IO_ERROR;
    }

    fclose(file);

    return 0;
}
