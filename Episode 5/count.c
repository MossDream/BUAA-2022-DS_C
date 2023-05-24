#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct Tree_node
{
    char word[50];
    int count;
    struct Tree_node *left;
    struct Tree_node *right;
} Tree;
void create_binary_search_tree(Tree **root, char *word)
{
    if (*root == NULL)
    {
        Tree *temp = (Tree *)malloc(sizeof(Tree));
        strcpy(temp->word, word);
        temp->count = 1;
        temp->left = temp->right = NULL;
        *root = temp;
    }
    else
    {
        if (strcmp(word, (*root)->word) < 0)
        {
            create_binary_search_tree(&(*root)->left, word);
        }
        else if (strcmp(word, (*root)->word) > 0)
        {
            create_binary_search_tree(&(*root)->right, word);
        }
        else
        {
            (*root)->count++;
        }
    }
}
void inorder(Tree *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%s %d\n", root->word, root->count);
        inorder(root->right);
    }
}
int main()
{
    FILE *fp = fopen("article.txt", "r");
    if (fp == NULL)
    {
        printf("File not found");
        return 0;
    }
    char word[50] = {0};
    char c = 0;
    int num = 0;
    Tree *root = NULL;
    while ((c = fgetc(fp)) != EOF)
    {
        if (isalpha(c))
        {
            while (isalpha(c))
            {
                word[num++] = tolower(c);
                c = fgetc(fp);
            }
            word[num] = '\0';
            create_binary_search_tree(&root, word);
            for (int i = 0; i < num; i++)
            {
                word[i] = 0;
            }
            num = 0;
        }
    }
    if (root != NULL)
    {
        printf("%s ", root->word);
    }
    if (root->right != NULL)
    {
        printf("%s ", root->right->word);
    }
    if (root->right->right != NULL)
    {
        printf("%s ", root->right->right->word);
    }
    printf("\n");
    inorder(root);
    fclose(fp);
    fp = NULL;
    return 0;
}