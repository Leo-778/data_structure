#include<stdio.h>
//全排列问题
const int maxn = 11;

int n,P[maxn],used[maxn]={false};

void generate(int index){
    if (index == n+1)
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%d", P[i]);
        }
        printf("\n");
        return;
    }   
    for (int x = 1; x <= n; x++)
    {
        if (used[x]!=true)
        {
            used[x] = true;
            P[index] = x;
            generate(index + 1);
            used[x] = false;
        }
    }
}

int main(int argc, char const *argv[])
{
    n = 3;
    generate(1);
    return 0;
}
