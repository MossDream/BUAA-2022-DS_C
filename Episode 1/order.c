#define  _CRT_SECURE_NO_WARNINGS 1
//��������1-n��n����Ȼ�������ֵ������е�����ȫ���е��㷨
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
    return -1; //û�ҵ�������-1
}
void order(int n) {//n����Ȼ���ĸ���
    int i, num1 = 0, num2 = 0, flag = 1;
    while (flag) {
        for (i = n; i >= 2; i--) {
            if (a[i - 1] < a[i]) {
                //1.���Ҷ˵������ҵ���һ���ƻ�����(��������)����
                num1 = i - 1;//��¼λ��
                flag = 1;//ѭ�������ı�־��
                break;
            }
            else {
                flag = 0;
            }
        }
        //2.���Ҷ˵������ҵ���һ������a[num1]����,�ö��ֲ���,����¼
        num2 = BinarySearch(a, num1, n);
        int temp;
         temp = a[num2]; a[num2] = a[num1]; a[num1] = temp;//3.����a[num1]��a[num2]
        //4.��a[num1]֮�������������,�ÿ������� 
         qsort(a + num1 + 1, n - num1, sizeof(int), compare);
        //�������ٴ�ӡ
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
            //��һ�γ�ʼ���ٴ�ӡ
            printf("%d ", a[i]);
        }
        //��һ�γ�ʼ���ٴ�ӡ
        printf("\n");
        order(n);
    }
    /*end = clock(); 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
    printf("The code took % f seconds to execute.\n", cpu_time_used);*/
    return 0;
}
