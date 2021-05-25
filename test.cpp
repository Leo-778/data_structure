#include <stdio.h>
#include <stdlib.h>

//二叉排序树节点
typedef struct BSTNode{
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

//链式队列节点
typedef struct LinkNode
{
    BSTree data;
    struct LinkNode *next;
}LinkNode,* LNode;

//链式队列
typedef struct{
    LinkNode *front, *rear;
} LinkQueue;

void Creat_BST(BSTree &T, int str[], int n);
void order(BSTree t); //中序输出
int DeleteBST(BSTree &T, int key);


//插入操作（递归）
int BST_Inster(BSTree &T,int k){
    if (T==nullptr)
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->key = k;
        T->lchild = T->rchild = nullptr;
        return 1;
    }
    if(k==T->key)
        return 0;
    else if(k < T->key)
        return BST_Inster(T->lchild, k);
    else if(k > T->key)
        return BST_Inster(T->rchild, k);
}

//BST构造
void Creat_BST(BSTree &T,int str[],int n){
    T = nullptr;
    int i = 0;
    while (i < n)
    {
        BST_Inster(T, str[i]);
        i++;
    }
    return;
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
void EnQueue(LinkQueue &Q,BSTree t){
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
bool DeQueue(LinkQueue &Q,BSTree &t){
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

//二叉树层次遍历(不带头结点的链式队列)
void LevelOrder(BSTree T){
    LinkQueue Q;
    InitQueue(Q);
    BSTree p;
    EnQueue(Q, T);
    while (!IsEmpty(Q))
    {
        DeQueue(Q,p);
        printf("%d ", T->key);
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }

}

void order(BSTree t)//中序输出
{
    if(t == NULL){
        return ;
    }
    order(t->lchild);
    printf("%d ", t->key);
    order(t->rchild);
}

int main(int argc, char const *argv[])
{
    int a[5] = {3,4,2,5,9};
    BSTree T = NULL;
    Creat_BST(T, a, 5);
    LevelOrder(T);
    printf("\n");
    order(T);
    return 0;
}