#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct choose
{
    int num;
    char op;
} choose;
typedef struct Tree_node
{
    choose data;
    struct Tree_node *left;
    struct Tree_node *right;
} Tree;
void build_expreeion_tree(choose *back_formula, int backnum, Tree **root, Tree **stack)
{
    int i = 0;
    int top = -1;
    for (i = 0; i < backnum; i++)
    {
        if (back_formula[i].op == 0)
        {
            Tree *temp = (Tree *)malloc(sizeof(Tree));
            temp->data.num = back_formula[i].num;
            temp->data.op = 0;
            temp->left = temp->right = NULL;
            *root = temp;
            top++;
            stack[top] = temp;
        }
        else
        {
            Tree *temp = (Tree *)malloc(sizeof(Tree));
            temp->data.op = back_formula[i].op;
            temp->right = stack[top];
            stack[top] = NULL;
            top--;
            temp->left = stack[top];
            stack[top] = NULL;
            top--;
            *root = temp;
            top++;
            stack[top] = temp;
        }
    }
}
int count_expression_tree(Tree *root)
{
    if (root->data.op == 0)
    {
        return root->data.num;
    }
    else
    {
        switch (root->data.op)
        {
        case '+':
            return count_expression_tree(root->left) + count_expression_tree(root->right);
            break;
        case '-':
            return count_expression_tree(root->left) - count_expression_tree(root->right);
            break;
        case '*':
            return count_expression_tree(root->left) * count_expression_tree(root->right);
            break;
        case '/':
            return count_expression_tree(root->left) / count_expression_tree(root->right);
            break;
        }
    }
}
int main()
{

    Tree *stack[100] = {0};
    Tree *root = NULL;
    char mid_formula[500] = {0};
    choose back_formula[500] = {0};
    char op_stack[500] = {0};

    gets(mid_formula);

    int i = 0;
    int backnum = 0;
    int op_top = -1;

    while (mid_formula[i] != '=')
    {
        if (mid_formula[i] == ' ')
        {
            i++;
            continue;
        }
        else if (isdigit(mid_formula[i]))
        {
            back_formula[backnum].num = mid_formula[i] - '0';
            while (isdigit(mid_formula[i + 1]))
            {
                back_formula[backnum].num = back_formula[backnum].num * 10 + (mid_formula[i + 1] - '0');
                i++;
            }
            backnum++;
        }
        else if (mid_formula[i] == '(')
        {
            op_top++;
            op_stack[op_top] = mid_formula[i];
        }
        else if (mid_formula[i] == ')')
        {
            while (op_stack[op_top] != '(')
            {
                back_formula[backnum].op = op_stack[op_top];
                op_stack[op_top] = 0;
                op_top--;
                backnum++;
            }
            op_stack[op_top] = 0;
            op_top--;
        }
        else if (mid_formula[i] == '+' || mid_formula[i] == '-' || mid_formula[i] == '*' || mid_formula[i] == '/')
        {
            if (op_top == -1)
            {
                op_top++;
                op_stack[op_top] = mid_formula[i];
            }
            else
            {
                if (mid_formula[i] == '+' || mid_formula[i] == '-')
                {
                    while (op_stack[op_top] != '(' && op_top != -1)
                    {
                        back_formula[backnum].op = op_stack[op_top];
                        op_stack[op_top] = 0;
                        op_top--;
                        backnum++;
                    }
                    op_top++;
                    op_stack[op_top] = mid_formula[i];
                }
                else if (mid_formula[i] == '*' || mid_formula[i] == '/')
                {
                    while ((op_stack[op_top] == '*' || op_stack[op_top] == '/') && op_top != -1)
                    {
                        back_formula[backnum].op = op_stack[op_top];
                        op_stack[op_top] = 0;
                        op_top--;
                        backnum++;
                    }
                    op_top++;
                    op_stack[op_top] = mid_formula[i];
                }
            }
        }
        i++;
    }
    while (op_top != -1)
    {
        back_formula[backnum].op = op_stack[op_top];
        op_stack[op_top] = 0;
        op_top--;
        backnum++;
    }
    build_expreeion_tree(back_formula, backnum, &root, &stack[0]);
    if (root != NULL)
    {
        if (root->data.op == 0)
        {
            printf("%d ", root->data.num);
        }
        else
        {
            printf("%c ", root->data.op);
        }
    }
    if (root->left != NULL)
    {
        if (root->left->data.op == 0)
        {
            printf("%d ", root->left->data.num);
        }
        else
        {
            printf("%c ", root->left->data.op);
        }
    }
    if (root->right != NULL)
    {
        if (root->right->data.op == 0)
        {
            printf("%d ", root->right->data.num);
        }
        else
        {
            printf("%c ", root->right->data.op);
        }
    }
    printf("\n");
    printf("%d", count_expression_tree(root));
    return 0;
}