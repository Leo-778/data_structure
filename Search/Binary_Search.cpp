#include<stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *elem;
    int len;
}SSTable;

//创建查找表
void Creat(SSTable &t,int *a,int n){
    t.elem = (int *)malloc(n * sizeof(int));
    t.len = n;
    for (int i = 0; i < n; i++)
    {
        t.elem[i] = a[i];
    }
    
}

int Binary_Search(SSTable t,int key){
    int low = 0, high = t.len - 1, mid;
    while(low<=high){
        mid = (low + high) / 2;
        if (t.elem[mid]==key)
        {
            return mid;
        }
        if (t.elem[mid]<key)
        {
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}


int main(int argc, char const *argv[])
{
    int a[10] = {0,1, 2, 3, 4, 5, 6, 7, 8, 9};
    SSTable t;
    Creat(t,a,10);
    int i = Binary_Search(t, 3);
    printf("%d", i);
    return 0;
}
