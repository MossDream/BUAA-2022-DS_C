#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h> 
typedef struct block {
    int pos;
    int size;
}block;
int find_min(int a[], int len) {
    int i, min = a[0], pos = 0;
    for (i = 1; i < len; i++) {
        if (a[i] < min)
            min = a[i];
	}
    for (i = 0; i < len; i++) {
        if (a[i] == min) {
            pos = i;
            break;
        }
    }
    return pos;
}
int main(){
    clock_t start, end; 
    double cpu_time_used; 
    start = clock(); 
    int n;
    scanf("%d", &n);
    block arr[120] = { 0 };
    int sub[120] = { 0 };
    int rec[120] = { 0 };
    int i, j = 0, k = 0;
    for (i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].pos, &arr[i].size);
    }
    int loc = 0, op = 0, flag1 = 0, flag2 = 0;
    int m = 0;
    while (scanf("%d", &op) != EOF) {
        if (op == -1) {
            break;
        }
        int loccpy = loc;
        int icpy = 0;
        for (i = loc; i < loccpy + n ; i++) {
            icpy = i;
            if (i > n - 1) {
                i %= n;
            }
            if (arr[i].size == op) {
                loc = i + 1;
                arr[i].size = 0;
                flag1 = 1;
                break;
            }
            else if (arr[i].size > op) {
                sub[j++] = arr[i].size - op;
                rec[k++] = i;
                flag2 = 1;
            }
            i = icpy;
        }
        if (flag2&&flag1==0) {
            int tmp = find_min(sub, j);
            arr[rec[tmp]].size -= op;
            loc = rec[tmp];
        }
        flag1 = 0;
        flag2 = 0;
        k = 0;
        for (j = 0; j < n; j++) {
            sub[j] = 0;
            rec[j] = 0;
        }
        j = 0;
    }
    int icpy = 0;
    for (i = loc; i < loc + n; i++) {
        icpy = i;
        if (i > n - 1) {
            i %= n;
        }
        if (arr[i].size != 0) {
            printf("%d %d\n", arr[i].pos, arr[i].size);
        }
        i = icpy;
    }
    end = clock(); 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
    //printf("The code took % f seconds to execute.\n", cpu_time_used);
      return 0;
}