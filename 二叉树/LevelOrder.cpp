#include<stdio.h>
#include <stdlib.h>

const int maxn = 10;

typedef struct BitNode{
    int key;
    struct BitNode *lchild, *rchild;
} BitNode, *Bitree;

typedef struct LinkNode
{
    Bitree val;
    struct LinkNode *next;
}LinkNode,*LNode;

typedef struct 
{
    LinkNode *front,*rear;
}LinkQueue;

void Initqueue(LinkQueue &q){
    q.front = q.rear = (LinkNode *)malloc(sizeof(LinkNode));
    q.rear->next = NULL;
}

bool Isempty(LinkQueue q){
    if (q.front==NULL)
    {
        return true;
    }
    else
        return false;
}

void EnQueue(LinkQueue &q,Bitree t){
    LNode s = (LNode)malloc(sizeof(LinkNode));
    s->val = t;
    s->next = NULL;
    if (q.front==NULL)
    {
        q.front = s;
        q.rear = s;
    }
    else{
        q.rear->next = s;
        q.rear = s;
    }
}

Bitree DeQueue(LinkQueue &q){
    if (Isempty(q))
    {
        return NULL;
    }
    LNode p = q.front;
    Bitree t = p->val;
    q.front = p->next;
    if(q.rear==p){
        q.rear = NULL;
        q.front = NULL;
    }
    free(p);
    return t;
}

void visit(Bitree T){
    printf("%c ",T->key);
}

void LevelOrder(Bitree t){
    if (t==NULL)
    {
        return;
    }
    LinkQueue q;
    Initqueue(q);
    Bitree p;
    EnQueue(q, p);
    while (!Isempty(q))
    {
        p=DeQueue(q);
        visit(p);
        if (p->lchild!=NULL)
        {
            EnQueue(q,p->lchild);
        }
        if (p->rchild!=NULL)
        {
            EnQueue(q, p->rchild);
        }
    }
}