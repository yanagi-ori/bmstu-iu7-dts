//
// Created by Ivan Bogatyrev on 12/14/2020.
//

#include <stdio.h>
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
    if (fscanf(file, "%hi", &table->size) != 0)
    {
        return IO_FILE_SIZE_ERROR;
    }
    if (table->size < 1)
    {
        return IO_FILE_SIZE_ERROR;
    }
    return 0;
}

short int get_table_data(table_t *table, FILE *file){

    return 0;
}

short int load_file(table_t *table)
{
    //TODO: clear table
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        return IO_ERROR;
    }
    if (get_table_size(table, file) != 0)
    {
        return IO_FILE_SIZE_ERROR;
    }

    return 0;
}