#include<stdio.h>
#include<stdlib.h>
//双链表基本操作

typedef int ElemType;

typedef struct DNode               //定义单链表结点类型
{
    ElemType data;                //每个节，点存放一个数据元素
    struct DNode *next,*prior;           //指针指向下一个节点
} DNode, *DLinkList;


//初始化双链表
bool InitDLinkList(DLinkList &L){
    L = (DNode *) malloc(sizeof(DNode)); //分配一一个头结点
    if (L==NULL)          //内存不足，分配失败
        return false;
    L->prior = NULL;      //头结点的prior 永远指向NULL
    L->next = NULL;       //头结点之后暂时还没有节点
    return true ;
}

//在p结点之后插入s结点
bool InsertNextDNode(DNode *p, DNode *s)
{
    if (p==NULL || s==NULL) //非法参数
        return false;
    s->next = p ->next;
    if (p->next != NULL)//如果p结点有后继结点
        p->next->prior = s;
    s->prior=p;
    p->next=s;
    return true;
}

//删除结点的函数，data为要删除结点的数据域的值
bool delDNode(DLinkList &head, int data) {
    DNode * temp = head;
    //遍历链表
    while (temp) {
        //判断当前结点中数据域和data是否相等，若相等，摘除该结点
        if (temp->data == data) {
            temp->prior->next = temp->next;
            temp->next->prior = temp->prior;
            free(temp);
            return true;
        }
        temp = temp->next;
    }
    printf("链表中无该数据元素\n");
    return false;
}

//查找（查）head为原双链表，elem表示被查找元素
int selectElem(DLinkList head, int elem) {
    //新建一个指针t，初始化为头指针 head
    DLinkList t = head;
    int i = 1;
    while (t) {
        if (t->data == elem) {
            return i;
        }
        i++;
        t = t->next;
    }
    //程序执行至此处，表示查找失败
    return -1;
}

//修改（改），其中，i 表示更改结点在双链表中的位置，x 为新数据的值
bool amendElem(DLinkList &p, int i, int x) {
    int j = 0;
    DLinkList temp = p;
    //遍历到被删除结点
    for (j = 1; j < i; j++) {
        temp = temp->next;
        if (temp == NULL) {
            printf("更改位置有误！\n");
            return false;
        }
    }
    if (temp) {
        temp->data = x;
    }
    return true;
}

//输出链表的功能函数
void display(DLinkList head) {
    DLinkList temp = head;
    while (temp) {
        if (temp->next == NULL) {
            printf("%d\n", temp->data);
        }
        else {
            printf("%d->", temp->data);
        }
        temp = temp->next;
    }
}

DLinkList initLine(DLinkList head) {
    int i = 0;
    DLinkList list = NULL;
    head = (DLinkList)malloc(sizeof(DNode));
    head->prior = NULL;
    head->next = NULL;
    head->data = 1;
    list = head;
    for (i = 2; i <= 3; i++) {
        DLinkList body = (DLinkList)malloc(sizeof(DNode));
        body->prior = NULL;
        body->next = NULL;
        body->data = i;
        list->next = body;
        body->prior = list;
        list = list->next;
    }
    return head;
}


int main() {
    DLinkList head = NULL;
    //创建双链表
    printf("初始链表为：\n");
    head = initLine(head);
    display(head);
    //在表中第 3 的位置插入元素 7
    printf("在头节点后插入新节点data= 7：\n");
    DLinkList L = (DNode *)malloc(sizeof(DNode));
    L->data = 7;
    InsertNextDNode(head, L);
    display(head);
    //表中删除元素 2
    printf("删除元素 2：\n");
    delDNode(head, 2);
    display(head);
    printf("元素 3 的位置是：%d\n", selectElem(head, 3));
    //表中第 3 个节点中的数据改为存储 6
    printf("将第 3 个节点存储的数据改为 6：\n");
    amendElem(head, 3, 6);
    display(head);
    return 0;
}