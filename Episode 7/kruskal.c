#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_VERTEX_NUM 2000
#define MAX_EDGE_NUM 10000
// 定义边的结构体
typedef struct Edge
{
    int id;
    int weight;
    int adjvex1;
    int adjvex2;
} ENode, *Edge;
typedef struct Vertex
{
    int info;  // 顶点信息
    Edge next; // Enode组成的链表的头节点
} Vnode, *Vertex;
typedef struct GNode
{
    Vnode adjlist[MAX_VERTEX_NUM]; // 邻接表
    int numVertexes, numEdges;     // 图中当前的顶点数和边数
} LGraph;

// 从所有边的集合中删去权值最小的边，返回该边
Edge DeleteMinEdge(Edge edges[], int n)
{
    int i, j, min = 0x7fffffff;
    for (i = 0; i < n; i++)
    {
        if (edges[i]->weight < min)
        {
            min = edges[i]->weight;
            j = i;
        }
    }
    Edge tmp = edges[j];
    edges[j] = edges[n - 1];
    edges[n - 1] = NULL;
    return tmp;
}
// 判断是否构成回路，构成回路返回0，否则返回1
int Find(int parent[], int f)
{
    while (parent[f] > 0)
        f = parent[f];
    return f;
}
int JudgeCycle(Edge mst[], int n, Edge e)
{
    int i, j;
    int parent[MAX_VERTEX_NUM] = {0};
    for (i = 0; i < n; i++)
    {
        parent[i] = -1;
    }
    for (i = 0; i < n; i++)
    {
        int f1 = Find(parent, mst[i]->adjvex1);
        int f2 = Find(parent, mst[i]->adjvex2);
        if (f1 != f2)
        {
            parent[f1] = f2;
        }
    }
    int f1 = Find(parent, e->adjvex1);
    int f2 = Find(parent, e->adjvex2);
    if (f1 != f2)
    {
        parent[f1] = f2;
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    // 所有边的集合
    Edge edges[MAX_EDGE_NUM] = {0};
    int edges_cnt = 0; // 记录边数
    // 最小生成树的边集数组
    Edge mst[MAX_EDGE_NUM] = {0};
    int mst_cnt = 0; // 记录边数
    // 读入顶点数和边数
    int vertexNum = 0, edgeNum = 0;
    scanf("%d %d", &vertexNum, &edgeNum);
    // 读入边的信息
    int i;
    for (i = 0; i < edgeNum; i++)
    {
        int id, adjvex1, adjvex2, weight;
        scanf("%d %d %d %d", &id, &adjvex1, &adjvex2, &weight);
        Edge e = (Edge)malloc(sizeof(ENode));
        e->id = id;
        e->adjvex1 = adjvex1;
        e->adjvex2 = adjvex2;
        e->weight = weight;
        edges[edges_cnt++] = e;
    }
    // 从所有边的集合中删去权值最小的边，加入到最小生成树的边集数组中
    while (mst_cnt < vertexNum - 1)
    {
        Edge e = DeleteMinEdge(edges, edges_cnt--);
        if (JudgeCycle(mst, mst_cnt, e))
        {
            mst[mst_cnt++] = e;
        }
    }
    // 计算并输出最小生成树的权值之和
    int sum = 0;
    for (i = 0; i < mst_cnt; i++)
    {
        sum += mst[i]->weight;
    }
    printf("%d\n", sum);
    // 按边序号升序输出最小生成树的边
    // 用冒泡排序
    int j;
    for (i = 0; i < mst_cnt - 1; i++)
    {
        for (j = 0; j < mst_cnt - i - 1; j++)
        {
            if (mst[j]->id > mst[j + 1]->id)
            {
                Edge tmp = mst[j];
                mst[j] = mst[j + 1];
                mst[j + 1] = tmp;
            }
        }
    }
    for (i = 0; i < mst_cnt; i++)
    {
        printf("%d ", mst[i]->id);
    }
    printf("\n");

    return 0;
}