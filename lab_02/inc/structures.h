//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#ifndef LAB_02_STRUCTURES_H
#define LAB_02_STRUCTURES_H

#include <stdbool.h>

typedef struct date
{
    unsigned int year;
    unsigned short int month;
    unsigned short int day;
} date_t;

typedef struct is_dormitory
{
    unsigned short int dormitory_num;
    unsigned short int room_num;
} is_dormitory_t;

typedef struct is_house
{
    char *street;
    unsigned short int house_num;
    unsigned short int apartment_num;
} is_house_t;

typedef union address
{
    is_dormitory_t dormitory;
    is_house_t house;
} address_t;

typedef struct student
{
    char *surname;
    char *name;
    short int group;
    bool sex; // 0 - female, 1 - male
    short int age;
    double average_score;
    date_t date;
    bool is_dormitory;
    address_t address;
} student_t;

typedef struct keys
{
    int age;
    short id;
} keys_t;

typedef struct table
{
    student_t **students;
    keys_t *keys;
    short size;
} table_t;


#endif //LAB_02_STRUCTURES_H
