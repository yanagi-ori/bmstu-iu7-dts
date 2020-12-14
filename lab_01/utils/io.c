//
// Created by Ivan Bogatyrev on 11/8/2020.
//

#include <stdio.h>
#include <string.h>
#include "../headers/io.h"


void range_print()
{
    printf("\n%s %29s\n", "mantissa", "degree");
    printf("%2d %9d %9d %9d %1d %3d\n", 1, 10, 20, 30, 1, 5);
    printf("-|--------|---------|---------|E-|---|\n");
}

void print_result(const number_structure result)
{
    if (!strcmp("\0", result.mantissa))
    {
        printf("RESULT: %23s\n", "0.0");
    }
    else if (result.degree >= 0)
    {
        printf("RESULT: %20c0.%se+%d\n", result.m_sign, result.mantissa, result.degree);
    }
    else
    {
        printf("RESULT: %20c0.%se%d\n", result.m_sign, result.mantissa, result.degree);
    }
}
