#include <stdio.h>
int main()
{
    int num = 0;
    int stack[100] = {0};
    int op;
    while (scanf("%d", &op))
    {
        if (op == 1)
        {
            if (num == 100)
            {
                printf("error ");
            }
            else
            {
                scanf("%d", &stack[num]);
                num++;
            }
        }
        else if (op == 0)
        {
            if (num == 0)
            {
                printf("error ");
            }
            else
            {
                num--;
                printf("%d ", stack[num]);
            }
        }
        else if (op == -1)
        {
            break;
        }
    }
    return 0;
}