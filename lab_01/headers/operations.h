//
// Created by Ivan Bogatyrev on 9/26/2020.
//


#include "data_structure.h"

#ifndef LAB_01_OPERATIONS_H
#define LAB_01_OPERATIONS_H

short int to_exp(char *raw_int);

void normalization(number_structure *number);

void multiplication(number_structure *int_number, number_structure *float_number, number_structure *result_number);

void null_round(number_structure *result_number, short int index);

void rounding(number_structure *number, unsigned short int end_ind, short int flag);

#endif

