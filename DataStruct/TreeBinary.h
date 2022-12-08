/**
 * 普通二叉树
 */

#ifndef TREE_BINARY_H
#define TREE_BINARY_H

#include <stdio.h>
#include <stdlib.h>

#define TREE_DEEP_MAX 10

typedef int TreeValue;
typedef struct _treeNode TreeNode;
typedef struct _tree Tree;

struct _treeNode
{
    TreeNode *left;
    TreeNode *right;
    TreeValue data;
};

struct _tree
{
    TreeNode *root;
    TreeNode *cur;
    unsigned int deep;
    unsigned int size;
};

/**
 * 函数声明列表#############################################################################
 */

Tree *tree_new();
int tree_insert_left(Tree *t, TreeNode *tn, TreeValue val);
int tree_insert_right(Tree *t, TreeNode *tn, TreeValue val);
void tree_preorder(TreeNode *tn);
void tree_inorder(TreeNode *tn);
void tree_postorder(TreeNode *tn);
void tree_from_array(Tree *tree, TreeValue value[], int size);

/**
 * 函数实现列表#############################################################################
 */

Tree *tree_new()
{
    Tree *t = (Tree *)malloc(sizeof(Tree));
    if (t == NULL)
    {
        return NULL;
    }
    t->deep = 0;
    t->size = 0;
    t->root = NULL;
    t->cur = NULL;

    return t;
}

int tree_root(Tree *t, TreeValue val)
{
    int result = -1;
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node != NULL)
    {
        node->data = val;
        node->left = NULL;
        node->right = NULL;

        t->root = node;
        t->size++;
        t->deep++;
        t->cur = node;
        result = 1;
    }
    return result;
}

int tree_insert_left(Tree *t, TreeNode *tn, TreeValue val)
{
    int result = -1;
    if (tn != NULL && tn->left == NULL)
    {
        TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
        if (node != NULL)
        {
            node->data = val;
            node->left = NULL;
            node->right = NULL;

            tn->left = node;
            t->size++;
            t->cur = node;
            result = 1;
        }
    }
    return result;
}

int tree_insert_right(Tree *t, TreeNode *tn, TreeValue val)
{
    int result = -1;
    if (tn != NULL && tn->right == NULL)
    {
        TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
        if (node != NULL)
        {
            node->data = val;
            node->left = NULL;
            node->right = NULL;

            tn->right = node;
            t->size++;
            t->cur = node;
            result = 1;
        }
    }
    return result;
}

void tree_preorder(TreeNode *tn)
{
    if (tn != NULL)
    {
        printf("%4d ", tn->data);
        tree_preorder(tn->left);
        tree_preorder(tn->right);
    }
}

void tree_inorder(TreeNode *tn)
{
    if (tn != NULL)
    {
        tree_inorder(tn->left);
        printf("%4d ", tn->data);
        tree_inorder(tn->right);
    }
}

void tree_postorder(TreeNode *tn)
{
    if (tn != NULL)
    {
        tree_postorder(tn->left);
        tree_postorder(tn->right);
        printf("%4d ", tn->data);
    }
}

void tree_from_array(Tree *tree, TreeValue value[], int size)
{
    TreeNode **nodes = (TreeNode **)malloc(sizeof(TreeNode *) * size);
    for (int i = 0; i < size; i++)
    {
        TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
        node->data = value[i];
        node->left = NULL;
        node->right = NULL;
        nodes[i] = node;
    }

    for (int i = 0; i < size / 2; i++)
    {
        if (nodes[i * 2 + 1] != NULL && (i * 2 + 1) < size)
        {
            nodes[i]->left = nodes[i * 2 + 1];
        }
        if (nodes[i * 2 + 2] != NULL && (i * 2 + 2) < size)
        {
            nodes[i]->right = nodes[i * 2 + 2];
        }
    }
    tree->root = nodes[0];
}

#endif // TREE_BINARY_H