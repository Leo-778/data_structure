#include<stdio.h>
const int maxn = 11;
int n, k;

typedef struct{
    int key[maxn]={0};
    int length=0;
}sq;

sq p;

void combine(int index){
    if (p.length==k)//终止条件，输出
    {
        for (int i = 1; i <= k; i++)
        {
            printf("%d ", p.key[i]);
        }
        printf("\n");
        return;
    }
    for (int x = index; x <= n; x++)
    {
        p.key[p.length + 1] = x;
        p.length++;//处理结点

        combine(x + 1);//递归

        p.length--;//回溯，撤销处理结点
    }
}

int main(int argc, char const *argv[])
{
    n = 9, k = 7;
    combine(1);
    return 0;
}
