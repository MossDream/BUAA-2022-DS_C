#define  _CRT_SECURE_NO_WARNINGS 1
//这是生成1-n共n个自然数按照字典序排列的所有全排列的算法
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h> 
int a[50];
int compare(const void* a, const void* b) {
    return (*((int*)a) - *((int*)b));
}
int BinarySearch(int a[], int num1, int n)
{
    int left = num1 + 1;
    int right = n;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] <= a[num1]) {
            right = mid - 1;
        }
        else {
            if (mid == n || a[mid + 1] <= a[num1]) {
                return mid;
            }
            else {
                left = mid + 1;
            }
        }
    }
    return -1; //没找到，返回-1
}
void order(int n) {//n是自然数的个数
    int i, num1 = 0, num2 = 0, flag = 1;
    while (flag) {
        for (i = n; i >= 2; i--) {
            if (a[i - 1] < a[i]) {
                //1.从右端点向左找到第一个破坏升序(从右往左看)的数
                num1 = i - 1;//记录位置
                flag = 1;//循环结束的标志数
                break;
            }
            else {
                flag = 0;
            }
        }
        //2.从右端点向左找到第一个大于a[num1]的数,用二分查找,并记录
        num2 = BinarySearch(a, num1, n);
        int temp;
         temp = a[num2]; a[num2] = a[num1]; a[num1] = temp;//3.交换a[num1]和a[num2]
        //4.将a[num1]之后的数升序排列,用快速排序 
         qsort(a + num1 + 1, n - num1, sizeof(int), compare);
        //继续快速打印
        if (flag) {
            for (i = 1; i <= n; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");
        }
    }
}
int main() {
 //clock_t start, end; 
 //double cpu_time_used; 
 //start = clock();  
    
    int n;
    scanf("%d", &n);
    int i;
    if (n == 1) {
        printf("1\n");
    }
    else {
        for (i = 1; i <= n; i++) {
            a[i] = i;
            //第一次初始快速打印
            printf("%d ", a[i]);
        }
        //第一次初始快速打印
        printf("\n");
        order(n);
    }
    /*end = clock(); 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
    printf("The code took % f seconds to execute.\n", cpu_time_used);*/
    return 0;
}
