//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#ifndef LAB_06_BIN_TREE_H
#define LAB_06_BIN_TREE_H

#include <stdbool.h>

typedef struct tree_node tree_node_t;

struct tree_node
{
    int data;
    tree_node_t *left;
    tree_node_t *right;
    int crit;
};

tree_node_t *tree_find(tree_node_t *tree, int key);

//tree_node_t *tree_delete(tree_node_t *tree, int key);

tree_node_t *tree_insert(tree_node_t *tree, int val, tree_node_t* (*func)(tree_node_t *));

void draw_tree_hor(tree_node_t *tree, int depth, char *path, int right);

tree_node_t *no_balance(tree_node_t *tree);

tree_node_t *tree_delete_cmp(tree_node_t *tree, int key, int *cmps, bool *status);

#endif //LAB_06_BIN_TREE_H
