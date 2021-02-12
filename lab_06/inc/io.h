//
// Created by Ivan on 1/29/2021.
//

#ifndef LAB_06_IO_H
#define LAB_06_IO_H

#include <stdbool.h>

unsigned long get_file_size(FILE *f);

int data_extract(FILE *file_stream, int **array);

int file_mod_del(FILE **file, int key, char *file_path, int *cmps, bool *deleted);

#endif //LAB_06_IO_H
