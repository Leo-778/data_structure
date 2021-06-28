#include<stdio.h>
//组合求和

const int maxn = 11;
int target;

typedef struct{
    int key[maxn]={0};
    int length=0;
}sq;
sq p;

void combinationSum(int index,int *a,int n,int sum){
    if(sum==target){
        for (int i = 1; i <= p.length; i++)
        {
            printf("%d ",p.key[i]);
        }
        printf("\n");
        return;
    }
    if (sum>target)//超过return
        return;
    for (int x = index; x < n; x++)
    {
        sum += a[x];
        
        p.key[p.length + 1] = a[x];
        p.length++;//处理结点
        
        combinationSum(x,a,n,sum);//关键点，不需要+1了，因为可以重复读取

        sum -= a[x];//回溯
        p.length--;//回溯
    }
    
}

int main(int argc, char const *argv[])
{
    int candidates[4] = {2, 3, 6, 7};
    target = 7;
    combinationSum(0, candidates, 4,0);
    return 0;
}
