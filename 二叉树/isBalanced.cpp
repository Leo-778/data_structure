#include<stdio.h>
#include<algorithm>
using namespace std;
//给定一个二叉树，判断是否是平衡二叉树

typedef struct BitNode{
    int key;
    struct BitNode *lchild, *rchild;
} BitNode, *Bitree;
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

int getDepth(Bitree t){
    if (t==nullptr)
        return 0;
    return 1 + max(getDepth(t->lchild),getDepth(t->rchild));
}

bool isBalanced(Bitree t){
    if (t==nullptr)
        return true;
    if((getDepth(t->lchild) - getDepth(t->rchild)) > 1)
        return false;
    return isBalanced(t->rchild) && isBalanced(t->lchild);
}

// bool ret = true;
// int getDepth(Bitree t){
//     if (t==nullptr)
//         return 0;
//     int l=getDepth(t->lchild);
//     int r=getDepth(t->rchild);
//     if(abs(l-r)>1)
//         ret = false;
//     return 1 + max(getDepth(t->lchild),getDepth(t->rchild));
// }
// bool isbalance(Bitree t){
//     getDepth(t);
//     return ret;
// }


int main(int argc, char const *argv[])
{
    Bitree root = nullptr;
    //PrintPostOrder(0, 0, 9);
    root = CreateBTree();//    ABDH##I##E##CF#J##G##
    printf("%d", isBalanced(root));
    return 0;
}