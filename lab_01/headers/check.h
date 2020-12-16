#include "data_structure.h"

#ifndef LAB_01_CHECK_H
#define LAB_01_CHECK_H

short int input_check(char *float_number);

short int check_sign(char item);

int result_of_mantissa_parsing_check(const char *mantissa);

short int null_check(number_structure result_number);

short int integer_e_check(number_structure integer);

int check_expon(char *num, short int cur_len, short int len);

short integer_check(char *integer_raw);

#endif