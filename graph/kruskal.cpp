#include<stdio.h>
#include<cstdio>
#include<algorithm>

const int MAXV = 110;
const int MAXE = 10010;
//边集定义
struct edge{
    int u, v;//边的两个端点
    int cost;//边的权值
}E[MAXE];//最多有MAXE条边
bool cmp(edge a,edge b){
    return a.cost < b.cost;
}
//并查集部分
int root[MAXV];//并查集的数组
int Findroot(int x){//并查集查询函数
    int a = x;
    while (x != root[x])
    {
        x = root[x];
    }
    //路径压缩
    while (a != root[x])
    {
        int z = a;
        a = root[a];
        root[z] = x;
    }
    return x;
}
//kruskal部分，返回最小生成树的边权之和，参数n为顶点个数，m为图的边数
int kruskal(int n,int m){
    //ans为所求边权之和，Num_Edge为当前生成树的边数
    int ans = 0, Num_Edge = 0;
    for (int i = 0; i < n; i++)//顶点的范围是[0，n-1]
    {
        root[i] = i;//并查集初始化
    }
    //sort(E, E + m, cmp);//将所有边按照边权值从小到大排序
    for (int i = 0; i < m; i++)//枚举所有边
    {
        int faU = Findroot(E[i].u);//查询边的两个端点所在集合的根节点
        int faV = Findroot(E[i].v);
        if (faU != faV)
        {
            root[faU] = faV;//合并集合（即把测试边加入到最小生成树中）
            ans += E[i].cost;//边权之和加入测试边
            Num_Edge++;//当前生成树+1
            if(Num_Edge == n-1)//生成树边数=n-1时结束算法
                break;
        }
    }
    if(Num_Edge !=n-1)
        return -1;//无法连通返回-1
    else
        return ans;
}
int main(int argc, char const *argv[])
{
    
    return 0;
}
