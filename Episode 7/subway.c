#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// 邻接矩阵图结构定义
#define MAX_VERTEX_NUM 1000
#define INFINITY 65535
// 定义顶点类型(这里是一个站点)
typedef struct Vertex
{
    char station_name[70];
    int is_transfer;
} Vertex;
typedef Vertex VertexType;
// 定义边的类型(包括两站点路线的地铁编号和路线权重，权重这里为1)
typedef struct Edge
{
    int line_id;
    int weight;
} Edge;
typedef Edge EdgeType;
typedef struct GNode
{
    VertexType vexs[MAX_VERTEX_NUM];              // 顶点表
    EdgeType arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵，可看作边表
    int numVertexes, numEdges;                    // 图中当前的顶点数和边数
} MGraph;
// 向图中加入一个顶点(站点信息),返回顶点在表中的下标
int AddVertex(MGraph *G, VertexType v)
{
    int i;
    for (i = 0; i < G->numVertexes; i++)
    {
        if (strcmp(G->vexs[i].station_name, v.station_name) == 0)
        {
            return i;
        }
    }
    strcpy(G->vexs[G->numVertexes].station_name, v.station_name);
    G->vexs[G->numVertexes].is_transfer = v.is_transfer;
    G->numVertexes++;
    return G->numVertexes - 1;
}
// 简单初始化图
MGraph *InitGraph(MGraph *G)
{
    G = (MGraph *)malloc(sizeof(MGraph));
    int i, j;
    G->numEdges = 0;
    G->numVertexes = 0;
    for (i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (j = 0; j < MAX_VERTEX_NUM; j++)
        {
            G->arc[i][j].line_id = 0;
            G->arc[i][j].weight = INFINITY;
        }
    }
    return G;
}
// 根据文件中的输入信息建立图
MGraph *BuildGraph(MGraph *G, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        return NULL;
    }
    int last_vertex_index;    // 上一个顶点的下标
    int current_vertex_index; // 当前顶点的下标
    VertexType input;         // 输入的站点信息
    int line_num;             // 线路数量
    fscanf(fp, "%d", &line_num);
    int i = 0;
    for (i = 0; i < line_num; i++)
    {
        int line_id;     // 线路编号
        int station_num; // 站点数量
        fscanf(fp, "%d %d", &line_id, &station_num);
        last_vertex_index = -1;
        current_vertex_index = -1;
        int j = 0;
        for (j = 0; j < station_num; j++)
        {
            fscanf(fp, "%s %d", input.station_name, &input.is_transfer);
            current_vertex_index = AddVertex(G, input);
            if (last_vertex_index != -1)
            {
                G->arc[last_vertex_index][current_vertex_index].line_id = line_id;
                G->arc[last_vertex_index][current_vertex_index].weight = 1;
                G->arc[current_vertex_index][last_vertex_index].line_id = line_id;
                G->arc[current_vertex_index][last_vertex_index].weight = 1;
            }
            last_vertex_index = current_vertex_index;
        }
    }
    fclose(fp);
    return G;
}
int FindStation(MGraph *G, char *station_name)
{
    int i;
    for (i = 0; i < G->numVertexes; i++)
    {
        if (strcmp(G->vexs[i].station_name, station_name) == 0)
        {
            return i;
        }
    }
    return -1;
}
// Dijkstra算法
int dist[MAX_VERTEX_NUM];      // 表示当前点到源点的最短路径长度
int path[MAX_VERTEX_NUM];      // 记录当前点的前一个顶点
int collected[MAX_VERTEX_NUM]; // 表示当前点是否已经收录到集合S中
void Dijkstra(MGraph *G, int start_station_index)
{
    // 初始化
    int i;
    for (i = 0; i < G->numVertexes; i++)
    {
        dist[i] = G->arc[start_station_index][i].weight;
        if (dist[i] < INFINITY)
        {
            path[i] = start_station_index;
        }
        else
        {
            path[i] = -1;
        }
        collected[i] = 0;
    }
    dist[start_station_index] = 0;
    collected[start_station_index] = 1;
    path[start_station_index] = start_station_index;
    // 开始循环
    int v;
    while (1)
    {
        int min_dist = INFINITY;
        int min_dist_index = -1;
        for (i = 0; i < G->numVertexes; i++)
        {
            if (collected[i] == 0 && dist[i] < min_dist)
            {
                min_dist = dist[i];
                min_dist_index = i;
            }
        }
        if (min_dist_index == -1)
        {
            break;
        }
        collected[min_dist_index] = 1;
        for (v = 0; v < G->numVertexes; v++)
        {
            if (collected[v] == 0 && G->arc[min_dist_index][v].weight < INFINITY)
            {
                if (dist[min_dist_index] + G->arc[min_dist_index][v].weight < dist[v])
                {
                    dist[v] = dist[min_dist_index] + G->arc[min_dist_index][v].weight;
                    path[v] = min_dist_index;
                }
            }
        }
    }
}
// 打印路径,注意只需要打印换乘站及途径路线的信息
int final_path[MAX_VERTEX_NUM];
int final_path_num = 0;
// 找到最终路径,仍包括非换乘站
void FindFinalPath(int start_station_index, int end_station_index)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int temp = end_station_index;
    final_path[0] = end_station_index;
    final_path_num = 1;
    while (temp != start_station_index)
    {
        final_path[final_path_num++] = path[temp];
        temp = path[temp];
    }
    // 逆序
    for (i = 0, j = final_path_num - 1; i < j; i++, j--)
    {
        temp = final_path[i];
        final_path[i] = final_path[j];
        final_path[j] = temp;
    }
}
int last_final_path_index = 0;
int current_final_path_index = 1;
void PrintPath(MGraph *G)
{
    int line_id = 0;
    int distance = 0;
    int current_line = G->arc[final_path[0]][final_path[1]].line_id;
    printf("%s", G->vexs[final_path[0]].station_name);
    for (current_final_path_index = 1; current_final_path_index < final_path_num; current_final_path_index++)
    {
        if (G->arc[final_path[last_final_path_index]][final_path[current_final_path_index]].line_id != current_line)
        {
            printf("-%d(%d)-%s", current_line, distance, G->vexs[final_path[last_final_path_index]].station_name);
            current_line = G->arc[final_path[last_final_path_index]][final_path[current_final_path_index]].line_id;
            distance = 0;
        }
        distance++;
        last_final_path_index = current_final_path_index;
    }
    printf("-%d(%d)-%s", current_line, distance, G->vexs[final_path[last_final_path_index]].station_name);
}
int main()
{
    char filename[100] = {"bgstations.txt"};
    char start_station[70] = {0};
    char end_station[70] = {0};
    scanf("%s %s", start_station, end_station);
    int start_station_index = -1;
    int end_station_index = -1;
    MGraph *G = NULL;
    G = InitGraph(G);
    G = BuildGraph(G, filename);
    start_station_index = FindStation(G, start_station);
    end_station_index = FindStation(G, end_station);
    Dijkstra(G, start_station_index);
    FindFinalPath(start_station_index, end_station_index);
    PrintPath(G);
    return 0;
}