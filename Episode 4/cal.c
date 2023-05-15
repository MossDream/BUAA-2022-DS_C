#include <stdio.h>
#include <ctype.h>
#include <string.h>
typedef struct choose
{
    int num;
    char op;
} choose;
int main()
{
    char mid_formula[500] = {0};
    choose back_formula[500] = {0};
    char op_stack[500] = {0};
    double num_stack[500] = {0.0};

    gets(mid_formula);

    int i = 0;
    int backnum = 0;
    int op_top = -1;
    int num_top = -1;

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
    for (i = 0; i < backnum; i++)
    {
        if (back_formula[i].op == 0)
        {
            num_top++;
            num_stack[num_top] = back_formula[i].num;
        }
        else
        {
            double num1 = num_stack[num_top];
            num_stack[num_top] = 0.0;
            num_top--;
            double num2 = num_stack[num_top];
            num_stack[num_top] = 0.0;
            num_top--;
            if (back_formula[i].op == '+')
            {
                num_stack[++num_top] = num1 + num2;
            }
            else if (back_formula[i].op == '-')
            {
                num_stack[++num_top] = num2 - num1;
            }
            else if (back_formula[i].op == '*')
            {
                num_stack[++num_top] = num1 * num2;
            }
            else if (back_formula[i].op == '/')
            {
                num_stack[++num_top] = num2 / num1;
            }
        }
    }
    printf("%.2f", num_stack[num_top]);
    return 0;
}