#ifndef __STRUCT_H__
#define __STRUCT_H__

#define MAX_MANTISSA 31
#define MAX_DEGREE_LEN 8
#define MAX_DEGREE_VAL 99999
#define MAX_RAW_LEN 51

typedef struct
{
    char m_sign;
    char mantissa[MAX_MANTISSA * 2];
    int degree;
    short int point_index;
} number_structure;

#endif
