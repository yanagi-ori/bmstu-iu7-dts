//
// Created by Ivan Bogatyrev on 1/29/2021.
//

#include "../../inc/bin_tree.h"
#include "../../inc/balanced_tree.h"

int get_height(tree_node_t *tree)
{
    return (tree) ? tree->crit : 0;
}

int tree_bfactor(tree_node_t *tree)
{
    return get_height(tree->right) - get_height(tree->left);
}

void tree_fix_height(tree_node_t *p)
{
    int hl = get_height(p->left);
    int hr = get_height(p->right);

    p->crit = (hl > hr ? hl : hr) + 1;
}

tree_node_t *tree_rotate_left(tree_node_t *q)
{
    tree_node_t *p = q->right;

    q->right = p->left;
    p->left = q;

    tree_fix_height(q);
    tree_fix_height(p);

    return p;
}

tree_node_t *tree_rotate_right(tree_node_t *p)
{
    tree_node_t *q = p->left;

    p->left = q->right;
    q->right = p;

    tree_fix_height(p);
    tree_fix_height(q);

    return q;
}

tree_node_t *balance_node(tree_node_t *node)
{
    tree_fix_height(node);

    if (tree_bfactor(node) == 2)
    {
        if (tree_bfactor(node->right) < 0)
        {
            node->right = tree_rotate_right(node->right);
        }
        return tree_rotate_left(node);
    }

    if (tree_bfactor(node) == -2)
    {
        if (tree_bfactor(node->left) > 0)
        {
            node->left = tree_rotate_left(node->left);
        }
        return tree_rotate_right(node);
    }

    return node;
}