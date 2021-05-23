#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 100

//线索二叉树结点
typedef struct ThreadNode{
    int data;
    struct ThreadNode *lchild, *rchild;
    int ltag=0, rtag=0;
}ThreadNode,*ThreadTree;

//链式队列节点
typedef struct LinkNode
{
    ThreadTree data;
    struct LinkNode *next;
}LinkNode,* LNode;

//链式队列
typedef struct{
    LinkNode *front, *rear;
} LinkQueue;

void InitQueue(LinkQueue &Q);
bool IsEmpty(LinkQueue Q);
bool DeQueue(LinkQueue &Q, ThreadTree &t);
void EnQueue(LinkQueue &Q, ThreadTree t);


ThreadTree CreateBTree();
void PreOrder(ThreadTree T);
void InOrder(ThreadTree T);
void PostOrder(ThreadTree T);
void visit(ThreadTree T);
int treeDepth(ThreadTree T);
void LevelOrder(ThreadTree T);
void LevelOrder2(ThreadTree T);
void CreatInThread(ThreadTree T);
void CreatPreThread(ThreadTree T);
void CreatPostThread(ThreadTree T);
ThreadTree CreateIntBTree();

ThreadTree pre=nullptr;

int main(int argc, char const *argv[])
{
    
    ThreadTree root = nullptr;//线索二叉树
   // ThreadTree l;
    //int a[MaxSize] = {1  2  3  4  -1  -1  5  -1  -1  6  -1  -1  7  8  -1  9  -1  -1  0  -1  -1};

    //PrintPostOrder(0, 0, 9);
    root = CreateIntBTree();//    ABDH##I##E##CF#J##G##    1 2 3 4 ##5##6##78#9##0##


    PreOrder(root);

    //printf("houji = %d ", root->lchild->rchild->data);
    return 0;
}

//访问节点打印字符
void visit(ThreadTree T){
    printf("%d ",T->data);
}

// 线索二叉树
// void visit(ThreadTree q){
//     if(q->lchild==nullptr){
//         q->lchild = pre;
//         q->ltag = 1;
//     }
//     if (pre!=nullptr&&pre->rchild==nullptr)
//     {
//         pre->rchild = q;
//         pre->rtag = 1;
//     }
//     pre = q;
// }

//先序遍历递归版
void PreOrder(ThreadTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

//中序遍历递归版
void InOrder(ThreadTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

//后序遍历递归版
void PostOrder(ThreadTree T){
    if(T!=NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

//求树的深度
int treeDepth(ThreadTree T){
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

//队列入队(不带头结点)
void EnQueue(LinkQueue &Q,ThreadTree t){
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
bool DeQueue(LinkQueue &Q,ThreadTree &t){
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

//根据先序遍历构建二叉树
ThreadTree CreateBTree()
{
    ThreadTree bt = NULL;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        bt = new ThreadNode;
        bt->data = ch;
        bt->lchild = CreateBTree();
        bt->rchild = CreateBTree();
    }
    return bt;
}

//二叉树层次遍历(不带头结点的链式队列)
void LevelOrder(ThreadTree T){
    LinkQueue Q;
    InitQueue(Q);
    ThreadTree p;
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
void LevelOrder2(ThreadTree T){
    LinkQueue Q;
    InitQueue(Q);
    ThreadTree p;
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

//中序先线索化
void CreatInThread(ThreadTree T){
    pre = nullptr;
    if(T!=nullptr){
        InOrder(T);
        if (pre->rchild==nullptr)
        {
            pre->rtag = 1;
        }
        
    }
}

//先序先线索化
void CreatPreThread(ThreadTree T){
    pre = nullptr;
    if(T!=nullptr){
        PreOrder(T);
        if (pre->rchild==nullptr)
        {
            pre->rtag = 1;
        }
        
    }
}

//后序先线索化
void CreatPostThread(ThreadTree T){
    pre = nullptr;
    if(T!=nullptr){
        PostOrder(T);
        if (pre->rchild==nullptr)
        {
            pre->rtag = 1;
        }
        
    }
}

//根据先序遍历构建二叉树
ThreadTree CreateIntBTree()
{
    ThreadTree bt = NULL;
    int ch;
    scanf("%d ", &ch);
    if (ch != -1)
    {
        bt = new ThreadNode;
        bt->data = ch;
        bt->lchild = CreateBTree();
        bt->rchild = CreateBTree();
    }
    return bt;
}

//找到以P为根的子树中，第一个被中序遍历的节点
ThreadNode *Firstnode(ThreadNode *p){
    //循环找到最坐下节点（不一定是叶结点）
    while (p->ltag==0)
        p = p->lchild;
    return p;
}
//在中序线索二叉树中找到节点p的后继节点
ThreadNode *Nextnode(ThreadNode *p){
    //右子树中最左下节点
    if(p->rtag==0)
        return Firstnode(p->rchild);
    else
        return p->rchild;//rtag==1直接返回搜索
}
//对中序线索二叉树进行中序遍历（利用线索实现的非递归算法）
void Inorder(ThreadNode *T){
    for (ThreadNode *p = Firstnode(T); p != nullptr;p=Nextnode(p))
        visit(p);
}


//中序前驱
//找到以P为根的子树中，第一个被中序遍历的节点
ThreadNode *Lastnode(ThreadNode *p){
    //循环找到最坐下节点（不一定是叶结点）
    while (p->ltag==0)
        p = p->lchild;
    return p;
}
//在中序线索二叉树中找到节点p的前驱节点
ThreadNode *Prenode(ThreadNode *p){
    //右子树中最左下节点
    if(p->ltag==0)
        return Lastnode(p->lchild);
    else
        return p->lchild;//ltag==1直接返回搜索
}
//对中序线索二叉树进行中序遍历（利用线索实现的非递归算法）
void Inorder(ThreadNode *T){
    for (ThreadNode *p = Lastnode(T); p != nullptr;p=Prenode(p))
        visit(p);
}