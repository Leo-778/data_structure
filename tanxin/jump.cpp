#include<stdio.h>
#include<algorithm>
using namespace std;

int n = 5;

int jump(int *nums){
    int maxcover = 0;//表示当前第i个位置最远可以到达的位置
    int step = 0;//步数
    int nextcover = 0;//第i+1个位置最远可以到达的位置
    for (int i = 0; i < n; i++)
    {
        nextcover = max(nums[i] + i, nextcover);//更新下⼀步覆盖最远距离下标
        if (i==maxcover)// 遇到当前覆盖最远距离下标
        {
            if (maxcover!=n-1)// 如果当前覆盖最远距离下标不是终点
            {
                step++;// 需要⾛下⼀步
                maxcover = nextcover;// 更新当前覆盖最远距离下标
                if (nextcover>=n-1)
                {
                    break;// 下⼀步的覆盖范围已经可以达到终点，结束循环
                }
            }
            else break; 
        }
        
    }
    return step;
}
int main(int argc, char const *argv[])
{
    int nums[n] = {2,3,1,1,4};
    printf("%d", jump(nums));
    return 0;
}
