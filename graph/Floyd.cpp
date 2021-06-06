#include<stdio.h>


#define MAXV  200
#define INF  1000001

int n, m;   //n是顶点个数，m为边数
int dis[MAXV][MAXV];//dis[i][j]表示顶点i和顶点j的最短距离
int path[MAXV][MAXV];//两个顶点之间的中转点


void Floyd(){
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n;j++)
            {
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = k;
                }
            }
            
        }
}