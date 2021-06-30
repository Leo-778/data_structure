#include<stdio.h>
#include<algorithm>
using namespace std;
// 完全二叉树的节点个数

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

int countNodes(Bitree t){
    if (t==nullptr)
        return 0;
    return 1 + countNodes(t->rchild) + countNodes(t->lchild);
}

int main(int argc, char const *argv[])
{
    Bitree root = nullptr;
    //PrintPostOrder(0, 0, 9);
    root = CreateBTree();//    ABDH##I##E##CF#J##G##
    printf("%d", countNodes(root));
    return 0;
}