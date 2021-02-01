//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#ifndef LAB_06_BIN_TREE_H
#define LAB_06_BIN_TREE_H

typedef struct tree_node tree_node_t;

struct tree_node
{
    int data;
    tree_node_t *left;
    tree_node_t *right;
    int height_difference;
};

tree_node_t *tree_find(tree_node_t *tree, int key);

tree_node_t *tree_insert(tree_node_t *tree, int val);

void draw_tree_hor(tree_node_t *tree, int depth, char *path, int right);

#endif //LAB_06_BIN_TREE_H
