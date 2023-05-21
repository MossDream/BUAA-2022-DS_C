#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} node;
void create_binary_search_tree(node **root, int data, int height)
{
    if (*root == NULL)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->data = data;
        temp->height = height;
        temp->left = temp->right = NULL;
        *root = temp;
    }
    else
    {
        if (data < (*root)->data)
        {
            create_binary_search_tree(&(*root)->left, data, height + 1);
        }
        else if (data >= (*root)->data)
        {
            create_binary_search_tree(&(*root)->right, data, height + 1);
        }
    }
}
void preorder(node *root)
{
    if (root)
    {
        if (root->left == NULL && root->right == NULL)
        {
            printf("%d %d\n", root->data, root->height);
        }
        preorder(root->left);
        preorder(root->right);
    }
}
int main()
{
    int n = 0;
    scanf("%d", &n);
    int i = 0;
    node *root = NULL;
    int data = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &data);
        create_binary_search_tree(&root, data, 1);
    }
    preorder(root);
    return 0;
}