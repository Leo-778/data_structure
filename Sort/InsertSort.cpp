#include<stdio.h>

//打印测试
void print(int a[], int n ,int i){
    printf("%d:",i);
    for(int j=0; j<10; j++){
        printf("%d",a[j]);
    }
    printf("\n");
}

//直接插入排序
void InsertSort(int *a,int n){
    int temp;
    for (int i = 1; i < n; i++)
    {
        temp = a[i];
        int j=i;
        while (temp < a[j - 1])
        {
            a[j ] = a[j-1];
            j--;
        }
        a[j] = temp;
        print(a, 10, i);
    }
}

//折半插入排序
void BInsertSort(int *a,int size){
    int i, j, low = 0, high = 0, mid;
    int temp;
    for (i = 1; i < size; i++)
    {
        low = 0;
        high = i - 1;
        temp = a[i];
        while (low<=high)
        {
            mid = (low + high) / 2;
            if(a[mid]>temp)
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (j = i; j > low; j--)
            a[j] = a[j - 1];
        a[low] = temp;
        print(a, 10, i);
    }
}

int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    BInsertSort(a, 10);
    
    return 0;
}
