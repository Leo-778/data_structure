#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define VERTICES 6

//并查集

int find_root(int x, int parent[])  // 找到根节点
{
    int x_root = x;
    while (parent[x_root] != -1)
    {
        x_root = parent[x_root];
    }
    return x_root;
}
int union_vertices(int x, int y, int parent[],int rank[])  // 让两个集合合并
{
    int x_root = find_root(x, parent);
    int y_root = find_root(y, parent);
    if (x_root == y_root)
        return 0;
    else
    {
        if (rank[x_root] > rank[y_root])  // 让 少的指向多 的
        {
            parent[y_root] = x_root;
        }
        else if (rank[x_root] < rank[y_root])
            parent[x_root] = y_root;
        else
        {
            parent[x_root] = y_root;   // 这个随便可以
            rank[y_root]++;
        }
        return 1;
    }
}
int main(void)
{
    int parent[VERTICES] = { 0 };
    int rank[VERTICES] = { 0 };
    memset(rank, 0, sizeof(rank));
    memset(parent, -1, sizeof(parent));
    int edges[5][2] = { {0,1},{1,2},{1,3},{3,4},{2,5} };

    for (int i = 0; i < 5; i++)
    {
        int x = edges[i][0];
        int y = edges[i][1];
        if (union_vertices(x, y, parent,rank) == 0)
        {
            printf("Cycle detected!\n");
            exit(0);
        }
    }
    printf("No cycle found.\n");
    return 0;
}