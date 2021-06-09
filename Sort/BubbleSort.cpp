#include<stdio.h>
#include<algorithm>
using namespace std;

//打印测试
void print(int a[], int n ,int i){
    printf("%d:",i);
    for(int j=0; j<10; j++){
        printf("%d",a[j]);
    }
    printf("\n");
}

void BubbleSort(int *a,int n){
    int count = 0;
    for (int i = 0; i < n-1; i++)
    {
        count = 0;
        for (int j = n-1; j > i; j--)
        {
            if(a[j-1]>a[j])
            {
                count = 1;
                swap(a[j-1], a[j]);
            }
        }
        if (count==0)
            break;

        print(a, 10, i);
    }
}

int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    BubbleSort(a, 10);
    
    return 0;
}