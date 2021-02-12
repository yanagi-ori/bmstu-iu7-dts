//
// Created by Ivan on 1/29/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "../inc/io.h"
#include "../inc/memory_management.h"
#include "../inc/errors.h"

#define INIT_LEN 100


unsigned long get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    unsigned long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    return size;
}

// extracts data from the file to an array
// returns the len of file
int data_extract(FILE *file_stream, int **array)
{
    if (get_file_size(file_stream) == 0)
    {
        return EMPTY_FILE;
    }
    *array = create_dyn_array(INIT_LEN);
    if (*array == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    int rc = 1;
    int length = INIT_LEN;
    int i = 0;

    while (rc == 1)
    {
        rc = fscanf(file_stream, "%d", *array + i);
        i += (rc == 1);

        if (i >= length)
        {
            if (resize_array(array, &length) != 0)
            {
                return MEMORY_ALLOCATION_ERROR;
            }
        }

    }
    length = i;

    if (rc != EOF)
    {
        free((void *) *array);
        return INVALID_FILE;
    }

    return length;
}


int file_mod_del(FILE **file, int key, char *file_path, int *cmps, bool *deleted)
{
    rewind(*file);
    int curr_val;
    char temp_str[41];
    int res;
    int i = 1;
    *cmps = 0;
    *deleted = false;
    FILE *temp = fopen("temp.txt", "w");

    res = fscanf(*file, "%d", &curr_val);
    itoa(curr_val, temp_str, 10);

    while (res == 1 && i++ > 0)
    {
        if (curr_val != key)
        {
            (*cmps)++;
            fprintf(temp, temp_str);
            fprintf(temp, " ");
        }
        else
        {
            *deleted = true;
        }
        res = fscanf(*file, "%d", &curr_val);
        itoa(curr_val, temp_str, 10);
    }

    fclose(*file);
    fclose(temp);

    remove(file_path);
    rename("temp.txt", file_path);

    *file = fopen(file_path, "r");

    return i;
}
