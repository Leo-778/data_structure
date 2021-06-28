#include<stdio.h>

typedef struct BitNode
{
    int key;
    struct BitNode *lchild, *rchild;
}BitNode,*Bitree;

void visit(Bitree t){

}

void PreOrder(Bitree t){
    if (t!=nullptr)
    {
        visit(t);
        PreOrder(t->lchild);
        PreOrder(t->rchild);
    }
}
