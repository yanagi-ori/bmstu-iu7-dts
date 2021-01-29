//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#ifndef LAB_06_TIMER_H
#define LAB_06_TIMER_H

#include <stdint.h>

typedef struct timer
{
    uint64_t start;
    uint64_t end;
} timer_t;

uint64_t tick(void);

uint64_t get_time(timer_t timer);

#endif //LAB_06_TIMER_H
