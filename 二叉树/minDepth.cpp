#include<stdio.h>
#include<algorithm>
using namespace std;

typedef struct BitNode{
    int key;
    struct BitNode *lchild, *rchild;
} BitNode, *Bitree;

int minDepth(Bitree t){
    if(t==nullptr){
        return 0;
    }
    if(t->lchild==NULL && t->rchild!=NULL){
        return 1 + minDepth(t->rchild);
    }
    if (t->rchild==NULL && t->lchild !=NULL)
    {
        return 1 + minDepth(t->lchild);
    }
    return 1 + min(minDepth(t->lchild), minDepth(t->rchild));
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
    printf("%d", minDepth(root));
    return 0;
}