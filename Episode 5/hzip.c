// 本程序只实现压缩功能
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 32

struct tnode
{ // Huffman树结构
    char c;
    int weight; // 树节点权重，叶节点为字符和它的出现次数
    struct tnode *left, *right;
};
int Ccount[128] = {0};            // 存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数
struct tnode *Root = NULL;        // Huffman树的根节点
char HCode[128][MAXSIZE] = {{0}}; // 字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）
char bin[8] = {0};                // 用于存放二进制编码
FILE *Src, *Obj;

void statCount();   // 步骤1：统计文件中字符频率
void createHTree(); // 步骤2：创建一个Huffman树，根节点为Root
void makeHCode();   // 步骤3：根据Huffman树生成Huffman编码
void atoHZIP();     // 步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

int main(int argc, char **argv)
{
    // 排查命令行参数输入的错误
    if (argc != 2 && argc != 3)
    {
        printf("Usage: hzip.exe [-u] <filename>");
        return 1;
    }
    if (argc == 2 && strstr(argv[1], ".txt") == NULL)
    {
        printf("File extension error!");
        return 1;
    }
    if (argc == 3 && strstr(argv[1], "u") == NULL)
    {
        printf("Usage: hzip.exe [-u] <filename>");
        return 1;
    }
    if (argc == 3 && strstr(argv[2], ".hzip") == NULL)
    {
        printf("File extension error!");
        return 1;
    }

    char input[50] = {0};
    char output[50] = {0};
    strcpy(input, argv[1]);
    strcpy(output, argv[1]);
    output[strlen(argv[1]) - 3] = 'h';
    output[strlen(argv[1]) - 2] = 'z';
    output[strlen(argv[1]) - 1] = 'i';
    output[strlen(argv[1])] = 'p';
    if ((Src = fopen(input, "r")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", input);
        return 1;
    }
    if ((Obj = fopen(output, "w")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", output);
        return 1;
    }

    statCount();   // 步骤1：统计文件中字符频率
    createHTree(); // 步骤2：创建一个Huffman树，根节点为Root
    makeHCode();   // 步骤3：根据Huffman树生成Huffman编码
    atoHZIP();     // 步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

    fclose(Src);
    fclose(Obj);
}
// 【实验步骤1】开始

void statCount()
{
    Ccount[0] = 1;
    while (1)
    {
        char c = fgetc(Src);
        if (c == EOF)
            break;
        if (c != '\n')
        {
            Ccount[c]++;
        }
    }
}

// 【实验步骤1】结束

// 【实验步骤2】开始
void bubble_sort(struct tnode **Forest, int m)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m - i - 1; j++)
        {
            if (Forest[j]->weight > Forest[j + 1]->weight)
            {
                struct tnode *temp = Forest[j];
                Forest[j] = Forest[j + 1];
                Forest[j + 1] = temp;
            }
            else if (Forest[j]->weight == Forest[j + 1]->weight)
            {
                if (Forest[j]->c > Forest[j + 1]->c)
                {
                    struct tnode *temp = Forest[j];
                    Forest[j] = Forest[j + 1];
                    Forest[j + 1] = temp;
                }
            }
        }
    }
}
void createHTree()
{
    struct tnode *Forest[500];
    int m = 0;
    int i = 0;
    for (i = 0; i < 128; i++)
    {
        if (Ccount[i] > 0)
        {
            Forest[m] = (struct tnode *)malloc(sizeof(struct tnode));
            Forest[m]->c = i;
            Forest[m]->weight = Ccount[i];
            Forest[m]->left = NULL;
            Forest[m]->right = NULL;
            m++;
        }
    }
    bubble_sort(Forest, m);
    while (m > 1)
    {
        struct tnode *temp = (struct tnode *)malloc(sizeof(struct tnode));
        temp->c = -1;
        temp->weight = Forest[0]->weight + Forest[1]->weight;
        temp->left = Forest[0];
        temp->right = Forest[1];
        for (i = 0; i < m - 2; i++)
        {
            Forest[i] = Forest[i + 2];
        }
        m -= 2;
        for (i = m - 1; i >= 0; i--)
        {
            if (Forest[i]->weight <= temp->weight)
            {
                break;
            }
        }
        int j = 0;
        for (j = m + 1; j >= i + 1; j--)
        {
            Forest[j + 1] = Forest[j];
        }
        Forest[i + 1] = temp;
        m++;
    }
    Root = Forest[0];
}

// 【实验步骤2】结束

// 【实验步骤3】开始
void preorder(struct tnode *p, char *code, int len)
{
    if (p != NULL)
    {
        if (p->left == NULL && p->right == NULL)
        {
            code[len] = '\0';
            strcpy(HCode[p->c], code);
        }
        else
        {
            code[len] = '0';
            preorder(p->left, code, len + 1);
            code[len] = '1';
            preorder(p->right, code, len + 1);
        }
    }
}
void makeHCode()
{
    char code[128] = {0};
    preorder(Root, code, 0);
}

// 【实验步骤3】结束

// 【实验步骤4】开始
void makeBin(int num)
{
    int i = 7;
    while (num > 0)
    {
        bin[i] = num % 2 + '0';
        num /= 2;
        i--;
    }
    int j = 0;
    for (j = 0; j <= i; j++)
    {
        bin[j] = '0';
    }
}
void atoHZIP()
{
    int i = 0;
    int cnt = 0;
    char str[5000] = {0};
    char c = 0;
    unsigned char hc = 0;
    int len = strlen(str);
    fseek(Src, 0, SEEK_SET);

    // 压缩文件第一部分处理
    //  第一个字节
    for (i = 0; i < 128; i++)
    {
        if (Ccount[i] > 0)
        {
            cnt++;
        }
    }
    makeBin(cnt);
    strcat(str, bin);
    // 每个字符的编码信息
    for (i = 0; i < 128; i++)
    {
        if (Ccount[i] > 0)
        {
            // ACSII码
            makeBin(i);
            strcat(str, bin);
            // Huaffman编码长度
            makeBin(strlen(HCode[i]));
            strcat(str, bin);
            // Huaffman编码，用0补全至8位
            strcat(str, HCode[i]);
            while (strlen(str) % 8 != 0)
            {
                strcat(str, "0");
            }
        }
    }
    // 输出并清空str
    len = strlen(str);
    for (i = 0; i < len; i++)
    {
        hc = (hc << 1) | (str[i] - '0');
        if ((i + 1) % 8 == 0)
        {
            fputc(hc, Obj);
            hc = 0;
        }
    }
    memset(str, 0, sizeof(char));

    // 压缩文件第二部分处理,每8位打印一次并清空str
    while ((c = fgetc(Src)) != EOF)
    {
        strcat(str, HCode[c]);
        if (strlen(str) % 8 == 0)
        {
            len = strlen(str);
            for (i = 0; i < len; i++)
            {
                hc = (hc << 1) | (str[i] - '0');
                if ((i + 1) % 8 == 0)
                {
                    fputc(hc, Obj);
                    hc = 0;
                }
            }
            memset(str, 0, sizeof(char));
        }
    }
    strcat(str, HCode[0]);
    while (strlen(str) % 8 != 0)
    {
        strcat(str, "0");
    }
    len = strlen(str);
    hc = 0;
    for (i = 0; i < len; i++)
    {
        hc = (hc << 1) | (str[i] - '0');
        if ((i + 1) % 8 == 0)
        {
            fputc(hc, Obj);
            hc = 0;
        }
    }
}
// 【实验步骤4】结束
