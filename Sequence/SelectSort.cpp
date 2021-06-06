#include<stdio.h>
//选择排序
void SelectSort(int *A,int n){
    int temp;
    for (int j = 0; j < n; j++)
    {
        for (int i = 1; i < n; i++)
        {
            if(A[i-1]>A[i])
            {
                temp = A[i-1];
                A[i-1] = A[i];
                A[i] = temp;
            }
        }  
    }
    return;
}
int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 4, 5, 6, 8, 7, 1, 9, 0};
    SelectSort(a, 10);
    for (int i = 0; i < 10; i++)
    {
        if(i==9)
            printf("%d", a[i]);
        else
            printf("%d, ", a[i]);
    }
    
    return 0;
}
