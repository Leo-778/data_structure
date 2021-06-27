#include<stdio.h>
#include<algorithm>
using namespace std;

const int n = 5;

bool canJump(int *nums){
    int maxreach = 0;//maxreach 表示当前第i个位置最远可以到大的位置
    for (int i = 0; i < n; ++i) {
        if(i>maxreach)
            return false;
        maxreach = max(i + nums[i], maxreach);//更新maxreach
        if (maxreach>=n-1)
            return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int p[5] = {3,2,1,0,4};
    printf("%d",canJump(p));
    return 0;
}
