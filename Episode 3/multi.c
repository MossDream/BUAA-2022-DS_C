#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>
long a_base[200], b_base[200];
int a_exp[200], b_exp[200];
typedef struct res {
    int exp;
    int base;
}res;
res put[5000] = { -1 };
int compare(const void* a, const void* b) {
    return ((*(res*)b).exp - (*(res*)a).exp);
}
int main(){
    clock_t start, end; 
    double cpu_time_used; 
    start = clock(); 
    int cnta = 0, cntb = 0;
    char c = 0;
    while ( c != '\n') {
        scanf("%d%d%c", &a_base[cnta], &a_exp[cnta], &c);
        cnta++;
    }
    c = 0;
    while ( c != '\n') {
        scanf("%d%d%c", &b_base[cntb], &b_exp[cntb], &c);
        cntb++;
    }
    int i = 0, j = 0, num1 = 0, num2 = 0;
    for (i = 0; i < cnta; i++) {
        for (j = 0; j < cntb; j++) {
            put[num1++].exp = a_exp[i] + b_exp[j];
            put[num2++].base = a_base[i] * b_base[j];
        }
    }
    qsort(put, num1, sizeof(res), compare);
    for (i = 0; i < num1; i++) {
        if (i < num1 - 1) {
            if (put[i].exp == put[i + 1].exp) {
                put[i + 1].base += put[i].base;
            }
            else {
                printf("%d %d ", put[i].base, put[i].exp);
            }
        }
        else {
            printf("%d %d", put[i].base, put[i].exp);
        }
    }
    end = clock(); 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
    //printf("The code took % f seconds to execute.\n", cpu_time_used);
      return 0;
}