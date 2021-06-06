#include<stdio.h>

#define MAXV  1000
#define INF  1000001

int n, m,G[MAXV][MAXV];//n是顶点个数，MAXV是最大顶点数
int d[MAXV];//顶点与集合S的最短距离长度
int pre[MAXV];//pre[v]表示从起点到顶点v的最短路径上v的前一个顶点
bool vis[MAXV] = {false};//标记数组，false表示未访问

void Dijkstra(int s){
    for (int i = 1; i < MAXV;i++)//初始化数组d
        d[i] = INF;
    d[0] = 0;//只有0号顶点到集合S的距离为0，其余全为INF
    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF;//u使d[u]最小，MIN存放最小的d[u]
        for (int j = 0; j < n; j++)//找到未访问中d[u]最小的
        {
            if (vis[j] == false && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            } 
        }
        if(u==-1)
            return ;//找不到小于INF的，则剩下的点不连通
        vis[u] = true;//标记u为已访问
        for (int v = 0; v < n; v++)//更新d[]
        {
            if (vis[v] == false && G[u][v] != INF && d[u]+G[u][v] < d[v])//v未访问&&u能到达v&&以u为中介点可以使d[v]更优
            {   
                d[v] = d[u]+G[u][v];//将G[u][v]赋值给d[v]
                pre[v] = u;         //记录v的前驱顶点是u
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
