#include<stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *elem;
    int len;
}SSTable;

//创建查找表
void Creat(SSTable &t,int *a,int n){
    t.elem = (int *)malloc(n * sizeof(int));
    t.len = n;
    for (int i = 0; i < n; i++)
    {
        t.elem[i] = a[i];
    }
    
}

int cnt=0;

//顺序查找
int Search_Seq(SSTable ST, int key){
    for (int i = 0; i < ST.len; i++)
    {
        if (ST.elem[i]==key)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int a[10] = {1, 2, 31, 42, 5, 6, 7, 8, 9, 0};
    SSTable t;
    Creat(t,a,10);
    Search_Seq(t, 2);
    printf("%d", cnt);
    return 0;
}
