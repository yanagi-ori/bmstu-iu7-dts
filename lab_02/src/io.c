//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/structures.h"
#include "../inc/io.h"
#include "../inc/errors.h"
#include "../inc/table_utils.h"

#define GHZ 1500000000

short menu(short int *action)
{
    {
        printf("Menu: \n");
        printf("1. Load data from file;\n");
        printf("2. Add student to the bottom of the table;\n");
        printf("3. Remove all students of specified age;\n");
        printf("4. Show sorted by age array of keys\n");
        printf("5. Show sorted by age table;\n");
        printf("6. Show sorted by age table using sorted array of keys;\n");
        printf("7. Show the results of comparing the efficiency of processing a table and an array of keys;\n");
        printf("8. List the students living in the dormitory for the specified year of admission;\n");
        printf("9. Show the table;\n");
        printf("0. Exit.\n");
        printf("Enter the number of menu: ");
    }

    if (scanf("%hi", action) != 1)
    {
        return INVALID_INPUT_DATA;
    }
    if (*action > 9 || *action < 0)
    {
        return INVALID_INPUT_DATA;
    }

    return 0;
}

short get_table_size(table_t *table, FILE *file)
{
    if (fscanf(file, "%hi", &table->size) != 1)
    {
        return IO_FILE_SIZE_ERROR;
    }
    if (table->size < 1)
    {
        return IO_FILE_SIZE_ERROR;
    }
    return 0;
}

short get_date(date_t *date, FILE *stream, int i)
{

    if (!stream->_file)
    {
        printf("Please, enter the student admission date (dd mm yyyy): ");
    }
    //TODO: improve checking if the date is correct

    int temp;
    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0 || temp > 31)
    {
        return IO_DATE_FORMAT_ERROR_DAY;
    }
    date->day = (unsigned short) temp;

    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0 || temp > 12)
    {
        return IO_DATE_FORMAT_ERROR_MONTH;
    }
    date->month = temp;

    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
        return IO_DATE_FORMAT_ERROR_YEAR;
    }
    date->year = temp;

    return 0;
}

short get_student_data(table_t *table, FILE *stream, int i)
{
    char buffer[100];
    int temp;

    student_t *temp_student = malloc(sizeof(student_t));

    if (!stream->_file)
    {
        printf("Enter the student's surname: ");
    }
    if (fscanf(stream, "%99s", buffer) != 1)
    {
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->surname = strdup(buffer);

    if (!stream->_file)
    {
        printf("Enter the student's name: ");
    }
    if (fscanf(stream, "%99s", buffer) != 1)
    {
        free(temp_student->surname);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->name = strdup(buffer);

    if (!stream->_file)
    {
        printf("Enter the student's group number: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->group = (short) temp;

    if (!stream->_file)
    {
        printf("Enter the student's sex ( m / f ): ");
    }
    if (fscanf(stream, "%99s", buffer) != 1)
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (strlen(buffer) != 1 || (buffer[0] != 'm' && buffer[0] != 'f'))
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (buffer[0] == 'f')
    {
        temp_student->sex = (bool) 0;
    }
    else
    {
        temp_student->sex = (bool) 1;
    }

    if (!stream->_file)
    {
        printf("Enter the student's age: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->age = (short) temp;

    double temp_score;
    if (!stream->_file)
    {
        printf("Enter the student's average score: ");
    }
    if (fscanf(stream, "%lf", &temp_score) != 1)
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp_score <= 0)
    {
        free(temp_student->surname);
        free(temp_student->name);
        free(temp_student);
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->average_score = temp_score;

    table->students[i] = temp_student;

    return 0;
}

short get_address_state(table_t *table, FILE *stream, int i)
{
    char buffer[100];

    if (!stream->_file)
    {
        printf("Enter the address status ([d]ormitory or [h]ome): ");
    }
    if (fscanf(stream, "%99s", buffer) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (buffer[0] == 'd' || strcmp(buffer, "dormitory") == 0)
    {
        table->students[i]->is_dormitory = true;
    }
    else if (buffer[0] == 'h' || strcmp(buffer, "home") == 0)
    {
        table->students[i]->is_dormitory = false;
    }
    return 0;
}

short get_dormitory_data(address_t *address, FILE *stream)
{
    int temp;
    if (!stream->_file)
    {
        printf("Enter the number of dormitory: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
        return IO_DATA_FORMAT_ERROR_DORMITORY;
    }
    address->dormitory.dormitory_num = (unsigned short) temp;

    if (!stream->_file)
    {
        printf("Enter the number of room: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
        return IO_DATA_FORMAT_ERROR_DORMITORY;
    }
    address->dormitory.room_num = (unsigned short) temp;

    return 0;
}

short get_home_address(address_t *address, FILE *stream)
{
    char buffer[100];
    int temp;

    if (!stream->_file)
    {
        printf("Please, enter the street: ");
    }
    if (fscanf(stream, "%99s", buffer) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    address->house.street = strdup(buffer);

    if (!stream->_file)
    {
        printf("... the house number: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
        return IO_DATA_FORMAT_ERROR_ADDRESS_HOME;
    }
    address->house.house_num = (unsigned short) temp;

    if (!stream->_file)
    {
        printf("... the apartment number: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
        return IO_DATA_FORMAT_ERROR_ADDRESS_APRT;
    }
    address->house.apartment_num = (unsigned int) temp;

    return 0;
}

short get_table_data(table_t *table, FILE *stream)
{
    short int rc = 0;
    for (short i = 0; i < table->size; i++)
    {
        rc = get_student_data(table, stream, i);
        if (rc == IO_TABLE_DATA_READ_ERROR)
        {
            return IO_TABLE_DATA_READ_ERROR;
        }
        rc = get_date(&table->students[i]->date, stream, i);
        if (rc != 0)
        {
            return rc;
        }
        rc = get_address_state(table, stream, i);
        if (rc == IO_TABLE_DATA_READ_ERROR)
        {
            return IO_TABLE_DATA_READ_ERROR;
        }
        if (table->students[i]->is_dormitory)
        {
            rc = get_dormitory_data(&table->students[i]->address, stream);
            if (rc != 0)
            {
                return rc;
            }
        }
        else
        {
            rc = get_home_address(&table->students[i]->address, stream);
            if (rc != 0)
            {
                return rc;
            }
        }

        update_keys(table, i, i, table->students[i]->age);
    }

    return rc;
}

short load_file(table_t *table)
{
    short int rc;
    free_table(table);
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        return IO_ERROR;
    }
    rc = get_table_size(table, file);
    if (rc != 0)
    {
        return rc;
    }
    table->students = realloc(table->students, sizeof(student_t *) * table->size);
    table->keys = realloc(table->keys, sizeof(keys_t) * table->size);
    rc = get_table_data(table, file);
    if (rc != 0)
    {
        return rc;
    }

    fclose(file);
    printf("Done\n\n");
    return 0;
}

short append_student(table_t *table)
{
    int i = table->size;
    short int rc;
    table->size++;
    *table->students = realloc(*table->students, sizeof(student_t *) * (table->size));
    rc = get_student_data(table, stdin, i);
    if (rc == IO_TABLE_DATA_READ_ERROR)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    rc = get_date(&table->students[i]->date, stdin, i);
    if (rc != 0)
    {
        return rc;
    }
    rc = get_address_state(table, stdin, i);
    if (rc == IO_TABLE_DATA_READ_ERROR)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (table->students[i]->is_dormitory)
    {
        get_dormitory_data(&table->students[i]->address, stdin);
    }
    else
    {
        get_home_address(&table->students[i]->address, stdin);
    }

    update_keys(table, i, i, table->students[i]->age);

    printf("Done\n\n");
    return 0;
}

short delete_students(table_t *table)
{
    printf("Enter the age to delete: ");
    int age;
    if (scanf("%d", &age) != 1)
    {
        return IO_ERROR;
    }
    student_t **array = table->students;
    int j = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (array[j]->age == age)
        {
            remove_item(table, j);
        }
        else
        {
            j++;
        }

    }

    printf("Done\n\n");
    return 0;
}

void print_table(const table_t table, bool keys)
{
    puts("");

    for (int k = 0; k < table.size; k++)
    {
        int i = (keys) ? table.keys[k].id : k;

        printf("Surname: %10s | Name: %s\t| Group: %5hi | Sex: %6s | Age: %2d | Average score: %lf | "
               "Admission date: %2d %2d %4d | Address: %9s ",
               table.students[i]->surname, table.students[i]->name, table.students[i]->group,
               ((table.students[i]->sex) ? "Male" : "Female"), table.students[i]->age, table.students[i]->average_score,
               table.students[i]->date.day, table.students[i]->date.month, table.students[i]->date.year,
               ((table.students[i]->is_dormitory) ? "Dormitory" : "Home"));

        if (table.students[i]->is_dormitory)
        {
            printf("| Dormitory number: %5d | Room number: %d\n",
                   table.students[i]->address.dormitory.dormitory_num,
                   table.students[i]->address.dormitory.room_num);
        }
        else
        {
            printf("| Street: %15s | House: %d\t| Apartment: %d\n",
                   table.students[i]->address.house.street,
                   table.students[i]->address.house.house_num,
                   table.students[i]->address.house.apartment_num);
        }
    }
    printf("\n");
}

void print_table_keys(const table_t table)
{
    for (int i = 0; i < table.size; i++)
    {
        printf("Key: %3d | Age: %5d |\n", table.keys[i].id, table.keys[i].age);
    }
}

void print_sorts_vs_results(uint64_t total_ticks, short sort_type, short table_type)
{
    printf("Sorting %s with %s.\n", table_type ? "table" : "keys array", sort_type ? "QuickSort" : "bubble sort");
    printf("%Ild ticks, %.10lf seconds\n", total_ticks, (double) total_ticks / GHZ);
}

short specified_output(table_t table)
{
    int year;
    printf("Enter the year: ");
    if (scanf("%d", &year) != 1)
    {
        return IO_ERROR;
    }
    if (year <= 0)
    {
        return IO_DATE_FORMAT_ERROR_YEAR;
    }
    for (int i = 0; i < table.size; i++)
    {
        if (table.students[i]->date.year == year)
        {
            printf("Surname: %10s | Name: %s\t| Group: %5hi | Sex: %6s | Age: %2d | Average score: %lf | "
                   "Admission date: %2d %2d %4d | Address: %9s ",
                   table.students[i]->surname, table.students[i]->name, table.students[i]->group,
                   ((!table.students[i]->sex) ? "Female" : "Male"), table.students[i]->age,
                   table.students[i]->average_score,
                   table.students[i]->date.day, table.students[i]->date.month, table.students[i]->date.year,
                   ((table.students[i]->is_dormitory) ? "Dormitory" : "Home"));

            if (table.students[i]->is_dormitory)
            {
                printf("| Dormitory number: %5d | Room number: %d\n",
                       table.students[i]->address.dormitory.dormitory_num,
                       table.students[i]->address.dormitory.room_num);
            }
            else
            {
                printf("| Street: %15s | House: %d\t| Apartment: %d\n",
                       table.students[i]->address.house.street,
                       table.students[i]->address.house.house_num,
                       table.students[i]->address.house.apartment_num);
            }
        }
    }
    return 0;
}