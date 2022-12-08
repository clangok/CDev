#include <stdio.h>
#include "TreeBinary.h"

int main(void)
{

    int size = 32;
    TreeValue value[size];
    for (int i = 0; i < size; i++)
    {
        value[i] = i;
    }
    Tree *tree = tree_new();
    tree_from_array(tree, value, size);

    /**
        char a[] = "wang", b[] = "lin", c[] = "qiang", d[] = "ziluo", e[] = "xiaoyan";
        tree_root(tree, a);
        tree_insert_left(tree, tree->root, b);
        tree_insert_right(tree, tree->cur, c);
        tree_insert_right(tree, tree->root, d);
        tree_insert_right(tree, tree->root->right, e);
    */
    printf("Tree p=%p\n", tree);
    printf("Tree->root=%p\n", tree->root);
    printf("Tree->cur=%p\n", tree->cur);
    tree_inorder(tree->root->right);
}