#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>
typedef struct info
{
    char word[50];
    int cnt;
} info;
int binary_search(info *a, int low, int high, char *str)
{
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(str, a[mid].word) == 0)
            return mid;
        else if (strcmp(str, a[mid].word) < 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}
int cmp(const void *a, const void *b)
{
    info *c = (info *)a;
    info *d = (info *)b;
    return strcmp(c->word, d->word);
}
int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    FILE *fpr = fopen("article.txt", "r");
    if (fpr == NULL)
    {
        perror("In open article.txt:");
    }
    info a[250] = {0};
    char tmp[50] = {0};
    int c = 0;
    int i = 0, j = 0, cnt = 0;
    while ((c = fgetc(fpr)) != EOF)
    {
        if (isalpha(c))
        {
            c = tolower(c);
            tmp[cnt++] = c;
            while (isalpha(c = fgetc(fpr)))
            {
                c = tolower(c);
                tmp[cnt++] = c;
            }
            if (binary_search(a, 0, i - 1, tmp) == -1)
            {
                strcpy(a[i].word, tmp);
                a[i++].cnt++;
                qsort(a, i, sizeof(info), cmp);
            }
            else
            {
                int pos = binary_search(a, 0, i - 1, tmp);
                a[pos].cnt++;
            }
            for (j = 0; j < cnt; j++)
            {
                tmp[j] = 0;
            }
            cnt = 0;
        }
    }
    for (j = 0; j < i - 1; j++)
    {
        printf("%s %d\n", a[j].word, a[j].cnt);
    }
    printf("%s %d", a[j].word, a[j].cnt);
    fclose(fpr);
    fpr = NULL;
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("The code took % f seconds to execute.\n", cpu_time_used);
    return 0;
}