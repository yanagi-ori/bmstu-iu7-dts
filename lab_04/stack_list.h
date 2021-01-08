//
// Created by Ivan Bogatyrev on 1/8/2021.
//

#ifndef LAB_04_STACK_LIST_H
#define LAB_04_STACK_LIST_H

#include <stdlib.h>
#include "errors.h"

typedef struct node
{
    int value;
    struct node *next;
} list_stack_t;



#endif //LAB_04_STACK_LIST_H
