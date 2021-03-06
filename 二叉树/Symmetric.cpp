#include<stdio.h>
#include<algorithm>
using namespace std;
//判断二叉树是否对称

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

bool compare(Bitree p, Bitree q){
    if (p==nullptr&&q==nullptr)
        return true;
    if (q!=nullptr&&p==nullptr)
        return false;
    if (q==nullptr&&p!=nullptr)
        return false;
    if(p->key != q->key)
        return false;
    return compare(p->rchild, q->lchild) && compare(p->lchild, q->rchild);
}

bool isSymmetric(Bitree t){
    if (t==nullptr)
    {
        return true;
    }
    return compare(t->lchild, t->rchild);
}

int main(int argc, char const *argv[])
{
    Bitree root = nullptr;
    //PrintPostOrder(0, 0, 9);
    root = CreateBTree();//    ABDH##I##E##CF#J##G##
    printf("%d", compare(root->rchild, root->lchild));
    return 0;
}