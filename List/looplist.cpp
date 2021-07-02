#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct LNode{//定义单链表结点类型
    ElemType data;//每个节点存放1个数据元素
    struct LNode *next ;//指针指向下一个节点
}LNode, *LinkList;

//初始化一个循环单链表
bool InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode)); //分配一个头结点
    if (L==NULL)//内存不足， 分配失败
        return false;
    L->next = L; //头结点next指向头结点
    return true;
}
