#include<stdio.h>
#include<algorithm>
using namespace std;

int n = 7;

int jump(int *nums){
    int maxpos = 0;// 目前能跳到的最远位置
    int step = 0;//步数
    int end = 0; // 上次跳跃可达范围右边界（下次的最右起跳点）
    for (int i = 0; i < n-1; i++)
    {
            if(maxpos >=i ){
                maxpos = max(maxpos, i + nums[i]);
                if (i==end)// 到达上次跳跃能到达的右边界了
                {
                    end = maxpos;// 目前能跳到的最远位置变成了下次起跳位置的有边界
                    ++step;// 进入下一次跳跃
                }
            }
    }
    return step;
}
int main(int argc, char const *argv[])
{
    int nums[n] = {2,3,1,2,4,2,3};
    printf("%d", jump(nums));
    return 0;
}