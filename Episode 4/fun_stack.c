#include <stdio.h>
#include <string.h>
typedef struct fun
{
    char name[30];
    char call_info[10][30];
    int call_num;
} fun;
int fun_num = 0;
int find_fun_name(fun *print, char *fun_name)
{
    int i = 0;
    for (i = 0; i < fun_num; i++)
    {
        if (strcmp(print[i].name, fun_name) == 0)
        {
            return i;
        }
    }
    return -1;
}
int find_call_info(char call_info[10][30], char *fun_name)
{
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        if (strcmp(call_info[i], fun_name) == 0)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    int op = 0;
    char fun_name[30] = {0};
    fun name_stack[150] = {0};
    fun print[150] = {0};
    int flag = 0;
    int top = -1;
    while (flag == 0)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            top--;
            if (top == -1)
            {
                flag = 1;
            }
            break;
        case 8:
            scanf("%s", fun_name);
            if (top == -1)
            {
                top++;
                strcpy(name_stack[top].name, fun_name);
                strcpy(print[fun_num].name, fun_name);
                fun_num++;
            }
            else
            {
                if (find_fun_name(print, fun_name) == -1)
                {
                    strcpy(print[fun_num].name, fun_name);
                    fun_num++;
                }
                int i = find_fun_name(print, name_stack[top].name);
                if (find_call_info(print[i].call_info, fun_name) == -1)
                {
                    strcpy(print[i].call_info[print[i].call_num], fun_name);
                    print[i].call_num++;
                }
                top++;
                strcpy(name_stack[top].name, fun_name);
            }
            break;
        default:
            break;
        }
    }
    int i = 0;
    int j = 0;
    for (i = 0; i < fun_num; i++)
    {
        if (print[i].call_num > 0)
        {
            printf("%s:", print[i].name);
            for (j = 0; j < print[i].call_num; j++)
            {
                if (j == print[i].call_num - 1)
                {
                    printf("%s\n", print[i].call_info[j]);
                }
                else
                {
                    printf("%s,", print[i].call_info[j]);
                }
            }
        }
    }
    return 0;
}