#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//二叉排序树

//二叉排序树节点
typedef struct BSTNode{
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

void Creat_BST(BSTree &T, int str[], int n);
void order(BSTree t); //中序输出
int DeleteBST(BSTree &T, int key);

int main(int argc, char const *argv[])
{
    int a[8] = {50,66,60,26,21,30,70,68};
    BSTree T = NULL;
    Creat_BST(T, a, 8);
    printf("中序遍历二叉排序树：\n");
    order(T);
    printf("\n");
    
    return 0;
}

//查找操作(非递归)
// BSTNode *BST_Search(BSTree T,int key){
//     while (T != nullptr)
//     {
//         if(T->key > key)
//             T = T->lchild;
//         if(T->key < key)
//             T = T->rchild;
//         if(T->key == key)
//             return T;
//     }
//     return nullptr;
// }


//查找操作(递归)
BSTNode *BST_Search(BSTree T,int key){
    if(T == nullptr)
        return nullptr;
    if(T->key == key)
        return T;
    else if(T->key > key)
        return BST_Search(T->lchild, key);
    else if(T->key < key)
        return BST_Search(T->rchild, key);
}

//插入操作（非递归）
// int BST_Inster(BSTree &T,int k){
    
//     BSTree p = (BSTree)malloc(sizeof(BSTNode));
//     p->key = k;
//     p->lchild = T->rchild = nullptr;
//     if(T==nullptr){
//         T = p;
//         return 1;
//     }
//     BSTree q = T;
//     BSTree pre;
//     while (q!=nullptr)
//     {
//         pre = q;
//         if (pre->key > k)
//             q = pre->lchild;
//         if(pre->key < k)
//             q = pre->rchild;
//     }
//     if(pre->key > k)
//         pre->lchild = p;
//     if(pre->key < k)
//         pre->rchild = p;
// }

//插入操作（递归）
int BST_Inster(BSTree &T,int k){
    if (T==nullptr)
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->key = k;
        T->lchild = T->rchild = nullptr;
        return 1;
    }
    if(k==T->key)
        return 0;
    else if(k < T->key)
        return BST_Inster(T->lchild, k);
    else if(k > T->key)
        return BST_Inster(T->rchild, k);
}

//BST构造
void Creat_BST(BSTree &T,int str[],int n){
    T = nullptr;
    int i = 0;
    while (i < n)
    {
        BST_Inster(T, str[i]);
        i++;
    }
    return;
}

//删除函数
int Delete(BSTree p)
{
    BSTree q, s;
    //情况 1，结点 p 本身为叶子结点，直接删除即可
    if(!p->lchild && !p->rchild){
        p = NULL;
    }
    else if(!p->lchild){ //左子树为空，只需用结点 p 的右子树根结点代替结点 p 即可；
        q = p;
        p = p->rchild;
        free(q);
    }
    else if(!p->rchild){//右子树为空，只需用结点 p 的左子树根结点代替结点 p 即可；
        q = p;
        p = p->lchild;//这里不是指针 *p 指向左子树，而是将左子树存储的结点的地址赋值给指针变量 p
        free(q);
    }
    else{//左右子树均不为空，采用第 2 种方式
        q = p;
        s = p->lchild;
        //遍历，找到结点 p 的直接前驱(左子树最右下的结点)
        while(s->rchild)
        {
            q = s;
            s = s->rchild;
        }
        //直接改变结点 p 的值
        p->key = s->key;
        //Delete(s);
        //判断结点 p 的左子树 s 是否有右子树，分为两种情况讨论
        if( q != p ){
            q->rchild = s->lchild;//若有，则在删除直接前驱结点的同时，令前驱的左孩子结点改为 q 指向结点的孩子结点
        }else{
            q->lchild = s->lchild;//否则，直接将左子树上移即可
        }
        free(s);
    }
    return 1;
}

int DeleteBST(BSTree &T, int key){
    if( !T){//不存在关键字等于key的数据元素
        return 0;
    }
    else
    {
        if( key == T->key ){
            Delete(T);
            return 1;
        }
        else if( key < T->key){
            //使用递归的方式
            return DeleteBST(T->lchild, key);
        }
        else{
            return DeleteBST(T->rchild, key);
        }
    }
}

void order(BSTree t)//中序输出
{
    if(t == NULL){
        return ;
    }
    order(t->lchild);
    printf("%d ", t->key);
    order(t->rchild);
}