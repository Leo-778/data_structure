#include<stdio.h>
#include<stdlib.h>
//并查集
#define VERTICES 6

void Initialise(int parent[],int rank[]){
    for (int i = 0; i < VERTICES ; i++)
    {
        parent[i] = -1;
        rank[i] = 0;
    }
    return;
}

int Find_root(int x,int parent[]){
    int x_root = x;
    while (parent[x_root]!=-1)
    {
        x_root = parent[x_root];
    }
    return x_root;
}

int Union_Vertices(int x,int y,int parent[],int rank[]){
    int x_root = Find_root(x,parent);
    int y_root = Find_root(y, parent);
    if(x_root==y_root)
        return 0;
    else{
        if(rank[x_root] > rank[y_root])
            parent[y_root] = x_root;
        else if(rank[y_root] > rank[x_root])
            parent[x_root] = y_root;
        else{
            parent[x_root] = y_root;
            rank[y_root]++;
        }
        return 1;
    }
}

int main(int argc, char const *argv[])
{
    int parent[VERTICES] = {0};
    int rank[VERTICES] = {0};
    Initialise(parent, rank);
    int edges[5][2] = {
        {0, 1}, {1, 2}, {1, 3}, {3, 4}, {2, 5}};
    for (int i = 0; i < 5; i++)
    {   
        int x = edges[i][0];
        int y = edges[i][1];
        if(Union_Vertices(x,y,parent,rank)==0){
            printf("Cycle detected!\n");
            exit(0);
        }
    }
    printf("No Cycles Find!\n");
    return 0;
}
