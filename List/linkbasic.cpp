#include<stdio.h>
#include<stdlib.h>
//链表基本操作

typedef int ElemType;

typedef struct LNode               //定义单链表结点类型
{
    ElemType data;                //每个节，点存放一个数据元素
    struct LNode *next;           //指针指向下一个节点
} LNode, *LinkList;

/*********************************不带头结点***********************************/
bool InitList(LinkList &l){
    l = NULL;    //空表，暂时还没有任何结点
    return true;
}

bool ListInsert(LinkList &L,int i, ElemType e){
    if(i<1)
        return false;
    if(i==1){ //插入第1个结点的操作与 其他结点操作不同
        LNode *s = (LNode * )malloc( sizeof(LNode));
        s->data = e;
        s->next=L;
        L=s;          // 头指针指向新结点
        return true;
    }
    LNode *p;          // 指针p指向当前扫描到的结点
    int j = 1;         // 当前p指向的是第几个结点
    p = L;             //p指向第1个结点(注意:不是头结点)
    while (p!=NULL && j<i-1) { //循环找到第 1-1个结点
        p = p -> next;
        j++;
    }
    if(p==NULL)        //i值不合法
        return false;
    LNode *s = (LNode * )malloc(sizeof(LNode));
    s->data = e;
    s->next=p->next ;
    p->next=s;
    return true; //插入成功
}

bool ListDelete(LinkList &L, int i, ElemType &e){
    if(i<1)
        return false;
    if(i==1){
        L = NULL;
    }
    LNode *p;       //指针p指向当前扫描到的结点
    int j = 1;      //当前p指向的是第几个结点
    p = L;          //p指向头指针
    while (p!=NULL && j<i-1) { //循环找到第 i-1个结点
        p = p ->next;
        j++;
    }
    if(p==NULL)//i值不合法
        return false;
    LNode *q = p->next; //令q指向被删除结点
    e = q->data;        //用e返回元素的值
    p->next = q->next;  //将*q结点从链中“断开”
    free(q);            //释放结点的存储空间
    return true;        //删除成功
}


/*********************************不带头结点***********************************/

/**********************************带头结点************************************/
bool InitList(LinkList &l){
    l = (LNode *)malloc(sizeof(LNode));//分配头结点
    if (l==NULL)       //内存不足，分配失败
        return false;
    l->next = NULL;    //头结点之后暂时还没有节点
    return true;
}

//在第i个位置插插入元素e (带头结点)
bool ListInsert(LinkList &L, int i, ElemType e){
    if(i<1)
        return false;
    LNode *p;    //指针p指向当 前扫描到的结点
    int j = 0;   // 当前p指向的是第几个结点
    p = L;       // L指向头结点，头结点是第0个结点(不存数据)
    while(p!=NULL && j<i-1) { //循环找到第 i-1个结点
        p=p->next;
        j++; 
    }
    if(p==NULL)   //i值不合法
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next=s;               //将结点s连到p之后|
    return true;             //插入成功
}
//删除表L中第i个位置的元素，并用e返回删除元素的值。
bool ListDelete(LinkList &L, int i, ElemType &e){
    if(i<1)
        return false;
    LNode *p;       //指针p指向当前扫描到的结点
    int j = 0;      // 当前p指向的是第几个结点
    p = L;          //L指向头结点，头结点是第0个结点(不存数据)
    while (p!=NULL && j<i-1) { //循环找到第 1-1个结点
        p = p ->next;
        j++;
    }
    if(p==NULL)//i值不合法
        return false;
    if (p -> next == NULL) //第1-1个结点之后已无其他结点
        return false;
    LNode *q = p->next; //令q指向被删除结点
    e = q->data;        //用e返回元素的值
    p->next = q->next;  //将*q结点从链中“断开”
    free(q);            //释放结点的存储空间
    return true;        //删除成功
}

/**********************************带头结点************************************/

//前插操作     在p结点之前插入元素e
bool InsertPriorNode (LNode *p, ElemType e){
    if (p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s==NULL)           //内存分配失败
        return false;
    s->next = p->next;
    p->next = s;          //新结点s连到p之后
    s->data = p->data;    //将p中元素复制到s中
    p->data = e;          //p中元素覆盖为e
    return true;
}
//后插操作  在p结点之后插入元素e
bool InsertNextNode (LNode *p,ElemType e){
    if (p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s==NULL)       //内存分配失败
        return false;
    s->data = e;     //用结点s保存数据元素e
    s->next=p->next;
    p->next = s;     //将结点s连到p之后
    return true;
}

//删除指定结点p
bool DeleteNode (LNode *p) {
    if (p==NULL)
        return false;
    LNode *q = p->next;       //令q指向*p的后继结点
    p->data = p->next->data;  //和后继结点交换数据域
    p->next = q->next;        //将*q结点从链中“断开”
    free(q);                  //释放后继结点的存储空间
    return true;
}

//按位查找，返回第i个元素(带头结点)
LNode * GetElem(LinkList L, int i){
    if(i<0)
        return NULL;
    LNode *p;// 指针p指向当前扫描到的结点 int j = 0;
    int j = 0; //当前p指向的是第几个结点
    p = L;     //L指向头结点，头结点是第0个结点(不存数据)
    while (p!=NULL && j<i) { //循环找到第 i个结点
        p=p->next;
        j++;
    }
    return p;
}

//按值查找，找到数据域==e的结点
LNode * LocateElem(LinkList L,ElemType e) {
    LNode *p = L ->next; //从第1个结点开始查找数据域为e的结点
    while (p != NULL && p->data != e)
        p = p->next;
    return p; //找到后返回该结 点指针， 否则返回NULL
}

//求表的长度
int Length(LinkList L){
    int len = 0; //统计表长
    LNode *p = L;
    while (p->next != NULL){
        p = p->next;
        len++;
    }
    return len;
}
