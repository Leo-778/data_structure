#include<stdio.h>

#include<algorithm>
using namespace std;

const int maxn = 100;

//将数组a的[l1,r1]和[l2,r2]区间合并
void merge(int *a, int l1, int r1, int l2, int r2){
    int i = l1, j = l2;
    int temp[maxn], index = 0;
    while (i <= r1 && j <= r2)
    {
        if(a[i]<=a[j]){
            temp[index++] = a[i++];
        }
        else{
            temp[index++] = a[j++];
        }
    }
    while(i<=r1)
        temp[index++] = a[i++];
    while(j<=r2)
        temp[index++] = a[j++];
    for (int i = 0; i < index; i++)
        a[l1 + i] = temp[i];//将合并后的序列赋值回数组a
}

//递归实现
void MergeSort(int *a,int left,int right){
    if (left<right)
    {
        int mid = (left + right) / 2;
        MergeSort(a, left, mid);
        MergeSort(a, mid + 1, right);
        merge(a, left, mid, mid + 1, right);
    }
}

//非递归实现
void MergeSort_2(int *a,int n){
    for (int step = 2; step / 2 <= n; step *= 2)
    {
        for (int i = 0; i < n; i+=step)
        {
            int mid = i + step / 2 - 1;
            if (mid + 1 <= n)
            {
                merge(a, i, mid, mid + 1, min(i + step - 1, n));
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    MergeSort_2(a, 10);
    for (int i = 0; i < 10; i++)
    {
        if(i==9)
            printf("%d", a[i]);
        else
            printf("%d, ", a[i]);
    }
    
    return 0;
}