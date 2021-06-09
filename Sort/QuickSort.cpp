#include<stdio.h>
#include<algorithm>
using namespace std;

//对区间[left,right]进行划分
int Partition(int *a,int left,int right){
    int temp = a[left];
    while (left<right)
    {
        while (left<right && a[right]>temp)
            right--;
        a[left] = a[right];
        while (left<right && a[left]<=temp)
            left++;
        a[right] = a[left];
    }
    a[left] = temp;
    return left;
}

//快速排序
void QuickSort(int *a,int left,int right){
    if(left<right){
        int pos = Partition(a, left, right);
        QuickSort(a, left, pos - 1);
        QuickSort(a, pos + 1, right);
    }
}

int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    QuickSort(a, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        if(i==9)
            printf("%d", a[i]);
        else
            printf("%d, ", a[i]);
    }
    
    return 0;
}