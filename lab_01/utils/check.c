//
// Created by Ivan Bogatyrev on 9/26/2020.
//

#include "../headers/check.h"
#include "../headers/errors.h"
#include "../headers/parse.h"
#include <string.h>
#include <ctype.h>

short int e_counter(const char item, short int *e_counter)
{
    if (item == 'e' || item == 'E')
    {
        (*e_counter)++;
    }
    if (*e_counter > 1)
    {
        return -1;
    }

    return 0;
}

short int dots_counter(const char item, short int *dots)
{
    if (item == '.')
    {
        (*dots)++;
    }
    if (*dots > 1)
    {
        return -1;
    }
    return 0;
}

short int check_allowed(const char item)
{
    if (item != '-' && item != '+' && item != '.' && item != 'e' && item != 'E' && (is_not_digit(item)))
    {
        return -1;
    }
    return 0;
}

short int sign_check(const char *num, const short int index)
{
    if (num[index] == '+' || num[index] == '-')
    {
        if (index == 0)
        {
            return 0;
        }
        if (!(num[index - 1] == 'E' || num[index - 1] == 'e'))
        {
            return -1;
        }
    }
    return 0;
}

short int sign_after_e_check(const char e, const char sign)
{
    if ((e == 'e' || e == 'E'))
    {
        if (!(sign == '+' || sign == '-'))
        {
            return -1;
        }
    }
    return 0;
}

short int dots_in_degree_check(const char item, short int e_counter)
{
    if (item == '.' && e_counter != 0)
    {
        return -1;
    }
    return 0;
}

short int check_sign(const char item)
{
    if (item != '-' && item != '+')
    {
        return -1;
    }
    return 0;
}


short integer_check(char *integer_raw)
{
    for (int i = 1; i < strlen(integer_raw); i++)
    {
        if (!isdigit(integer_raw[i]))
        {
            return 1;
        }
    }

    return 0;
}

short int input_check(char *float_number)
{
    short int index = 0, es = 0, dots = 0;
    char item;

    while (float_number[index] != '\0')
    {
        item = float_number[index];

        if (check_allowed(item) != 0)
        {
            return INPUT_FORBIDDEN_SYMBOL;
        }
        if (e_counter(item, &es) != 0)
        {
            return INPUT_E_ERROR;
        }
        if (sign_check(float_number, index) != 0)
        {
            return INPUT_SIGN_ERROR;
        }
        if (sign_after_e_check(item, float_number[index + 1]) != 0)
        {
            return INPUT_SIGN_ERROR;
        }
        if (dots_in_degree_check(item, es) != 0)
        {
            return INPUT_DOTS_IN_DEGREE;
        }
        if (dots_counter(item, &dots) != 0)
        {
            return INPUT_DOTS_IN_DEGREE;
        }
        index++;
    }

    if (check_sign(float_number[0]) != 0)
    {
        return INPUT_SIGN_ERROR;
    }

    if (item == 'e' || item == 'E')
    {
        return INPUT_E_ERROR;
    }

    if (item == '+' || item == '-')
    {
        return INPUT_SIGN_ERROR;
    }

    return 0;
}

int result_of_mantissa_parsing_check(const char *const mantissa)
{
    if (!mantissa[0])
    {
        return -1;
    }
    return 0;
}

short int null_check(const number_structure result_number)
{
    unsigned short int len = strlen(result_number.mantissa);

    for (int i = 0; i < len; i++)
    {
        if (result_number.mantissa[i] != '0')
        {
            return 0;
        }
    }

    return 1;
}

short int integer_e_check(number_structure integer)
{

    unsigned short int counter1 = 0;
    unsigned short int counter2 = 0;
    null_counter(integer.mantissa, 0, &counter1, 1);
    null_counter(integer.mantissa, strlen(integer.mantissa) - 1, &counter2, -1);
    if (integer.degree >= 0)
    {
        if (counter1 > integer.degree + 1)
        {
            return -1;
        }
    }
    else
    {
        if (counter2 < -integer.degree + 1)
        {
            return -1;
        }
    }

    return 0;
}

int check_expon(char *const num, short int cur_len, short int len)
{
    if (cur_len == len)
    {
        return 1;
    }

    if (toupper(num[cur_len]) == 'E')
    {
        return 0;
    }

    return check_expon(num, ++cur_len, len);
}