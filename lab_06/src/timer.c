//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include "../inc/timer.h"
#include <stdint.h>

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t) high << 32) | low;

    return ticks;
}

uint64_t get_time(timer_t timer)
{
    return timer.end - timer.start;
}