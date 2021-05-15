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

//定义栈
typedef struct{
    BiTree data[MaxSize];
    int top;
} SqStack;

void InitQueue(LinkQueue &Q);
bool IsEmpty(LinkQueue Q);
bool DeQueue(LinkQueue &Q, BiTree &t);
void EnQueue(LinkQueue &Q, BiTree t);

void InitStack(SqStack &S);
bool StackIsEmpty(SqStack &S);
bool Push(SqStack &S, BiTree x);
bool Pop(SqStack &S, BiTree &x);

BiTree CreateBTree();
void PreOrder(BiTree T);
void InOrder(BiTree T);
void PostOrder(BiTree T);
void visit(BiTree T);
int treeDepth(BiTree T);
void LevelOrder(BiTree T);
void LevelOrder2(BiTree T);
void PreOrderNonRec(BiTree T);
void InOrderNonRec(BiTree &T);
void PostOrderNonRec(BiTree &T);

int main(int argc, char const *argv[])
{
    BiTree root = nullptr;

    root = CreateBTree();//ABDH##I##E##CF#J##G##

    LevelOrder(root);
    printf("\n");
    LevelOrder2(root);
    printf("\n");
    printf("%d\n", treeDepth(root));
    PostOrderNonRec(root);
    printf("\n");
    PostOrder(root);
    return 0;
}

//访问节点打印字符
void visit(BiTree T){
    printf("%c ",T->data);
}
//访问节点打印字符
// void visit(BiTree T){

// }

//先序遍历递归版
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

//中序遍历递归版
void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

//后序遍历递归版
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

/********************************队列操作**************************************/
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

//队列入队(不带头结点)
void EnQueue(LinkQueue &Q,BiTree t){
    LNode s = (LNode)malloc(sizeof(LinkNode));
    s->data = t;
    s->next = nullptr;
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

//队列出队(不带头结点)
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

/********************************队列操作**************************************/

/********************************栈操作***************************************/
//初始化栈
void InitStack(SqStack &S){
    S.top = -1;
}

//判断栈是否为空
bool StackIsEmpty(SqStack &S){
    if(S.top==-1)
        return true;
    else
        return false;
}

//进栈
bool Push(SqStack &S,BiTree x){
    if (S.top==MaxSize-1)
        return false;
    S.top++;
    S.data[S.top] = x;
    return true;
}

//出栈
bool Pop(SqStack &S,BiTree &x){
    if(S.top==-1)
        return false;
    x = S.data[S.top];
    S.top--;
    return true;
}

/********************************栈操作***************************************/

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

//二叉树层次遍历(自上而下，从右到左)
void LevelOrder2(BiTree T){
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while (!IsEmpty(Q))
    {
        DeQueue(Q,p);
        visit(p);
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
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

//先遍历非递归版
void PreOrderNonRec(BiTree T){
    if (T==nullptr)
        return;
    SqStack S;
    BiTree p;
    p = T;
    InitStack(S);
    while (p!=nullptr || !StackIsEmpty(S))
    {
        while (p!=nullptr)
        {
            visit(p);
            Push(S, p);
            p = p->lchild;
        }
        if (!StackIsEmpty(S))
        {
            Pop(S, p);
            p = p->rchild;
        }
    }
}

//中序遍历非递归版
void InOrderNonRec(BiTree &T){
    if (T==nullptr)
        return;
    SqStack S;
    InitStack(S);
    BiTree p;
    p = T;
    while (p!=nullptr || !StackIsEmpty(S))
    {
        while (p!=nullptr)
        {
            Push(S, p);
            p = p->lchild;
        }
        if(!StackIsEmpty(S)){
            Pop(S, p);
            visit(p);
            p = p->rchild;
        }
    }
    return;
}

//后序遍历非递归版(就是从右往左的先序遍历)
void PostOrderNonRec(BiTree &T){
    if (T==nullptr)
        return;
    SqStack S1,S2;
    InitStack(S1);
    InitStack(S2);
    BiTree p;
    p = T;
    while(p!=nullptr || !StackIsEmpty(S1)){
        while (p!=nullptr)
        {
            Push(S1, p);
            Push(S2, p);
            p = p->rchild;
        }
        if (!StackIsEmpty(S1))
        {
            Pop(S1, p);
            p = p->lchild;
        }
    }
    while (!StackIsEmpty(S2))
    {
        Pop(S2, p);
        visit(p);
    }
}