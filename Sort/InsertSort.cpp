#include<stdio.h>
//插入排序
void InsertSort(int *a,int n){
    int temp;
    for (int i = 1; i <= n; i++)
    {
        temp = a[i];
        int j=i;
        while (temp < a[j - 1])
        {
            a[j ] = a[j-1];
            j--;
        }
        a[j] = temp;
    }
}
int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 4, 5, 6, 8, 7, 1, 9, 0};
    InsertSort(a, 10);
    for (int i = 0; i < 10; i++)
    {
        if(i==9)
            printf("%d", a[i]);
        else
            printf("%d, ", a[i]);
    }
    
    return 0;
}
