//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#include <stdio.h>
#include "../inc/io.h"

unsigned long get_file_size(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return size;
}
