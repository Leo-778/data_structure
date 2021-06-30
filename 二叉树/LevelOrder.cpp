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
    q.front = nullptr;
    q.rear = NULL;
    return;
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
    return;
}

bool DeQueue(LinkQueue &q,Bitree &t){
    if (Isempty(q))
    {
        return false;
    }
    LNode p = q.front;
    t = p->val;
    q.front = p->next;
    if(q.rear==p){
        q.rear = NULL;
        q.front = NULL;
    }
    free(p);
    return true;
}

void visit(Bitree T){
    printf("%c ",T->key);
}

void LevelOrder(Bitree T){
    LinkQueue Q;
    Initqueue(Q);
    Bitree p;
    EnQueue(Q, T);
    while (!Isempty(Q))
    {
        DeQueue(Q,p);
        visit(p);
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }

}

//根据先序遍历构建二叉树
Bitree CreateBTree()
{
    Bitree bt = NULL;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        bt = new BitNode;
        bt->key = ch;
        bt->lchild = CreateBTree();
        bt->rchild = CreateBTree();
    }
    return bt;
}

int main(int argc, char const *argv[])
{
    Bitree root = nullptr;
    //PrintPostOrder(0, 0, 9);
    root = CreateBTree();//    ABDH##I##E##CF#J##G##
    LevelOrder(root);
    return 0;
}