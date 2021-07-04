#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

#define MaxSize 10 //定义队列中元素的最大个数
typedef struct{
    ElemType data[MaxSize];
    int front, rear; //队头指针和队尾指针
} SqQueue;

//初始化队列
void InitQueue(SqQueue &Q){
    Q.rear = Q.front = 0;//初始时 队头、队尾指针指向0
}

//判断队列是否为空
bool QueueEmpty(SqQueue Q){
    if(Q. rear==Q. front) //队空条件
        return true;
    else
        return false;
}