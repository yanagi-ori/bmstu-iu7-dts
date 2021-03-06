//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "../../inc/bin_tree.h"
#include <stdbool.h>
#include "../../inc/balanced_tree.h"

#define NUM_OF_SPACES    5


tree_node_t *tree_find(tree_node_t *tree, int key)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (tree->data == key)
    {
        return tree;
    }

    if (tree->data < key)
    {
        return tree_find(tree->right, key);
    }

    if (tree->data > key)
    {
        return tree_find(tree->left, key);
    }

    return NULL;
}

tree_node_t *min_node(tree_node_t *tree)
{
    tree_node_t *current = tree;
    while (current && current->left)
    {
        current = current->left;
    }
    return current;
}

tree_node_t *init_node(int val)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));

    if (node == NULL)
    {
        return NULL;
    }

    node->crit = 1;
    node->data = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

tree_node_t *no_balance(tree_node_t *tree)
{
    return tree;
}

tree_node_t *tree_insert(tree_node_t *tree, int val, tree_node_t *(*func)(tree_node_t *))
{
    if (tree == NULL)
    {
        return init_node(val);
    }

    if (val < tree->data)
    {
        tree->left = tree_insert(tree->left, val, func);
    }
    else
    {
        tree->right = tree_insert(tree->right, val, func);
    }

    return func(tree);
}

void draw_tree_hor(tree_node_t *tree, int depth, char *path, int right)
{
    if (path == NULL)
    {
        path = malloc(sizeof(char) * 2048);

        if (path == NULL)
        {
            return;
        }
        draw_tree_hor(tree, 0, path, 0);
        free(path);
    }
    else
    {
        if (tree == NULL)
        {
            return;
        }

        depth++;

        draw_tree_hor(tree->right, depth, path, 1);

        if (depth > 1)
        {
            path[depth - 2] = 0;

            if (right)
            {
                path[depth - 2] = 1;
            }
        }

        if (tree->left)
        {
            path[depth - 1] = 1;
        }

        printf("\n");

        for (int i = 0; i < depth - 1; i++)
        {
            if (i == depth - 2)
            {
                printf("+");
            }
            else if (path[i])
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }

            for (int j = 1; j < NUM_OF_SPACES; j++)
            {
                if (i < depth - 2)
                {
                    printf(" ");
                }
                else
                {
                    printf("-");
                }
            }
        }

        printf("[%d]\n", tree->data);

        for (int i = 0; i < depth; i++)
        {
            if (path[i])
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }

            for (int j = 1; j < NUM_OF_SPACES; j++)
            {
                printf(" ");
            }
        }

        draw_tree_hor(tree->left, depth, path, 0);
    }
}

tree_node_t *tree_delete_cmp(tree_node_t *tree, int key, int *cmps, bool *status)
{
    if (tree == NULL)
    {
        return tree;
    }
    if (key < tree->data)
    {
        (*cmps)++;
        tree->left = tree_delete_cmp(tree->left, key, cmps, status);
    }
    else if (key > tree->data)
    {
        (*cmps)++;
        tree->right = tree_delete_cmp(tree->right, key, cmps, status);
    }
    else if (tree->left != NULL && tree->right != NULL)
    {
        *status = true;
        tree->data = min_node(tree->right)->data;
        tree->right = tree_delete_cmp(tree->right, tree->data, cmps, status);
    }
    else
    {
        if (!tree->left)
        {
            *status = true;
            tree = tree->left;
        }
        else if (!tree->right && tree->left)
        {
            *status = true;
            tree = tree->right;
        }
        else
        {
            *status = true;
            tree = NULL;
        }
    }
    return tree;
}
