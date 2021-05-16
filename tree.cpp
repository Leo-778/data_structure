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
int CountNodes(BiTree T);
int CountLeaves(BiTree T);
int CountKNodes(BiTree T, int k);
bool StructureCmp(BiTree T1, BiTree T2);
void Mirror(BiTree &T);
BiTree FindLCA(BiTree T, BiTree T1, BiTree T2);
int CountSonDis(BiTree T, BiTree T1);
int DistanceNodes(BiTree T, BiTree T1, BiTree T2);

int main(int argc, char const *argv[])
{
    BiTree root1 = nullptr;
    BiTree l, r;

    root1 = CreateBTree();//    ABDH##I##E##CF#J##G##
    int a;

    l = root1->lchild->lchild->rchild;
    r = root1->rchild->rchild;
    LevelOrder(root1);
    printf("\n");
    visit(root1);
    printf("\n");
    visit(l);
    printf("\n");
    visit(r);
    a = DistanceNodes(root1, r, l);
    printf("\n%d\n", a);
    BiTree b=FindLCA(root1,l,r);
    visit(b);
    return 0;
}

//访问节点打印字符
void visit(BiTree T){
    printf("%c ",T->data);
}

//访问节点打印数字
//  void visit(BiTree T){
//     printf("%d ",T->data);
//  }

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

//求树的结点个数
int CountNodes(BiTree T){
    if (T==nullptr)
        return 0;
    return CountNodes(T->lchild) + CountNodes(T->rchild)+1;
}

//求树的叶子结点的个数
int CountLeaves(BiTree T){
    if(T==nullptr)
        return 0;
    if(T->lchild==nullptr&&T->rchild==nullptr)
        return 1;
    return CountLeaves(T->rchild) + CountLeaves(T->lchild);
}

//求二叉树第k层的结点个数
int CountKNodes(BiTree T,int k){
    if(T==nullptr)
        return 0;
    if(k==1)
        return 1;
    return CountKNodes(T->lchild, k - 1) + CountKNodes(T->rchild, k - 1);
}

//判断两颗二叉树是否结构相同
bool StructureCmp(BiTree T1,BiTree T2){
    if(T1==nullptr&&T2==nullptr)
        return true;
    if(T1==nullptr||T2==nullptr)
        return false;
    return StructureCmp(T1->lchild, T2->lchild) && StructureCmp(T1->rchild, T2->rchild);
}

//求二叉树镜像
void Mirror (BiTree &T){
    if (T==nullptr)
        return;
    BiTree p;
    p = T->rchild;
    T->rchild = T->lchild;
    T->lchild = p;
    Mirror(T->lchild);
    Mirror(T->rchild);
}

//求两个节点的最低的公共祖先结点(LCA)
BiTree FindLCA(BiTree T,BiTree T1,BiTree T2){
    if (T==nullptr)
        return nullptr;
    if (T==T1||T==T2)
        return T;
    BiTree left = FindLCA(T->lchild, T1, T2);
    BiTree right = FindLCA(T->rchild, T1, T2);
    if (left != nullptr && right != nullptr)
        return T;
    return left ? left : right;
}

//求一个节点到他的子孙结点的距离
int CountSonDis(BiTree T,BiTree T1){
    if(T==nullptr)
        return -1;
    if(T==T1)
        return 0;
    int dis = CountSonDis(T->lchild, T1);
    if(dis==-1)
        dis = CountSonDis(T->rchild, T1);
    if(dis!=-1)
        return dis+1;
    return -1;
}

//求任意两节点距离
int DistanceNodes(BiTree T,BiTree T1,BiTree T2){
    BiTree p = FindLCA(T, T1, T2);
    int dis1 = CountSonDis(p, T1);
    int dis2 = CountSonDis(p, T2);
    return dis1 + dis2;
}