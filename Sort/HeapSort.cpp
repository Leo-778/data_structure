#include<stdio.h>

#include<algorithm>
using namespace std;

//打印测试
void print(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//从小到大排序（结果就是大顶堆）
void Down(int *a,int i,int n){
    int parent = i;
    int child = 2 * i + 1;
    while (child < n)
    {
        if (child + 1 < n && a[child] < a[child + 1])
        {
            child++;
        }
        if(a[parent]<a[child])
        {
            swap(a[parent], a[child]);
            parent = child;
        }
        child = child * 2 + 1;
    }
}

//建立大顶堆
void BuildHeap(int *a,int n){
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Down(a, i, n);
    }
}

//堆排序
void HeapSort(int *a,int n){
    BuildHeap(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);

        Down(a, 0, i);
        print(a, n);
    }
}

const int maxn = 100;
int heap[maxn], n = 10;
//对heap数组在[low,high]范围内进行向下调整
void DownAdjust(int low,int high){
    int i = low, j = i * 2;//i为与调整节点，j为其左孩子。
    while (j<=high)
    {
        if (j + 1 <= high && heap[j+1]>heap[j])
            j = j + 1;
        if(heap[j]>heap[i]){
            swap(heap[j], heap[i]);
            i = j;
            j = i * 2;
        }else{
            break;//孩子节点比与调整节点i小，调整结束。
        }
    }
    
}
//对heap数组在[low,high]范围内进行向上调整
void UpAdjust(int low,int high){
    int i = low, j = i * 2;//i为与调整节点，j为其左孩子。
    while (j>=low)
    {
        if(heap[j]<heap[i]){
            swap(heap[j], heap[i]);
            i = j;
            j = i / 2;
        }else{
            break;//孩子节点比与调整节点i小，调整结束。
        }
    }
}
//插入
void Insert(int x){
    heap[++n] = x;
    UpAdjust(1, n);
}

//删除
void DeleteTop(){
    heap[1] = heap[n--];
    DownAdjust(1, n);
}

int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    HeapSort(a, 10);
    
    return 0;
}