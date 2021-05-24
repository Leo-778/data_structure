#include <stdio.h>
#include <stdlib.h>
//分别定义平衡因子数
#define LH +1
#define EH  0
#define RH -1
typedef int ElemType;
//定义平衡二叉树
typedef struct AVLNode{
    ElemType key;
    int blance;//balance flag
    struct AVLNode *lchild,*rchild;
} AVTNode, *AVLTree;