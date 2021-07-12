#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

#define MaxSize 10 //定义队列中元素的最大个数
typedef struct{
    ElemType data[MaxSize];
    int front, rear; //队头指针和队尾指针
    int size=0;
    int tag;
} SqQueue;

//初始化队列
void InitQueue(SqQueue &Q){
    Q.rear = Q.front = 0;//初始时 队头、队尾指针指向0
}

//判断队列是否为空
bool QueueEmpty1(SqQueue Q){
    if(Q. rear==Q. front) //队空条件
        return true;
    else
        return false;
}

//2、判断队列是否为空
bool QueueEmpty2(SqQueue Q){
    if(Q.size == MaxSize) //队空条件
        return true;
    else
        return false;
}

//3、判断队列是否为空
bool QueueEmpty3(SqQueue Q){
    if(Q. rear==Q. front && Q.tag == 0) //队空条件
        return true;
    else
        return false;
}

//1判断队满
bool QueueFull1(SqQueue Q){
    if ((Q.rear+1)%MaxSize==Q.front)
        return true;
    else
        return false;
}

//2判断队满
bool QueueFull2(SqQueue Q){
    if (Q.size==MaxSize)
        return true;
    else
        return false;
}

//3判断队满
bool QueueFull3(SqQueue Q){
    if (Q. rear==Q. front && Q.tag == 1)
        return true;
    else
        return false;
}

//出队
bool DeQueue(SqQueue &Q,ElemType &x){
    if(QueueEmpty1){
        return false;
    }
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    // Q.size--;  //使用方法2
    // Q.tag = 0; //使用方法3
    return true;
}

//入队
bool EnQueue(SqQueue &Q,ElemType x){
    if (QueueFull1)
        return true;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    // Q.size++;  //使用方法2
    // Q.tag = 1; //使用方法3
    return true;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
