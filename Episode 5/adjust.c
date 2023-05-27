#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *medium;
    struct TreeNode *right;
} Tree;
typedef struct Gate
{
    int num;
    int flow;
} Gate;
int compare(const void *a, const void *b)
{
    Gate *c = (Gate *)a;
    Gate *d = (Gate *)b;
    if (c->flow == d->flow)
    {
        return (c->num - d->num);
    }
    return (d->flow - c->flow);
}
int find(Tree *node, int num, int val)
{
    int i = 0;
    for (i = 0; i < num; i++)
    {
        if (node[i].val == val)
        {
            return i;
        }
    }
    return -1;
}
void BFS_and_print(Tree *node, Tree *queue, Gate *gate, int gatenum)
{
    queue[0].val = node[0].val;
    queue[0].left = node[0].left;
    queue[0].medium = node[0].medium;
    queue[0].right = node[0].right;
    Tree *front = &queue[0];
    Tree *rear = &queue[1];
    int cnt = 0;
    while (cnt < gatenum)
    {
        if (front->val < 100)
        {
            printf("%d->%d\n", gate[cnt++].num, front->val);
        }
        if (front->left != NULL)
        {
            (*rear).val = (*(front->left)).val;
            (*rear).left = (*(front->left)).left;
            (*rear).medium = (*(front->left)).medium;
            (*rear).right = (*(front->left)).right;
            rear++;
        }
        if (front->medium != NULL)
        {
            (*rear).val = (*(front->medium)).val;
            (*rear).left = (*(front->medium)).left;
            (*rear).medium = (*(front->medium)).medium;
            (*rear).right = (*(front->medium)).right;
            rear++;
        }
        if (front->right != NULL)
        {
            (*rear).val = (*(front->right)).val;
            (*rear).left = (*(front->right)).left;
            (*rear).medium = (*(front->right)).medium;
            (*rear).right = (*(front->right)).right;
            rear++;
        }
        front++;
    }
}
int main()
{
    int cnt = 0;
    int i = 0;
    int tmp = 0;
    int nodenum = 0;
    int gatenum = 0;
    int arr[5] = {0};
    Tree node[100] = {0};
    Tree queue[100] = {0};
    while (tmp != -1)
    {
        scanf("%d", &tmp);
        if (tmp != -1)
        {
            arr[cnt++] = tmp;
        }
        else
        {
            break;
        }
        while (tmp != -1)
        {
            scanf("%d", &tmp);
            if (tmp != -1)
            {
                arr[cnt++] = tmp;
            }
        }
        switch (cnt)
        {
        case 1:
            node[nodenum].val = arr[0];
            if (node[nodenum].val < 100)
            {
                gatenum++;
            }
            node[nodenum].left = NULL;
            node[nodenum].medium = NULL;
            node[nodenum].right = NULL;
            nodenum++;
            break;
        case 2:
            if (find(node, nodenum, arr[0]) == -1)
            {
                node[nodenum].val = arr[0];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                nodenum++;
                node[nodenum].val = arr[1];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[nodenum - 1].left = &node[nodenum];
                nodenum++;
            }
            else
            {
                int pos = find(node, nodenum, arr[0]);
                node[nodenum].val = arr[1];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[pos].left = &node[nodenum];
                nodenum++;
            }
            break;
        case 3:
            if (find(node, nodenum, arr[0]) == -1)
            {
                node[nodenum].val = arr[0];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                nodenum++;
                node[nodenum].val = arr[1];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[nodenum - 1].left = &node[nodenum];
                nodenum++;
                node[nodenum].val = arr[2];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[nodenum - 2].medium = &node[nodenum];
                nodenum++;
            }
            else
            {
                int pos = find(node, nodenum, arr[0]);
                node[nodenum].val = arr[1];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[pos].left = &node[nodenum];
                nodenum++;
                node[nodenum].val = arr[2];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[pos].medium = &node[nodenum];
                nodenum++;
            }
            break;
        case 4:
            if (find(node, nodenum, arr[0]) == -1)
            {
                node[nodenum].val = arr[0];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                nodenum++;
                node[nodenum].val = arr[1];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[nodenum - 1].left = &node[nodenum];
                nodenum++;
                node[nodenum].val = arr[2];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[nodenum - 2].medium = &node[nodenum];
                nodenum++;
                node[nodenum].val = arr[3];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[nodenum - 3].right = &node[nodenum];
                nodenum++;
            }
            else
            {
                int pos = find(node, nodenum, arr[0]);
                node[nodenum].val = arr[1];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[pos].left = &node[nodenum];
                nodenum++;
                node[nodenum].val = arr[2];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[pos].medium = &node[nodenum];
                nodenum++;
                node[nodenum].val = arr[3];
                if (node[nodenum].val < 100)
                {
                    gatenum++;
                }
                node[nodenum].left = NULL;
                node[nodenum].medium = NULL;
                node[nodenum].right = NULL;
                node[pos].right = &node[nodenum];
                nodenum++;
            }
            break;
        default:
            break;
        }
        for (i = 0; i < cnt; i++)
        {
            arr[i] = 0;
        }
        cnt = 0;
        tmp = 0;
    }
    Gate gate[100] = {0};
    for (i = 0; i < gatenum; i++)
    {
        scanf("%d", &gate[i].num);
        scanf("%d", &gate[i].flow);
    }
    qsort(gate, gatenum, sizeof(Gate), compare);
    BFS_and_print(node, queue, gate, gatenum);
    return 0;
}