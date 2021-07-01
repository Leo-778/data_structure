#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
//给定一个二叉树，返回所有从根节点到叶子结点的路径

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

void binaryTreepath(Bitree t,vector<string> &path,vector<string> &result){
    if (t->lchild==nullptr && t->rchild)
    {
        
    }
    
}

int main(int argc, char const *argv[])
{
    Bitree root = nullptr;
    //PrintPostOrder(0, 0, 9);
    root = CreateBTree();//    ABDH##I##E##CF#J##G##
    //printf("%d", countNodes(root));
    return 0;
}