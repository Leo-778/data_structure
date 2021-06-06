#include<stdio.h>


const int MAXN = 1000;
vector<int> G[MAXN];
int n, m;//顶点数、边数
int inDegree[MAXN];//入度

bool topologicalSort(){
    int num = 0;
    queue<int> q;
    for (int i = 0; i < n; ++i)
    {
        if(inDegree[i] == 0){
            q.push(i);    //将所有入度为0的顶点入队
        }
    }

    while(!q.empty()){
        int u = q.front();
        //printf("%d", u);//此处可输出顶点u，作为拓扑序列中的顶点
        q.pop();
        
        for (int i = 0; i < G[u].size(); ++i)
        {
            int v = G[u][i];//u的后继结点v
            inDegree[v]--;//顶点v的入度减1
            if(inDegree[v] == 0){//顶点v的入度减为0，则入队
                q.push(v);
            }
        }
        G[u].clear();//清空顶点u的所有出边（如无必要可不写）
        num++;//加入拓扑序列的顶点数加1
    }

    if(num == n) return true;//给的图是有向无环图
    else return false;  //给定的图中有还
}