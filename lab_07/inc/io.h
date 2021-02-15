//
// Created by Ivan Bogatyrev on 2/13/2021.
//

#ifndef LAB_07_IO_H
#define LAB_07_IO_H

#include "graph.h"

unsigned long getFileSize(FILE *file);

int fileRead(FILE *file, int ***table, int *num);

#endif //LAB_07_IO_H
