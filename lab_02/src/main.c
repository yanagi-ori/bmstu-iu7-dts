#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/structures.h"
#include "../inc/table_utils.h"
#include "../inc/io.h"


int main()
{
    table_t table;
    student_t *students_arr = NULL;
    keys_t *keys_arr = NULL;

    table_init(&table, students_arr, keys_arr);

    short int action, rc;

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
                rc = load_file();
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                return INVALID_INPUT_DATA;
        }
        break;

    }

    return 0;
}
