#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//树的基本操作
#define MaxSize 100

//二叉树的结点（链式存储）
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild,*rchild;
    struct BiTNode *parent;
}BiTNode,* BiTree;

//链式队列节点
typedef struct LinkNode
{
    BiTree data;
    struct LinkNode *next;
}LinkNode;

typedef struct{
    LinkNode *front, *rear;
} LinkQueue;

int treeDepth(BiTree T);

int main(int argc, char const *argv[])
{
    BiTree root = NULL;

    root = (BiTree)malloc(sizeof(BiTNode));
    root->data = {1};
    root->lchild = NULL;
    root->rchild = NULL;

    BiTNode *p = (BiTree)malloc(sizeof(BiTNode));
    p->data = {2};
    p->lchild = NULL;
    p->rchild = NULL;
    root->lchild = p;

    printf("%d", treeDepth(root));

    return 0;
}

//访问节点打印字符
void visit(BiTree T){
    printf("%c",T->data);
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

//初始化队列


//二叉树层次遍历
void LevelOrder(BiTree T){
    LinkQueue Q;

}