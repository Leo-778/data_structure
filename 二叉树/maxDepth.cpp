#include<stdio.h>
#include<algorithm>
using namespace std;

typedef struct BitNode{
    int key;
    struct BitNode *lchild, *rchild;
} BitNode, *Bitree;

int maxDepth(Bitree t){
    if(t==nullptr){
        return 0;
    }
    if (t->lchild ==NULL && t->rchild ==NULL)
    {
        return 1;
    }
    return max(maxDepth(t->lchild) + 1, maxDepth(t->rchild) + 1);
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
    printf("%d", maxDepth(root));
    return 0;
}