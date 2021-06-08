#include<stdio.h>

void BubbleSort(int *a,int n){
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if(a[i]>a[j])
            {
                temp = a[j];
                a[j] = a[i];
                a[i] = temp;
                
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 4, 5, 6, 8, 7, 1, 9, 0};
    BubbleSort(a, 10);
    for (int i = 0; i < 10; i++)
    {
        if(i==9)
            printf("%d", a[i]);
        else
            printf("%d, ", a[i]);
    }
    
    return 0;
}