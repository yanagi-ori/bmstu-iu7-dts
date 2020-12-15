#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/structures.h"
#include "../inc/table_utils.h"
#include "../inc/io.h"


int main()
{
    table_t table;

    short int action, rc;

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
                break;
            case 2:
                rc = append_student(&table);
                if (rc != 0)
                {
                    return rc;
                }
                break;
            case 3:
                rc = delete_students(&table);
                if (rc != 0)
                {
                    return rc;
                }
                break;
            case 9:
                if (!table.students[0])
                { return TABLE_IS_EMPTY; }
                print_table(table, false);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid menu number\n");
                return INVALID_INPUT_DATA;
        }
    }
}
