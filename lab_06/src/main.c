#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/timer.h"
#include "../inc/bin_tree.h"
#include "../inc/balanced_tree.h"

int main(int argc, char **argv)
{
    printf("Lab 06. Graphs & Hash-Tables.\n");
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments");
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Invalid file");
        return IO_ERROR;
    }

    int *arr;
    int file_len = data_extract(file, &arr);
    if (file_len == EMPTY_FILE)
    {
        fprintf(stderr, "The file is empty");
        return EMPTY_FILE;
    }
    if (file_len == MEMORY_ALLOCATION_ERROR)
    {
        fprintf(stderr, "Memory allocation error");
    }
    if (file_len == INVALID_FILE)
    {
        fprintf(stderr, "Could not read the file to the end");
    }

    tree_node_t *bin_tree = NULL;
    timer_t timer;
    timer.start = tick();
    for (int i = 0; i < file_len; i++)
    {
        if (tree_find(bin_tree, arr[i]) == NULL)
        {
            bin_tree = tree_insert(bin_tree, arr[i], no_balance);
        }
    }
    timer.end = tick();
    printf("The binary tree was built in %llu ticks\n", get_time(timer));
    draw_tree_hor(bin_tree, 0, NULL, 0);

    tree_node_t *balanced_tree = NULL;
    timer.start = tick();
    for (int i = 0; i < file_len; i++)
    {
        if (tree_find(balanced_tree, arr[i]) == NULL)
        {
            balanced_tree = tree_insert(balanced_tree, arr[i], balance_node);
        }
    }
    timer.end = tick();
    printf("The binary tree was balanced in %llu ticks\n", get_time(timer));
    draw_tree_hor(balanced_tree, 0, NULL, 0);

    return 0;
}
