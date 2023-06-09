#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 邻接表图结构定义
#define MAX_VERTEX_NUM 2000
typedef struct Edge
{
    int id;     // 路径编号
    int adjvex; // 代表每个邻接点在顶点数组中的下标
    int weight; // 权重
    struct Edge *next;
} Enode, *Edge;
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

int visited[MAX_VERTEX_NUM] = {0}; // 访问标志数组
int path[MAX_VERTEX_NUM] = {0};    // 记录路径

Edge InsertEdge(Edge head, int id, int vertex)
{
    Edge e, p;
    e = (Edge)malloc(sizeof(Enode));
    e->id = id;
    e->adjvex = vertex;
    e->weight = 1;
    e->next = NULL;   // 录入信息
    if (head == NULL) // 构造头节点
    {
        head = e;
        return head;
    }
    else
    {
        for (p = head; p->next != NULL; p = p->next)
            ;
        p->next = e; // 插入节点
        return head;
    }
}
void PrintPath(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", path[i]);
    }
    puts("");
}
void _DFS(LGraph *G, int v, int level)
{
    Edge p;
    if (v == G->numVertexes - 1)
    {
        PrintPath(level);
        return;
    }
    for (p = G->adjlist[v].next; p != NULL; p = p->next)
    {
        if (visited[p->adjvex] == 0)
        {
            visited[p->adjvex] = 1;
            path[level] = p->id;
            _DFS(G, p->adjvex, level + 1);
            visited[p->adjvex] = 0;
        }
    }
    return;
}
void FindPath(LGraph *G)
{
    _DFS(G, 0, 0);
}
int main()
{
    int i = 0;
    int vertexNum, edgeNum;
    scanf("%d %d", &vertexNum, &edgeNum);
    LGraph *G;
    G = (LGraph *)malloc(sizeof(LGraph));
    G->numVertexes = vertexNum;
    G->numEdges = edgeNum;
    for (i = 0; i < vertexNum; i++)
    {
        G->adjlist[i].info = i; // 顶点信息
        G->adjlist[i].next = NULL;
    }
    for (i = 0; i < edgeNum; i++)
    {
        int v1 = 0, v2 = 0, id = 0;
        scanf("%d %d %d", &id, &v1, &v2);
        G->adjlist[v1].next = InsertEdge(G->adjlist[v1].next, id, v2);
        G->adjlist[v2].next = InsertEdge(G->adjlist[v2].next, id, v1);
    }
    visited[0] = 1; // 初始化访问标志数组
    FindPath(G);
    return 0;
}
