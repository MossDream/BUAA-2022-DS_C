#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 从标准输入中输入一组互不相同的整数（个数不超过100）及排序方式，按照从小到大排序，输出按某种算法排序的结果及元素的比较次数
// 同时通过此题准备好基本的排序算法，以便后面的题目使用
// 本题所有的所有排序算法统一接受两个参数，第一个参数是待排序的数组，第二个参数是数组的元素个数
// 本题所有的排序算法都是从小到大排序
// 本题的五种排序：1. 选择排序 2. 冒泡排序 3. 堆排序 4. 二路归并排序 5. 快速排序
int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0;
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
// 选择排序
// 选择排序的思想是：每次从待排序的数组中选择最小的元素，放到已排序数组的末尾
// 比较次数是指选择未排序部分的最小元素时的比较次数
void select_sort(int *arr, int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < num; j++)
        {
            cnt1++;
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        swap(&arr[i], &arr[min]);
    }
    return;
}
// 冒泡排序
// 若某趟排序中没有进行数据交换，就认为排序结束
// 比较次数是指相邻元素的比较次数
void bubble_sort(int *arr, int num)
{
    int flag = 1;
    for (int i = 0; i < num - 1 && flag; i++)
    {
        flag = 0;
        for (int j = 0; j < num - 1 - i; j++)
        {
            cnt2++;
            if (arr[j] > arr[j + 1])
            {
                flag = 1;
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return;
}
// 堆排序
// 比较次数是指根元素调整过程中根元素与子树根结点的比较次数,即if (temp >= k[j]){break;}的执行次数
void adjust(int k[], int i, int n)
{
    int j, temp;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n)
    {
        if (j < n - 1 && k[j] < k[j + 1])
            j++;
        cnt3++;
        if (temp >= k[j])
        {
            break;
        }
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }

    k[(j - 1) / 2] = temp;
}
void heap_sort(int *arr, int num)
{
    int i;
    for (i = num / 2 - 1; i >= 0; i--)
    {
        adjust(arr, i, num);
    }
    for (i = num - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        adjust(arr, 0, i);
    }
    return;
}
// 二路归并排序
// 比较次数是指两个有序数组合并成一个有序数组的比较次数
void merge(int x[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend)
    {

        cnt4++;
        if (x[i] <= x[j])
        {
            tmp[q++] = x[i++];
                }
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
}
void msort(int x[], int tmp[], int left, int right)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;
        msort(x, tmp, left, center);
        msort(x, tmp, center + 1, right);
        merge(x, tmp, left, center, right);
    }
}
void merge_sort(int *arr, int num) // 要求必须用递归算法
{
    int *tmp = (int *)malloc(sizeof(int) * num);
    msort(arr, tmp, 0, num - 1);
    free(tmp);
    return;
}
// 快速排序
// 比较次数是指分界元素与其它元素的比较次数
void quick(int k[], int left, int right)
{
    int i, last;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            cnt5++;
            if (k[i] < k[left])
                swap(&k[++last], &k[i]);
        }
        swap(&k[left], &k[last]);
        quick(k, left, last - 1);
        quick(k, last + 1, right);
    }
}
void quick_sort(int *arr, int num)
{
    quick(arr, 0, num - 1);
    return;
}
int main()
{
    int num = 0;
    int op = 0;
    int arr[100] = {0};
    scanf("%d %d", &num, &op);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &arr[i]);
    }
    switch (op)
    {
    case 1:
        select_sort(arr, num);
        for (int i = 0; i < num; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("%d\n", cnt1);
        break;
    case 2:
        bubble_sort(arr, num);
        for (int i = 0; i < num; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("%d\n", cnt2);
        break;
    case 3:
        heap_sort(arr, num);
        for (int i = 0; i < num; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("%d\n", cnt3);
        break;
    case 4:
        merge_sort(arr, num);
        for (int i = 0; i < num; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("%d\n", cnt4);
        break;
    case 5:
        quick_sort(arr, num);
        for (int i = 0; i < num; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("%d\n", cnt5);
        break;
    default:
        break;
    }
    return 0;
}