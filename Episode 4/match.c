#include <stdio.h>
#include <string.h>
typedef struct unit
{
    char s;
    int num;
} unit;
int main()
{
    FILE *fpr = fopen("example.c", "r");
    if (fpr == NULL)
    {
        perror("In open file example.c:");
    }
    char line[200] = {0};
    int linenum = 0;

    int i = 0;

    int single_qoute = 0;
    int double_qoute = 0;
    int double_comment = 0;

    unit stack[500] = {0};
    int top = -1;

    char final[500] = {0};
    int finalnum = 0;

    while (fgets(line, 200, fpr) != NULL)
    {
        linenum++;
        for (i = 0; i < strlen(line); i++)
        {
            if (double_comment)
            {
                if (line[i] == '*' && line[i + 1] == '/')
                {
                    double_comment = 0;
                    i++;
                }
                continue;
            }
            else if (single_qoute)
            {
                if (line[i] == '\'')
                {
                    single_qoute = 0;
                }
                continue;
            }
            else if (double_qoute)
            {
                if (line[i] == '\"')
                {
                    double_qoute = 0;
                }
                continue;
            }
            else
            {
                if (line[i] == '\'')
                {
                    single_qoute = 1;
                }
                else if (line[i] == '\"')
                {
                    double_qoute = 1;
                }
                else if (i < strlen(line) - 1 && line[i] == '/' && line[i + 1] == '/')
                {
                    break;
                }
                else if (i < strlen(line) - 1 && line[i] == '/' && line[i + 1] == '*')
                {
                    double_comment = 1;
                    i++;
                }
                else if (line[i] == '(')
                {
                    top++;
                    stack[top].s = line[i];
                    stack[top].num = linenum;
                    final[finalnum++] = line[i];
                }
                else if (line[i] == '{')
                {
                    if (top != -1 && stack[top].s == '(')
                    {
                        printf("without maching '(' at line %d", stack[top].num);
                        return 0;
                    }
                    else
                    {
                        top++;
                        stack[top].s = line[i];
                        stack[top].num = linenum;
                    }
                    final[finalnum++] = '{';
                }
                else if (line[i] == ')')
                {
                    if (top != -1 && stack[top].s == '(')
                    {
                        top--;
                    }
                    else
                    {
                        printf("without maching ')' at line %d", linenum);
                        return 0;
                    }
                    final[finalnum++] = ')';
                }
                else if (line[i] == '}')
                {
                    if (top != -1 && stack[top].s == '{')
                    {
                        top--;
                    }
                    else
                    {
                        printf("without maching '}' at line %d", linenum);
                        return 0;
                    }
                    final[finalnum++] = '}';
                }
            }
        }
    }
    if (top == -1)
    {
        printf("%s", final);
    }
    else
    {
        printf("without maching '%c' at line %d", stack[0].s, stack[0].num);
    }
    fclose(fpr);
    fpr = NULL;
    return 0;
}