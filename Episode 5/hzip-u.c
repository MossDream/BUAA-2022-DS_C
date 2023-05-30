// 本程序仅实现解压缩功能
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 12000

typedef struct Tree
{
    char c;
    struct Tree *left, *right;
} Tree;
Tree *Root = NULL;
char s[10005], HCode[128][50], r[MAXSIZE], code[MAXSIZE];
int sum, maxlen = 0, minlen, k = 0, l = 0, m = 0;
FILE *Src, *Obj;

void readHZIP();            // 读取文件中Huffman编码信息
void Hcode(int n);          // 生成Huffman编码
void unhzip();              // 生成解压文件
void createHTree();         // 建立Huffman树
void visit(Tree *p, int i); // 遍历Huffman树，找到ASCII码

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
    // 文件处理
    char input[50] = {0};
    char output[50] = {0};
    strcpy(input, argv[2]);
    strcpy(output, argv[2]);
    output[strlen(argv[2]) - 4] = 't';
    output[strlen(argv[2]) - 3] = 'x';
    output[strlen(argv[2]) - 2] = 't';
    output[strlen(argv[2]) - 1] = '\0';
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

    readHZIP();    // 读取文件中字符
    createHTree(); // 建立Huffman树
    unhzip();      // 生成解压文件

    fclose(Src);
    fclose(Obj);

    return 0;
}

void readHZIP()
{
    int i = 0, j, times, u, v;
    unsigned char d, ac;
    // 读取字符数
    d = fgetc(Src);
    sum = d;
    for (i = 0; i < sum; i++)
    {
        // 读取ACSII字符
        d = fgetc(Src);
        ac = d;
        // 读取Huffman编码长度
        d = fgetc(Src);
        // 确保长度大于8的编码正确读入
        times = d;
        u = times % 8;
        v = times / 8;
        if (u > 0)
            v++;
        for (j = 0; j < v; j++)
        {
            d = fgetc(Src);
            Hcode(d);
        }
        code[times] = '\0';
        // 构建HCode表信息
        strcpy(HCode[ac], code);
        memset(code, 0, sizeof(char));
    }
}

void createHTree()
{
    int i, j;
    Tree *p, *q;
    Root = (Tree *)malloc(sizeof(Tree));
    Root->left = NULL;
    Root->right = NULL;
    for (i = 0; i < 128; i++)
    {
        p = Root;
        if (HCode[i][0] != '\0')
        {
            for (j = 0; j < strlen(HCode[i]); j++)
            {
                if (HCode[i][j] == '0' && p->left == NULL)
                {
                    q = (Tree *)malloc(sizeof(Tree));
                    q->left = NULL;
                    q->right = NULL;
                    p->left = q;
                    p = p->left;
                }
                else if (HCode[i][j] == '0' && p->left != NULL)
                {
                    p = p->left;
                }
                else if (HCode[i][j] == '1' && p->right == NULL)
                {
                    q = (Tree *)malloc(sizeof(Tree));
                    q->left = NULL;
                    q->right = NULL;
                    p->right = q;
                    p = p->right;
                }
                else
                {
                    p = p->right;
                }
            }
            p->c = i;
        }
    }
}

void unhzip()
{
    // 为提高效率，每到1000个字符解压一次
    unsigned char d;
    char e;
    int i, len;
    while (!feof(Src))
    {
        e = fgetc(Src);
        d = e;
        Hcode(d);
        if (strlen(code) >= 1000)
        {
            while (l != -1)
            {
                m = k;
                visit(Root, k);
            }
            if (k >= strlen(code))
                memset(code, 0, sizeof(char));
            else
            {
                len = strlen(code);
                for (i = k; i < len; i++)
                {
                    code[i - k] = code[i];
                }
                code[len - k] = '\0';
            }
            k = l = m = 0;
        }
    }
    while (l != -1)
    {
        m = k;
        visit(Root, k);
    }
    k = l = m = 0;
}

void visit(Tree *p, int i)
{
    if (i >= strlen(code))
    {
        l = -1;
        return;
    }
    if (p->left == NULL && p->right == NULL)
    {
        fputc(p->c, Obj);
        putchar(p->c);
        k = i;
        return;
    }
    if (code[i] == '0')
        visit(p->left, i + 1);
    else
        visit(p->right, i + 1);
    return;
}

void Hcode(int n)
{
    char ss[MAXSIZE] = {}, t;
    int i = 0, j;
    while (i < 8)
    {
        ss[i++] = n % 2 + '0';
        n /= 2;
    }
    for (i = 0, j = strlen(ss) - 1; i <= j; i++, j--)
    {
        t = ss[i];
        ss[i] = ss[j];
        ss[j] = t;
    }
    strcat(code, ss);
}
