#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct edit_unit
{
    int op;
    int pos;
    int del_num_flag;
    char str[100];
} edit_unit;
void insert(char *text, int pos, char *str)
{
    int len = strlen(text);
    int len2 = strlen(str);
    int i = 0;
    for (i = len; i >= pos; i--)
    {
        text[i + len2] = text[i];
    }
    for (i = 0; i < len2; i++)
    {
        text[pos + i] = str[i];
    }
}
void del(char *text, int pos, int n)
{
    int len = strlen(text);
    int i = 0;
    for (i = pos; i < len - n; i++)
    {
        text[i] = text[i + n];
    }
    text[i] = 0;
}
void recover(char *text, edit_unit *info, int n)
{
    int i = 0;
    for (i = n - 1; i >= 0; i--)
    {
        if (info[i].op == 1)
        {
            int len = strlen(info[i].str);
            del(text, info[i].pos, len);
        }
        else if (info[i].op == 2)
        {
            insert(text, info[i].pos, info[i].str);
        }
    }
}
void print(char *text, edit_unit *info, int n)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < n; i++)
    {
        if (info[i].op == 1)
        {
            insert(text, info[i].pos, info[i].str);
        }
        else if (info[i].op == 2)
        {
            int len = strlen(info[i].str);
            if (info[i].del_num_flag == 1)
            {

                int numtmp = 0;
                for (j = 0; j < len; j++)
                {
                    numtmp = numtmp * 10 + (info[i].str[j] - '0');
                }
                del(text, info[i].pos, numtmp);
            }
            else
            {
                del(text, info[i].pos, strlen(info[i].str));
            }
        }
    }
    printf("%s", text);
}
int main()
{
    char text[600] = {0};
    gets(text);

    int n = 0;
    scanf("%d", &n);
    int num = n;
    int i = 0;
    edit_unit info[500] = {0};
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %s", &info[i].op, &info[i].pos, info[i].str);
    }
    recover(text, info, n);

    edit_unit tmp = {0};
    while (scanf("%d", &tmp.op) != -1)
    {
        if (tmp.op == 1)
        {
            scanf("%d %s", &tmp.pos, tmp.str);
            info[num].op = tmp.op;
            info[num].pos = tmp.pos;
            strcpy(info[num].str, tmp.str);
            num++;
        }
        else if (tmp.op == 2)
        {
            scanf("%d %s", &tmp.pos, tmp.str);
            info[num].op = tmp.op;
            info[num].pos = tmp.pos;
            strcpy(info[num].str, tmp.str);
            info[num].del_num_flag = 1;
            num++;
        }
        else if (tmp.op == 3)
        {
            if (num > 0)
            {
                info[num - 1].op = 0;
                info[num - 1].pos = 0;
                info[num - 1].str[0] = 0;
                num--;
            }
        }
        else if (tmp.op == -1)
        {
            break;
        }
    }
    print(text, info, num);
    return 0;
}