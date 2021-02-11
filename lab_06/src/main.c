#include <stdio.h>
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/timer.h"
#include "../inc/balanced_tree.h"
#include "../inc/hash_table.h"
#include "../inc/memory_management.h"

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
    printf("Simple hash function generation in %llu ticks\n", get_time(timer));

    timer.start = tick();
    hash_func_complicated(1234, table_size);
    timer.end = tick();
    printf("Complicated hash function generation in %llu ticks\n", get_time(timer));

    hash_table_t *table = ht_init(table_size);

    int coll = 0;

    timer.start = tick();
    for (int i = 0; i < file_len; i++)
    {
        int tmp_coll = ht_insert(table, arr[i], hash_func_simple);
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


    printf("Enter the number you wanna delete:\n");
    int user_search;
    int rc = scanf("%d", &user_search);
    if (rc == 1)
    {
        int comparisons = 1;
        bool deleted = false;
        timer.start = tick();
        tree_delete_cmp(bin_tree, user_search, &comparisons, &deleted);
        timer.end = tick();

        printf("Search results in binary tree: \n");
        if (deleted == true)
        {
            printf("The number \"%d\" was deleted in %llu CPU ticks\n", user_search, get_time(timer));
        }
        else
        {
            printf("The number wasn't found in the tree\n");
        }
        printf("The number of comparisons: %d\n", comparisons);
        printf("The size of binary tree data: %zu bytes\n", sizeof(tree_node_t) * file_len);
        printf("It takes %llu CPU ticks in average to find any number in binary tree\n",
               tree_search_performance_test(arr, file_len, no_balance));
        printf("Average number of comparisons for every number in tree %f\n\n",
               tree_search_cmp_avg(bin_tree, arr, file_len));


        timer.start = tick();
        comparisons = 1;
        deleted = false;
        tree_delete_cmp(balanced_tree, user_search, &comparisons, &deleted);

        timer.end = tick();
        printf("Search results in balanced binary tree: \n");
        if (deleted == false)
        {
            printf("The number wasn't found in the tree\n");
        }
        else
        {
            printf("The number \"%d\" was deleted in %llu CPU ticks\n", user_search, get_time(timer));
        }
        printf("The number of comparisons: %d\n", comparisons);
        printf("It takes %llu CPU ticks in average to find any number in balanced binary tree\n",
               tree_search_performance_test(arr, file_len, balance_node));
        printf("Average number of comparisons for every number in balanced tree %f\n\n",
               tree_search_cmp_avg(balanced_tree, arr, file_len));


        printf("Search results in hashtable:\n");
        printf("Enter the limit of comparisons: \n");
        int temp = user_search;
        short limit;
        rc = scanf("%d", &limit);
        user_search = temp;
        if (rc == 1 && limit > 0)
        {
            unsigned (*hash_func)(int, unsigned) = hash_func_simple;
            comparisons = ht_find(table, user_search, hash_func);
            if (comparisons > limit || comparisons <= 0)
            {
                printf("The number of comparisons got over the limit you entered. Restructuring the table...\n");
                while (comparisons > limit || comparisons <= 0)
                {
                    ht_clean(table);
                    table_size = next_prime((2 * table_size) + 1);
                    table = ht_init(table_size);
                    hash_func = hash_func_complicated;

                    coll = 0;

                    timer.start = tick();
                    for (int i = 0; i < file_len; i++)
                    {
                        ht_insert(table, arr[i], hash_func);
                    }
                    timer.end = tick();
                    printf("Restructured in %llu CPU ticks\nChecking the performance...\n", get_time(timer));
                    timer.start = tick();
                    comparisons = ht_find(table, user_search, hash_func_simple);
                    timer.end = tick();
                    if (comparisons > limit || comparisons <= 0)
                    {
                        printf("The number (%d) of comparisons got over the limit you entered. "
                               "Trying again...\n", comparisons);
                    }
                }
            }

            int hash_e_size = sizeof(hash_item_t);
            int hash_t_size = sizeof(hash_table_t);
            printf("The number of comparisons: %d\n", comparisons);
            printf("The size of binary tree data: %llu bytes\n",
                   sizeof(hash_item_t) * table->len + sizeof(hash_table_t));
            printf("It takes %llu CPU ticks in average to find any number in binary tree\n",
                   ht_search_performance_test(table, arr, file_len, hash_func));
            printf("Average number of comparisons for every number in tree %f\n\n",
                   ht_search_cmp_avg(table, arr, file_len, hash_func));
        }
        else
        {
            fprintf(stderr, "Entered invalid limit number");
        }

    }
    else
    {
        fprintf(stderr, "Entered invalid number");
    }


    free_tree(bin_tree);
    free_tree(balanced_tree);
    ht_clean(table);
    return 0;
}
