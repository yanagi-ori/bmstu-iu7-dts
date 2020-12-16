#include <stdio.h>
#include <string.h>
#include "headers/data_structure.h"
#include "headers/errors.h"
#include "headers/check.h"
#include "headers/parse.h"
#include "headers/operations.h"
#include "headers/io.h"


int main()
{
    char integer_raw[MAX_RAW_LEN] = {'\0'}, float_raw[MAX_RAW_LEN] = {'\0'};
    number_structure integer_n, float_n, result_n;
    memset(result_n.mantissa, '0', sizeof(result_n.mantissa));

    printf("RULES OF INPUT:\n"
           "* The number should have a sign of mantissa\n"
           "* The number should have a mantissa with length <= 30\n"
           "* E-symbol\n"
           "* Sign of the degree\n"
           "* Degree with length <= 5;\n\n");

    // reading of the first number
    printf("Enter a real integer number:");
    range_print();
    if (scanf("%50s", integer_raw) != 1)
    {
        printf("ERROR: Input length limit error\n");
        return INTEGER_INPUT_ERROR;
    }

    short int code_error = integer_check(integer_raw);
    short int fl = 0;
    if (code_error == 1)
    {
        printf("ERROR: invalid input of an integer number\n");
        return code_error;
    }

    // parsing of integer number
    if (check_expon(integer_raw, 0, strlen(integer_raw)))
    {
        code_error = to_exp(integer_raw);
        if (code_error == -1)
        {
            printf("ERROR: exponential conversion error\n");
            return INTEGER_TO_EXPON_ERROR;
        }
    }

    code_error = parse(integer_raw, &integer_n);
    if (code_error == PARSING_MANTISSA_ERROR)
    {
        printf("ERROR: the length of mantissa should be less than 30 symbols\n");
        return code_error;
    }
    if (code_error == PARSING_DEGREE_OUT_RANGE)
    {
        printf("ERROR: the length of degree should be less than 5 symbols\n");
        return code_error;
    }

    code_error = integer_e_check(integer_n);
    if (code_error == -1)
    {
        printf("The number you have entered is not an integer one");
        return INTEGER_WRONG_FORMAT;
    }

    //reading of the second number
    printf("\nEnter a float number:");
    range_print();
    if (scanf("%50s", float_raw) != 1)
    {
        printf("ERROR: Input length limit error\n");
        return FLOAT_INPUT_ERROR;
    }

    code_error = input_check(float_raw);
    if (code_error != 0)
    {
        if (code_error == INPUT_FORBIDDEN_SYMBOL)
        {
            printf("ERROR: forbidden symbol int the user input\n");
        }
        else if (code_error == INPUT_E_ERROR)
        {
            printf("ERROR: there is no \"E\" symbol in the user input\n");
        }

        else if (code_error == INPUT_SIGN_ERROR)
        {
            printf("ERROR: an extra +/- sign was found\n");
        }
        else if (code_error == INPUT_DOTS_IN_DEGREE)
        {
            printf("ERROR: float number in the degree\n");
        }
        else if (code_error == INPUT_DOTS_IN_MANTISSA)
        {
            printf("ERROR: an extra dot was found in mantissa\n");
        }
        return code_error;
    }

    if (check_expon(float_raw, 0, strlen(float_raw)))
    {
        code_error = to_exp(integer_raw);
        if (code_error == -1)
        {
            printf("ERROR: exponential conversion error\n");
            return INTEGER_TO_EXPON_ERROR;
        }
    }

    // parsing float number
    code_error = parse(float_raw, &float_n);
    if (code_error == PARSING_MANTISSA_ERROR)
    {
        printf("ERROR: the length of mantissa should be less than 30 symbols\n");
        return code_error;
    }
    if (code_error == PARSING_DEGREE_OUT_RANGE)
    {
        printf("ERROR: the length of degree should be less than 5 symbols\n");
        return code_error;
    }

    if (result_of_mantissa_parsing_check(float_n.mantissa))
    {
        printf("ERROR: incorrect input\n");
        return FLOAT_DATA_INVALID;
    }

    if (float_raw[1] == '0' && float_raw[2] == '.')
    {
        fl = 1;
        normalization(&float_n);
    }
    if (integer_raw[1] == '0' && integer_raw[2] == '.')
    {
        fl = 1;
        normalization(&integer_n);
    }

    multiplication(&integer_n, &float_n, &result_n);

    code_error = post_process(integer_n, float_n, &result_n, fl);
    if (code_error == PARSING_OVERFLOW)
    {
        printf("WARNING: the length of mantissa is more than 30 symbols, the result was rounded.\n");
        rounding(&result_n, MAX_MANTISSA - 3, 0);
        result_n.mantissa[MAX_MANTISSA - 2] = '\0';
    }
    if (code_error == PARSING_RANGE_ERROR)
    {
        printf("ERROR: the the degree of the result number is longer than 5 symbols.\n");
        return PARSING_OVERFLOW;
    }

    null_round(&result_n, strlen(result_n.mantissa) - 1);

    print_result(result_n);

    return 0;
}
