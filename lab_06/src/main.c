#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/timer.h"
#include "../inc/bin_tree.h"
#include "../inc/balanced_tree.h"
#include "../inc/hash_table.h"

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

    unsigned int table_size = next_prime((unsigned) file_len);
    timer.start = tick();
    hash_func_simple(1234, table_size);
    timer.end = tick();
    printf("Simple hashtable generation in %llu ticks\n", get_time(timer));

    timer.start = tick();
    hash_func_complicated(1234, table_size);
    timer.end = tick();
    printf("Complicated hashtable generation in %llu ticks\n", get_time(timer));

    hash_table_t *table = ht_init(table_size);

    int coll = 0;

    timer.start = tick();
    for (int i = 0; i < file_len; i++)
    {
        int tmp_coll = hash_insert(table, arr[i], hash_func_simple);
        if (tmp_coll == HASH_END)
        {
            return HASH_END;
        }
        coll = coll > tmp_coll ? coll : tmp_coll;
    }

    timer.end = tick();

    ht_print(table);

    printf("Max number of collisions: %d\n", coll);
    printf("Hashtable was generated in %llu ticks.\n", get_time(timer));


    printf("Enter the number you wanna find:\n");
    int user_search;
    int rc = scanf("%d", &user_search);
    if (rc == 1)
    {

        timer.start = tick();
        int comparisons = tree_find_cmp(bin_tree, user_search);
        timer.end = tick();

        printf("Search results in binary tree: \n");
        if (comparisons > 0)
        {
            printf("The number \"%d\" was found in %llu CPU ticks\n", user_search, get_time(timer));
        }
        else
        {
            printf("The number wasn't found in the tree\n");
        }
        printf("The number of comparisons: %d\n", comparisons);
        printf("The size of binary tree data: %zu bytes\n", sizeof(tree_node_t) * file_len);
        printf("It takes %llu CPU ticks in average to find any number in binary tree\n",
               tree_search_performance_test(bin_tree, arr, file_len));
        printf("Average number of comparisons for every number in tree %f\n\n",
               tree_search_cmp_avg(bin_tree, arr, file_len));


        timer.start = tick();
        comparisons = tree_find_cmp(balanced_tree, user_search);
        timer.end = tick();
        printf("Search results in balanced binary tree: \n");
        if (comparisons > 0){
            printf("The number \"%d\" was found in %llu CPU ticks\n", user_search, get_time(timer));
        }
        else
        {
            printf("The number wasn't found in the tree\n");
        }
        printf("The number of comparisons: %d\n", comparisons);
        printf("The size of binary tree data: %zu bytes\n", sizeof(tree_node_t) * file_len);
        printf("It takes %llu CPU ticks in average to find any number in binary tree\n",
               tree_search_performance_test(balanced_tree, arr, file_len));
        printf("Average number of comparisons for every number in tree %f\n\n",
               tree_search_cmp_avg(balanced_tree, arr, file_len));
    }
    else
    {
        fprintf(stderr, "Entered invalid number");
    }


    ht_clean(table);
    return 0;
}
