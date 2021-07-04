#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct LNode{//定义单链表结点类型
    ElemType data;//每个节点存放1个数据元素
    struct LNode *next ;//指针指向下一个节点
}LNode, *LinkList;

typedef struct DNode{
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinklist;

//初始化一个循环单链表
bool InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode)); //分配一个头结点
    if (L==NULL)//内存不足， 分配失败
        return false;
    L->next = L; //头结点next指向头结点
    return true;
}

//判断循环单链表是否为空
bool Empty(LinkList L) {
    if (L->next ==L)
        return true;
    else
        return false;
}

//判断结点p是否为循环单链表的表尾结点
bool isTail(LinkList L, LNode *p){
    if (p->next==L)
        return true;
    else
        return false;
}

//初始化空的循环双链表
bool InitDLinklist(DLinklist &L){
    L = (DNode *) malloc(sizeof(DNode)); //分配-个头结点
    if (L==NULL)//内存不足， 分配失败
        return false;
    L->prior = L;    //头结点的prior 指向头结点
    L->next = L;     //头结点的next 指向头结点
    return true;
}

//判断循环双链表是否为空
bool Emptv(DLinklist L) {
    if (L ->next ==L)
        return true;
    else
        return false;
}
//判断结点p是否为循环单链表的表尾结点
bool isTail(DLinklist L, DNode *p){
    if (p->next==L)
        return true;
    else
        return false;
}

//在p结点之后插入s结点
bool InsertNextDNode (DNode *p, DNode *s){
    s->next = p->next; //将结点*s插入到结点*p之后
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

int main(int argc, char const *argv[])
{
    LinkList l;
    DLinklist p;
    return 0;
}

