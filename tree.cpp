#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//树的基本操作
#define MaxSize 100

//二叉树的结点（链式存储）
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
    struct BiTNode *parent;
}BiTNode,* BiTree;

//线索二叉树结点
typedef struct ThreadNode{
    int data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
}ThreadNode,*ThreadTree;

//链式队列节点
typedef struct LinkNode
{
    BiTree data;
    struct LinkNode *next;
}LinkNode,* LNode;

//链式队列
typedef struct{
    LinkNode *front, *rear;
} LinkQueue;

void InitQueue(LinkQueue &Q);
bool IsEmpty(LinkQueue Q);
bool DeQueue(LinkQueue &Q, BiTree &t);
void EnQueue(LinkQueue &Q, BiTree t);

BiTree CreateBTree();
void PreOrder(BiTree T);
void InOrder(BiTree T);
void PostOrder(BiTree T);
void visit(BiTree T);
int treeDepth(BiTree T);
void LevelOrder(BiTree T);

int main(int argc, char const *argv[])
{
    BiTree root = NULL;

    // int a[10] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

    // root = (BiTree)malloc(sizeof(BiTNode));
    // root->data = {1};
    // root->lchild = NULL;
    // root->rchild = NULL;

    // BiTNode *p1 = (BiTree)malloc(sizeof(BiTNode));
    // p1->data = {3};
    // p1->lchild = NULL;
    // p1->rchild = NULL;
    // root->lchild = p1;

    // BiTNode *p2 = (BiTree)malloc(sizeof(BiTNode));
    // p2->data = {5};
    // p2->lchild = NULL;
    // p2->rchild = NULL;
    // root->rchild = p2;

    // BiTNode *p3 = (BiTree)malloc(sizeof(BiTNode));
    // p3->data = {4};
    // p3->lchild = NULL;
    // p3->rchild = NULL;
    // p1->rchild = p3;

    root = CreateBTree();

    LevelOrder(root);
    //printf("%d", treeDepth(root));
    //visit(root);
    return 0;
}

//访问节点打印字符
void visit(BiTree T){
    printf("%c ",T->data);
}
//访问节点打印字符
// void visit(BiTree T){

// }

//先序遍历
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

//中序遍历
void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

//后序遍历
void PostOrder(BiTree T){
    if(T!=NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

//求树的深度
int treeDepth(BiTree T){
    if(T == NULL){
        return 0;
    }
    else{
        int l = treeDepth(T->lchild);
        int r = treeDepth(T->rchild);
        return l > r ? l + 1 : r + 1;
    }
}

//初始化队列(不带头结点)
void InitQueue(LinkQueue &Q){
    Q.front = NULL;
    Q.rear = NULL;
    return;
}

//判断队列是否为空(不带头结点)
bool IsEmpty(LinkQueue Q){
    if(Q.front==NULL){
        return true;
    }
    else
        return false;
}

//入队(不带头结点)
void EnQueue(LinkQueue &Q,BiTree t){
    LNode s = (LNode)malloc(sizeof(LinkNode));
    s->data = t;
    s->next = NULL;
    if(Q.front==NULL){
        Q.front = s;
        Q.rear = s;
    }   
    else{
        Q.rear->next = s;
        Q.rear = s;
    }
    return;
}

//出队(不带头结点)
bool DeQueue(LinkQueue &Q,BiTree &t){
    if(Q.front==NULL){
        return false;
    }
    LinkNode *p = Q.front;
    t = p->data;
    Q.front = p->next;
    if(Q.rear==p){
        Q.rear = NULL;
        Q.front = NULL;
    }
    free(p);
    return true;
}

//二叉树层次遍历(不带头结点的链式队列)
void LevelOrder(BiTree T){
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while (!IsEmpty(Q))
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
BiTree CreateBTree()
{
    BiTree bt = NULL;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        bt = new BiTNode;
        bt->data = ch;
        bt->lchild = CreateBTree();
        bt->rchild = CreateBTree();
    }
    return bt;
}