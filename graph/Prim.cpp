#include <algorithm>
#include<stdio.h>
//prim算法,邻接矩阵版
#define MAXV  1000
#define INF  1000001

int n, m,G[MAXV][MAXV];//n是顶点个数，MAXV是最大顶点数
int d[MAXV];//顶点与集合S的最短距离
bool vis[MAXV] = {false};//标记数组未访问

//邻接矩阵版
int Prim(){//函数返回最小生成树的边权值之和
    for (int i = 1; i < MAXV;i++)//初始化数组d
        d[i] = INF;
    d[0] = 0;//只有0号顶点到集合S的距离为0，其余全为INF
    int ans = 0;//存放最小生成树的边权值之和
    for (int i = 0; i < n; i++)//循环n次
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
        //
        if(u==-1)
            return -1;//找不到小于INF的，则剩下的点不连通
        vis[u] = true;//标记u为已访问
        ans += d[u];//将与集合S距离最小的边加入最小生成树
        for (int v = 0; v < n; v++)//更新d[]
        {
            if (vis[v] == false && G[u][v] != INF && G[u][v] < d[v])//v未访问&&u能到达v&&以u为中介点可以使v离集合s更近
                d[v] = G[u][v];//将G[u][v]赋值给d[v]
        }
    }
    return ans;//返回最小生成树的边权值和
}
int main(int argc, char const *argv[])
{
    
    return 0;
}

