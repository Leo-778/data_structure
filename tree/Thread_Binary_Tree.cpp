#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

ThreadTree pre=nullptr;

int main(int argc, char const *argv[])
{
    
    ThreadTree root = nullptr;//线索二叉树
    ThreadTree l;
    
    //PrintPostOrder(0, 0, 9);
    root = CreateBTree();//    ABDH##I##E##CF#J##G##

    l = root->lchild->lchild->rchild;

    InOrder(root);

    printf("houji = %c ", l->lchild->lchild->data);
    return 0;
}

//访问节点打印字符
// void visit(ThreadTree T){
//     printf("%c ",T->data);
// }

//线索二叉树
void visit(ThreadTree q){
    if(q->lchild==nullptr){
        q->lchild = pre;
        q->ltag = 1;
    }
    if (pre!=nullptr&&pre->rchild==nullptr)
    {
        pre->rchild = q;
        pre->rtag = 1;
    }
    pre = q;
}

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