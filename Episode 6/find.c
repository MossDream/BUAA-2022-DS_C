#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NHASH 3001
#define MULT 37
unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}
typedef struct node
{
    char *word;
    struct node *next;
} Node;
char dic[3500][20] = {0};
int main()
{
    int num = 0;
    FILE *fp = fopen("dictionary3000.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%s", dic[num]);
        num++;
    }
    num--;
    char word[20] = {0};
    int op = 0;
    int res = 0;
    int times = 0;
    scanf("%s %d", word, &op);
    switch (op)
    {
    case 1: // 顺序查找
    {
        for (int i = 0; i < num; i++)
        {
            times++;
            if (strcmp(word, dic[i]) == 0)
            {
                res = 1;
                break;
            }
            else if (strcmp(word, dic[i]) < 0)
            {
                break;
            }
        }
        break;
    }
    case 2: // 二分查找
    {
        int left = 0;
        int right = num - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            times++;
            if (strcmp(word, dic[mid]) == 0)
            {
                res = 1;
                break;
            }
            else if (strcmp(word, dic[mid]) < 0)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        break;
    }
    case 3: // 通过索引表来获取单词查找范围，并在该查找范围中以折半方式查找
        // 索引表构建方式为：以26个英文字母为头字母的单词在字典中的起始位置和单词个数来构建索引表
        // 例如：索引表第一项为：a 0 100，表示字典中以a开头的单词在字典中的起始位置为0，单词个数为100
        // 构建索引表
        {
            int index[26][2] = {0};
            int index_num = 0;
            for (int i = 0; i < num; i++)
            {
                if (dic[i][0] == 'a' + index_num)
                {
                    index[index_num][1]++;
                }
                else
                {
                    index_num++;
                    while (dic[i][0] != 'a' + index_num)
                    {
                        index_num++;
                    }
                    index[index_num][0] = i;
                    index[index_num][1]++;
                }
            }
            // 查找
            int index_pos = word[0] - 'a';
            int left2 = index[index_pos][0];
            int right2 = index[index_pos][0] + index[index_pos][1] - 1;
            while (left2 <= right2)
            {
                int mid = (left2 + right2) / 2;
                times++;
                if (strcmp(word, dic[mid]) == 0)
                {
                    res = 1;
                    break;
                }
                else if (strcmp(word, dic[mid]) < 0)
                {
                    right2 = mid - 1;
                }
                else
                {
                    left2 = mid + 1;
                }
            }
            break;
        }
    case 4: // 按下面给定的hash函数为字典中单词构造一个hash表，hash冲突时按字典序依次存放单词
            // hash查找遇到冲突时，采用链地址法处理
            // 在冲突链表中找到或未找到(遇到第一个比待查找的单词大的单词或链表结束)便结束查找。
    {
        Node hash_table[NHASH] = {0};
        for (int i = 0; i < num; i++)
        {
            unsigned int h = hash(dic[i]);
            Node *p = &hash_table[h];
            while (p->next != NULL)
            {
                p = p->next;
            }
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->word = dic[i];
            new_node->next = NULL;
            p->next = new_node;
        }
        unsigned int h = hash(word);
        Node *p = &hash_table[h];
        while (p->next != NULL)
        {
            times++;
            if (strcmp(word, p->next->word) == 0)
            {
                res = 1;
                break;
            }
            else if (strcmp(word, p->next->word) < 0)
            {
                break;
            }
            p = p->next;
        }
        break;
    }
    default:
        break;
    }
    printf("%d %d\n", res, times);
    fclose(fp);
    fp = NULL;
    return 0;
}