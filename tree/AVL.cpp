#include <stdio.h>
#include <stdlib.h>


typedef int ElemType;
//定义二叉排序树
typedef struct AVLNode{
    ElemType key;
    int blance;//balance flag
    struct AVLNode *lchild,*rchild;
}AVLNode,*AVLTree;


//求树的深度
int treeDepth(AVLTree T)
{
    if(T == NULL){
        return 0;
    }
    else{
        int l = treeDepth(T->lchild);
        int r = treeDepth(T->rchild);
        return l > r ? l + 1 : r + 1;
    }
}

//更新平衡因子
int RBlance(AVLTree t){
    return treeDepth(t->lchild) - treeDepth(t->rchild);
}

//LL型，进行右旋操作，nod为最小不平衡子树的根节点
AVLTree R_Rotate(AVLTree nod)
{
    AVLTree temp;
    temp = nod->lchild; //临时保存nod的左子树

    nod->lchild = nod->lchild->rchild;//将node的左子树的右子树 变成 node的左子树
    temp->rchild = nod;               //node 变成 temp的右子树

    nod->blance = RBlance(nod); //更新平衡因子
    temp->blance = RBlance(temp);

    return temp;
}

//RR型，进行左旋操作，nod为最小不平衡子树的根节点
AVLTree L_Rotate(AVLTree nod){
    AVLTree temp;
    temp = nod->rchild; //临时保存nod的右子树

    nod->rchild = nod->rchild->lchild;//将node的右子树的左子树 变成 node的右子树
    temp->lchild = nod;               //node 变成 temp的左子树

    nod->blance = RBlance(nod); //更新平衡因子
    temp->blance = RBlance(temp);

    return  temp;
}

//LR型，先左旋再右旋
AVLTree L_R_Rotate(AVLTree nod){
    nod->lchild = L_Rotate(nod->lchild);
    nod = R_Rotate(nod);

    return nod;
}

//RL型，先右旋再左旋
AVLTree R_L_Rotate(AVLTree nod)
{
    nod->rchild = R_Rotate(nod->rchild);
    nod = L_Rotate(nod);

    return nod;
}

//插入新节点
AVLTree AVLInsert(AVLTree &T,int k){
    if (T==nullptr)
    {
        T = (AVLTree)malloc(sizeof(AVLNode));
        T->key = k;
        T->lchild = T->rchild = nullptr;
        T->blance = RBlance(T);
    }

    if (k == T->key)
    {
        printf("不允许插入重复值");
        exit(0);
    }
    if (T->key > k){
        T->lchild = AVLInsert(T->lchild, k);
        //T->blance = RBlance(T);
        if(T->blance > 1)   //在左孩子上插入，接下来要判断是 LL 还是 LR
        {
            // if (k < T->lchild->key) //LL型，进行右旋
            //     T = R_Rotate(T);
            // else
            //     T = R_L_Rotate(T);//LR型，进行右旋+左旋
        }
        //return T;
    }

    if (T->key < k){
        T->lchild = AVLInsert(T->rchild, k);
        //T->blance = RBlance(T);
        if(T->blance < -1)   //在右孩子上插入，接下来要判断是 RR 还是 RL
        {
            // if (k > T->rchild->key) //RR型，进行右旋
            //     T = L_Rotate(T);
            // else
            //     T = L_R_Rotate(T);//RL型，进行左旋+右旋
        }
        //return T;
    }
    T->blance = RBlance(T);
    return T;
}

/* 前序遍历AVL树，并打印节点高度 */
void PreOrder_Traverse(AVLTree nod)
{
    if (nod != NULL)
    {
        //printf("data = %d blance = %d\n", nod->key, nod->blance);
        printf("%d ", nod->key);
        PreOrder_Traverse(nod->lchild);
        PreOrder_Traverse(nod->rchild);
    }
}

void InOrder(AVLTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        printf("%d ", T->key);
        InOrder(T->rchild);
    }
}

int main(int argc, char const *argv[])
{
    int a[8] = {50,66,60,26,21,30,70,68};
    AVLTree T = NULL;
    for (int i = 0; i < 8; i++)
    {
        T=AVLInsert(T, a[i]);
    }
    PreOrder_Traverse(T);
    printf("\n");
    InOrder(T);
    printf("\n 深度 = %d ", treeDepth(T->lchild));
    return 0;
}
