//
// Created by Ivan Bogatyrev on 9/26/2020.
//


#include "data_structure.h"

#ifndef LAB_01_PARSE_H
#define LAB_01_PARSE_H

short int parse(const char *raw_number, number_structure *parsed_number);

int is_not_digit(char sym);

int char_to_int(char sym);

short post_process(number_structure integer_parsed,
                   number_structure float_parsed,
                   number_structure *result_number,
                   short int fl);

void null_counter(const char *mantissa, unsigned int index, unsigned short *counter, short int mode);

#endif //LAB_01_PARSE_H

