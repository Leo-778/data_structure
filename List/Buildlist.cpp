#include<stdio.h>
#include<stdlib.h>
//建立单链表(头插法，尾插法)
typedef int ElemType;

typedef struct LNode               //定义单链表结点类型
{
    ElemType data;                //每个节，点存放一个数据元素
    struct LNode *next;           //指针指向下一个节点
} LNode, *LinkList;

bool InitList(LinkList &l){
    l = (LNode *)malloc(sizeof(LNode));//分配头结点
    if (l==NULL)       //内存不足，分配失败
        return false;
    l->next = NULL;    //头结点之后暂时还没有节点
    return true;
}

//尾插法
LinkList list_tailInsert(LinkList &l){
    int x;
    l = (LinkList)malloc(sizeof(LNode));
    LinkList s, r = l;
    scanf("%d", &x);
    while (x!=9999)
    {
        s = (LinkList)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        scanf("%d", &x);
    }
    r->next = NULL;
    return l;
}

//头插法
LinkList list_headInsert(LinkList &l){
    LinkList s;
    int x;
    l = (LinkList)malloc(sizeof(LNode));
    l->next = NULL;
    scanf("%d", &x);
    while (x!=9999)
    {
        s = (LinkList)malloc(sizeof(LNode));
        s->data = x;
        s->next = l->next;
        l->next = s;
        scanf("%d", &x);
    }
    return l;
}
void display(LinkList p) {
    LinkList temp = p;//将temp指针重新指向头结点
    //只要temp指针指向的结点的next不是Null，就执行输出语句。
    while (temp->next) {
        temp = temp->next;
        printf("%d ", temp->data);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    LinkList l;
    InitList(l);
    l = list_tailInsert(l);
    display(l);
    LinkList p;
    InitList(p);
    p = list_headInsert(p);
    display(p);
    return 0;
}
