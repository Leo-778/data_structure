#include<stdio.h>
#include<algorithm>
using namespace std;
//最优装载问题

const int maxweight = 30;
const int n = 8;
int cnt = 0,p[n];

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
    int summ=0;
    sort(w, w + 8);
    maxloading(w, n);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
    {
        summ += p[i];
        printf("%d ", p[i]);
    }
    printf("\n%d ", summ);
    return 0;
}
