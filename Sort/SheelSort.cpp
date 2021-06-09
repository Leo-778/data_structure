#include<stdio.h>

//打印测试
void print(int a[], int n ,int i){
    printf("%d:",i);
    for(int j=0; j<10; j++){
        printf("%d",a[j]);
    }
    printf("\n");
}


void SheelSort(int *a,int n){
    int gap = n / 2;
    for (  ; gap>0; gap = gap / 2)
    {
        for (int i = gap; i <= n; i++)
        {
            int temp = a[i];
            int j;
            for (j = i-gap; j>=0&&temp<a[j]; j-=gap)
            {
                a[j + gap] = a[j];
            }
            a[j + gap] = temp;
        }
        print(a, 10, gap);
    }
}


int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    SheelSort(a, 10);
    
    return 0;
}
