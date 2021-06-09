#include<stdio.h>

#include<iostream>
using namespace std;

//打印测试
void print(int a[], int n ,int i){
    printf("%d:",i);
    for(int j=0; j<10; j++){
        printf("%d",a[j]);
    }
    printf("\n");
}

void SelectSort(int a[],int n){
    int temp;
    for(int i=0;i<n-1;i++){
        temp=i;      
        for(int j=i+1;j<n;j++){
            if(a[temp]>a[j]){   
                temp=j;  
            }
        }
        swap(a[i],a[temp]); 
        print(a, 10, i);
    }
} 
int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    SelectSort(a, 10);
    // for (int i = 0; i < 10; i++)
    // {
    //     if(i==9)
    //         printf("%d", a[i]);
    //     else
    //         printf("%d, ", a[i]);
    // }
    
    return 0;
}
