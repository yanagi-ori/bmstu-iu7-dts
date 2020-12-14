//
// Created by Ivan Bogatyrev on 9/26/2020.
//

#include "../headers/operations.h"
#include "../headers/parse.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char tmp[MAX_MANTISSA * 2];

char int_to_char(int number)
{
    return number + '0';
}

short int to_exp(char *raw_int)
{
    unsigned short int index = strlen(raw_int);
    char symbols[3] = {'e', '+', '0'};
    for (int i = 0; i < 3; i++)
    {
        if (index > 50)
        {
            return -1;
        }
        raw_int[index++] = symbols[i];
    }
    return 0;
}

void normalization(number_structure *number)
{
    short int k = 0;
    short int len = strlen(number->mantissa);
    short int i = len - number->point_index;

    while (number->mantissa[i++] == '0' && i < len)
    {
        k++;
    }

    if (k == 0)
    {
        return;
    }

    number->degree -= k;

    for (int q = len - 1; q > k; q--)
    {
        number->mantissa[q - k] = number->mantissa[q];
        number->mantissa[q] = '\0';
    }

    number->point_index -= k;

}

void discharge_multiplication(const char *const num, int len, char *const temp, int tmp_len, const int result_num)
{
    int discharge_num = result_num * (num[--len] - '0');
    temp[tmp_len] = int_to_char(char_to_int(temp[tmp_len]) + discharge_num % 10);
    temp[tmp_len - 1] = int_to_char(char_to_int(temp[tmp_len - 1]) + discharge_num / 10);

    if (len == 0)
    {
        return;
    }

    discharge_multiplication(num, len, temp, tmp_len - 1, result_num);
}

void discharge_sum(char *result_number, const char *const temp, int len)
{
    int discharge_num = char_to_int(temp[len]) + char_to_int(result_number[len]);

    result_number[len] = int_to_char(discharge_num % 10);
    result_number[len - 1] = int_to_char(char_to_int(result_number[len - 1]) + discharge_num / 10);

    if (len == 1)
    {
        return;
    }

    discharge_sum(result_number, temp, len - 1);
}


int mantissa_multiplication(number_structure *int_number, number_structure *float_number, char *result_mantissa)
{
    unsigned short len1 = strlen(int_number->mantissa), len2 = strlen(float_number->mantissa);
    int discharge = 1;
    int tmp_len = (MAX_MANTISSA * 2 - discharge);

    while (len1 != 0)
    {
        memset(tmp, '0', sizeof(tmp));
        discharge_multiplication(float_number->mantissa, len2, tmp, tmp_len,
                                 char_to_int(int_number->mantissa[len1 - 1]));
        discharge_sum(result_mantissa, tmp, (MAX_MANTISSA * 2) - 1);

        len1--;
        tmp_len--;
        discharge++;

    }

    return 0;
}


void get_sign(const number_structure num1, const number_structure num2, number_structure *result)
{
    if (num1.m_sign == num2.m_sign)
    {
        result->m_sign = '+';
    }
    else
    {
        result->m_sign = '-';
    }
}

void get_point_position(const number_structure num1, const number_structure num2, number_structure *result)
{
    result->point_index = num1.point_index + num2.point_index;
}

void multiplication(number_structure *int_number, number_structure *float_number, number_structure *result_number)
{
    mantissa_multiplication(int_number, float_number, result_number->mantissa);
    get_sign(*int_number, *float_number, result_number);
    get_point_position(*int_number, *float_number, result_number);
}

void null_round(number_structure *result_number, short int index)
{
    if (result_number->mantissa[index] == '0')
    {
        result_number->mantissa[index] = '\0';

        if (index != 0)
        {
            null_round(result_number, index - 1);
        }
    }
}

void rounding(number_structure *number, unsigned short int end_ind, short int flag)
{
    unsigned short int int_numb = number->mantissa[end_ind + 1] - '0';
    unsigned short int int_numb_cur = number->mantissa[end_ind] - '0';

    if (flag)
    {
        number->mantissa[end_ind] = int_to_char((int_numb_cur + 1) % 10);
    }

    if (number->mantissa[end_ind + 1] >= '5')
    {
        number->mantissa[end_ind] = int_to_char((int_numb + 1) % 10);
    }

    if (number->mantissa[end_ind] == '0' && end_ind != 0)
    {
        rounding(number, end_ind - 1, 1);
    }
}

void move_to_left(char *mantissa)
{
    unsigned short int len = strlen(mantissa);
    for (int i = 1; i < len; i++)
    {
        mantissa[i - 1] = mantissa[i];
    }
    mantissa[len - 1] = '\0';
}

void simplify_int(number_structure *integer)
{
    unsigned short int counter_left = 0;
    null_counter(integer->mantissa, 0, &counter_left, 1);
    while (integer->degree != 0)
    {
        if (counter_left > 0)
        {
            move_to_left(integer->mantissa);
            counter_left--;
        }
        else
        {
            integer->mantissa[strlen(integer->mantissa)] = '0';
        }
        integer->degree--;
    }
}