//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include <stdlib.h>
#include "../../inc/bin_tree.h"

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

tree_node_t *init_node(int val)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));

    if (node == NULL)
        return NULL;

    node->height_difference = 1;
    node->data = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}


tree_node_t *tree_insert(tree_node_t *tree, int val)
{
    if (tree == NULL)
        return init_node(val);

    if (val < tree->data)
        tree->left = tree_insert(tree->left, val);
    else
        tree->right = tree_insert(tree->right, val);

    return tree;
}