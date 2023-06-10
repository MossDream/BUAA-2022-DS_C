#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 邻接矩阵图结构定义
#define MAX_VERTEX_NUM 100
#define INFINITY 65535
typedef int VertexType;
typedef int EdgeType; // 这里边的类型是指权值，本题只是简单的图，所以权值都为1
typedef struct GNode
{
    VertexType vexs[MAX_VERTEX_NUM];              // 顶点表
    EdgeType arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵，可看作边表
    int numVertexes, numEdges;                    // 图中当前的顶点数和边数
} MGraph;
// 初始化一个有n个顶点但没有边的图
MGraph *CreateMGraph(MGraph *G, int n)
{
    G = (MGraph *)malloc(sizeof(MGraph));
    int i, j;
    G->numEdges = 0;
    G->numVertexes = n;
    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = INFINITY;
        }
    }
    for (i = 0; i < G->numVertexes; i++)
    {
        G->vexs[i] = i;
    }
    return G;
}
// 向图中插入一条边，这里是无向图且边用两个顶点表示
void InsertEdge(MGraph *G, VertexType v1, VertexType v2)
{
    G->arc[v1][v2] = 1;
    G->arc[v2][v1] = 1;
}
// 删除图中的指定顶点
void DeleteVertex(MGraph *G, VertexType v)
{
    int i, j;
    for (i = 0; i < G->numVertexes; i++)
    {
        G->arc[i][v] = INFINITY;
        G->arc[v][i] = INFINITY;
    }
}
int visited[MAX_VERTEX_NUM] = {0}; // 访问标志数组
// 深度优先搜索遍历图的递归实现,本题从第1个元素开始遍历
void DFS(MGraph *G, VertexType v)
{
    int j;
    visited[v] = 1;
    printf("%d ", G->vexs[v]);
    for (j = 0; j < G->numVertexes; j++)
    {
        if (G->arc[v][j] == 1 && !visited[j])
        {
            DFS(G, j);
        }
    }
}
// 广度优先搜索遍历图的递归实现,本题从第1个元素开始遍历
void BFS(MGraph *G, VertexType v)
{
    VertexType queue[MAX_VERTEX_NUM] = {0};
    int j;
    VertexType *front = queue;
    VertexType *rear = queue;
    visited[v] = 1;
    printf("%d ", G->vexs[v]);
    *rear++ = v;
    while (front != rear)
    {
        v = *front++;
        for (j = 0; j < G->numVertexes; j++)
        {
            if (G->arc[v][j] == 1 && !visited[j])
            {
                visited[j] = 1;
                printf("%d ", G->vexs[j]);
                *rear++ = j;
            }
        }
    }
}
int main()
{
    int vertexNum = 0, edgeNum = 0, i = 0;
    scanf("%d %d", &vertexNum, &edgeNum);
    MGraph *G = CreateMGraph(G, vertexNum);
    for (i = 0; i < edgeNum; i++)
    {
        VertexType v1 = 0, v2 = 0;
        scanf("%d %d", &v1, &v2);
        InsertEdge(G, v1, v2);
    }
    VertexType deleteVertex = 0;
    scanf("%d", &deleteVertex);

    DFS(G, 0);
    printf("\n");
    memset(visited, 0, sizeof(visited));
    BFS(G, 0);
    printf("\n");
    memset(visited, 0, sizeof(visited));

    DeleteVertex(G, deleteVertex);
    DFS(G, 0);
    printf("\n");
    memset(visited, 0, sizeof(visited));
    BFS(G, 0);
    printf("\n");

    return 0;
}