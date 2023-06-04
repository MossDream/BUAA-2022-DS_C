#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct Info
{
    char id[20];
    char name[20];
    int seatnum;
} Info;
int cmp1(const void *a, const void *b)
{
    Info *c = (Info *)a;
    Info *d = (Info *)b;
    if (c->seatnum != d->seatnum)
        return c->seatnum - d->seatnum;
    else
        return strcmp(c->id, d->id);
}
int cmp2(const void *a, const void *b)
{
    Info *c = (Info *)a;
    Info *d = (Info *)b;
    return strcmp(c->id, d->id);
}
int main()
{
    Info table[100] = {0};
    int N; // N为学生人数
    scanf("%d", &N);
    int pos = N - 1; // 定位到未处理的最后一个学生
    FILE *fp = fopen("in.txt", "r");
    FILE *fw = fopen("out.txt", "w");
    if (fp == NULL || fw == NULL)
    {
        printf("error\n");
        return 1;
    }
    int i = 0;
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%s %s %d", table[i].id, table[i].name, &table[i].seatnum);
    }
    qsort(table, N, sizeof(Info), cmp1);
    int M = table[N - 1].seatnum; // M为最大座位号
    int Q = N;
    if (M <= N)
    {
        Q = M;
    }
    // 检查漏排情况,必须采用这种处理方法，不要统一把所有漏排座号全部赋值
    if (table[0].seatnum > 1)
    {
        table[N - 1].seatnum = 1;
        pos--;
    }
    for (i = 1; i <= Q; i++)
    {
        if (table[i].seatnum - table[i - 1].seatnum > 1)
        {
            table[pos].seatnum = table[i - 1].seatnum + 1;
            pos--;
        }
    }
    // 当前表中最大座位号，注意：已经漏排处理过的不计入
    int m = table[pos].seatnum;
    // 检查重排情况,保证重复的不超过2个
    for (i = 0; i < N; i++)
    {
        if (table[i + 1].seatnum == table[i].seatnum)
        {
            m++;
            table[i + 1].seatnum = m;
        }
    }
    qsort(table, N, sizeof(Info), cmp2);
    for (i = 0; i < N; i++)
    {
        fprintf(fw, "%s %s %d\n", table[i].id, table[i].name, table[i].seatnum);
    }
    fclose(fp);
    fclose(fw);
    fp = NULL;
    fw = NULL;
    return 0;
}