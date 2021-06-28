#include<stdio.h>

const int maxn = 11;
typedef struct{
    int key[maxn]={0};
    int length=0;
}sq;
sq p;

int a[3] = {1, 2, 3};//测试集合
int n = 3;

void subsets(int index)
{
    for (int j = 0; j < p.length; j++)//在终止条件前打印出来，避免遗漏空集情况。
    {
        printf("%d ", p.key[j]);
    }
    printf("\n");

    if (index >=n)//终止条件
        return;
    
    for (int i = index; i < n; i++)
    {
        p.key[p.length] = a[i];
        p.length++;//处理结点

        subsets(i+1);//递归

        p.length--;//回溯，撤销处理结点
    }
}

int main(int argc, char const *argv[])
{
    subsets(0);
    return 0;
}
