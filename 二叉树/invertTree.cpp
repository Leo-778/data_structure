#include<stdio.h>
#include<algorithm>
using namespace std;

typedef struct BitNode{
    int key;
    struct BitNode *lchild, *rchild;
} BitNode, *Bitree;

void invertTree(Bitree &t){
    if (t==NULL)
    {
        return;
    }
    swap(t->lchild, t->rchild);
    invertTree(t->lchild);
    invertTree(t->rchild);
    return;
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
    invertTree(root);
    
    return 0;
}