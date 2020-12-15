#include <stdio.h>
#include <stdlib.h>
#include "../inc/errors.h"
#include "../inc/structures.h"
#include "../inc/table_utils.h"
#include "../inc/io.h"
#include "../inc/sort.h"


int main()
{
    table_t table;

    short int action, rc;
    bool keys_sorted = false;
    bool table_sorted = false;

    rc = table_init(&table);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    while (true)
    {
        rc = menu(&action);
        if (rc)
        {
            fprintf(stderr, "Invalid menu number\n");
            return rc;
        }

        switch (action)
        {
            case 1:
                rc = load_file(&table);
                if (rc != 0)
                {
                    return rc;
                }
                keys_sorted = false;
                table_sorted = false;
                break;
            case 2:
                rc = append_student(&table);
                if (rc != 0)
                {
                    return rc;
                }
                keys_sorted = false;
                table_sorted = false;
                break;
            case 3:
                rc = delete_students(&table);
                if (rc != 0)
                {
                    return rc;
                }
                break;
            case 4:
                if (!table.students[0] || !table.size)
                {
                    return TABLE_IS_EMPTY;
                }
                qsort(table.keys, table.size, sizeof(keys_t), comparator_keys);
                keys_sorted = true;
                print_table_keys(table);
                break;
            case 5:
                if (!table.students[0] || !table.size)
                {
                    return TABLE_IS_EMPTY;
                }
                qsort(table.students, table.size, sizeof(student_t *), comparator_table);
                table_sorted = true;
                print_table(table, false);
                break;
            case 6:
                if (!table.students[0] || !table.size)
                {
                    return TABLE_IS_EMPTY;
                }
                if (table_sorted)
                {
                    rc = load_file(&table);
                    if (rc != 0)
                    {
                        return rc;
                    }
                    keys_sorted = false;
                    table_sorted = false;
                }
                if (!keys_sorted)
                {
                    qsort(table.students, table.size, sizeof(student_t *), comparator_table);
                    keys_sorted = true;
                }
                print_table(table, true);
                break;
            case 7:
                if (!table.students[0] || !table.size)
                {
                    return TABLE_IS_EMPTY;
                }
                qs_vs_bubble(&table);
                break;
            case 8:
                if (!table.students[0] || !table.size)
                {
                    return TABLE_IS_EMPTY;
                }
                rc = specified_output(table);
                if (rc != 0)
                {
                    return rc;
                }
                break;
            case 9:
                if (!table.students[0] || !table.size)
                {
                    return TABLE_IS_EMPTY;
                }
                print_table(table, false);
                break;
            case 0:
                if (table.students[0])
                {
                    free_table(&table);
                }
                return 0;
            default:
                if (table.students[0])
                {
                    free_table(&table);
                    free(table.students);
                }
                printf("Invalid menu number\n");
                return INVALID_INPUT_DATA;
        }
    }
}
