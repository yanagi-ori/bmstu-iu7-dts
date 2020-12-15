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
