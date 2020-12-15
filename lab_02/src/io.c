//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/structures.h"
#include "../inc/io.h"
#include "../inc/errors.h"

short int menu(short int *action)
{
    {
        printf("Menu: \n");
        printf("1. Load data from file;\n");
        printf("2. Add student to the bottom of the table;\n");
        printf("3. Delete students by the value;\n");
        printf("4. Show sorted by average score table;\n");
        printf("5. Вывести упорядоченную (по площади) таблицу.\n");
        printf("6. Вывести упорядоченную таблицу (по площади), используя упорядоченый массив ключей.\n");
        printf("7. Вывести результаты сравнения эффективности программы при обработке таблицы и массив ключей.\n");
        printf("8. Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных.\n");
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

short int get_table_size(table_t *table, FILE *file)
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

short int get_date(date_t *date, FILE *stream, int i)
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

short int get_student_data(table_t *table, FILE *stream, int i)
{
    char buffer[100];
    int temp;
    int rc;

    student_t *temp_student = malloc(sizeof(student_t));

    if (!stream->_file)
    {
        printf("Enter the student's surname: ");
    }
    if (fscanf(stream, "%s", buffer) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->surname = strdup(buffer);

    if (!stream->_file)
    {
        printf("Enter the student's name: ");
    }
    if (fscanf(stream, "%s", buffer) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->name = strdup(buffer);

    if (!stream->_file)
    {
        printf("Enter the student's group number: ");
    }
    if (fscanf(stream, "%d", &temp) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->group = (short) temp;

    if (!stream->_file)
    {
        printf("Enter the student's sex ( m / f ): ");
    }
    if (fscanf(stream, "%s", buffer) != 1)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (strlen(buffer) != 1 || (buffer[0] != 'm' && buffer[0] != 'f'))
    {
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
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp <= 0)
    {
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
        return IO_TABLE_DATA_READ_ERROR;
    }
    if (temp_score <= 0)
    {
        return IO_TABLE_DATA_READ_ERROR;
    }
    temp_student->average_score = temp_score;

    table->students[i] = temp_student;

    return 0;
}

short int get_address_state(table_t *table, FILE *stream, int i)
{
    char buffer[100];

    if (!stream->_file)
    {
        printf("Enter the address status ([d]ormitory or [h]ome): ");
    }
    if (fscanf(stream, "%s", buffer) != 1)
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

short int get_dormitory_data(address_t *address, FILE *stream)
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

short int get_home_address(address_t *address, FILE *stream)
{
    char buffer[100];
    int temp;

    if (!stream->_file)
    {
        printf("Please, enter the street: ");
    }
    if (fscanf(stream, "%s", buffer) != 1)
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

short int get_table_data(table_t *table, FILE *stream)
{
    short int rc = 0;
    for (int i = 0; i < table->size; i++)
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
            get_dormitory_data(&table->students[i]->address, stream);
            printf("%s %s %d %d %d %lf %d %d %d dormitory %d %d\n",
                   table->students[i]->surname, table->students[i]->name, table->students[i]->group,
                   table->students[i]->sex, table->students[i]->age, table->students[i]->average_score,
                   table->students[i]->date.day, table->students[i]->date.month, table->students[i]->date.year,
                   table->students[i]->address.dormitory.dormitory_num, table->students[i]->address.dormitory.room_num
            );
        }
        else
        {
            get_home_address(&table->students[i]->address, stream);
            printf("%s %s %d %d %d %lf %d %d %d home %s %d %d\n",
                   table->students[i]->surname, table->students[i]->name, table->students[i]->group,
                   table->students[i]->sex, table->students[i]->age, table->students[i]->average_score,
                   table->students[i]->date.day, table->students[i]->date.month, table->students[i]->date.year,
                   table->students[i]->address.house.street, table->students[i]->address.house.house_num,
                   table->students[i]->address.house.apartment_num
            );
        }
    }


    return rc;
}

short int load_file(table_t *table)
{
    short int rc;
    //TODO: clear table
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
    *table->students = malloc(sizeof(student_t *) * table->size);
    rc = get_table_data(table, file);
    if (rc != 0)
    {
        return rc;
    }

    return 0;
}