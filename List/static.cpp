#include<stdio.h>

#define MaxSize 10//静态链表的最大长度
typedef int ElemType;

typedef struct {//静态链表结构类型的定义
    ElemType data;//存储数据元素
    int next; //下一个元素的数组下标
}SLinkList[MaxSize];

int main(int argc, char const *argv[])
{
    SLinkList a;
    return 0;
}

