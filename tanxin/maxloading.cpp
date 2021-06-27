#include<stdio.h>
#include<algorithm>
using namespace std;
//最优装载问题

const int maxweight = 30;//船只的最大载重
const int n = 8;//货物数量
int cnt = 0,p[n];//数组p用来存放可以放入的货物的重量

void maxloading(int *w,int n){
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (sum+w[i]<maxweight)
        {
            sum += w[i];
            cnt++;
            p[i] = w[i];
        }
        else
            break;
    }
}
int main(int argc, char const *argv[])
{
    int w[n] = {4, 10, 7, 11, 3, 5, 14, 2};
    sort(w, w + 8);//排序（从w[0]到w[7]排序）
    maxloading(w, n);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
    {
        printf("%d ", p[i]);
    }
    return 0;
}