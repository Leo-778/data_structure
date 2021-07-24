#include<stdio.h>
#include<stdlib.h>
const int MaxSize = 100;
//定义二叉树
typedef struct BitNode
{
    int key;
    struct BitNode *lchild, *rchild;
}BitNode,*Bitree;
//定义栈
typedef struct 
{
    Bitree elem[MaxSize];
    int top=-1;
}Stack;

//进栈
bool push(Stack &s,Bitree t){
    if (s.top==MaxSize-1)
        return false;
    s.top++;
    s.elem[s.top] = t;
    return true;
}

//出栈
Bitree pop(Stack &s){
    if(s.top==-1)
        return nullptr;
    return s.elem[s.top--];
}

//判断栈空
bool Isempty(Stack s){
    if (s.top==-1)
    {
        return true;
    }
    else
        return false;
}
//访问
void visit(Bitree t){
    printf("%c", t->key);
}
//先序遍历
void PreOrder(Bitree t){
    if (t!=nullptr)
    {
        visit(t);
        PreOrder(t->lchild);
        PreOrder(t->rchild);
    }
}
//非递归先序遍历
void nPreOrder(Bitree t){
    if (t==nullptr)
    {
        return;
    }
    Stack s;
    Bitree p=t;
    while(p!=nullptr ||!Isempty(s)){
        while(p!=nullptr){
            visit(p);
            push(s, p);
            p = p->lchild;
        }
        if(!Isempty(s)){
            p = pop(s)->rchild;
        }
    }
}
//中序遍历
void InOrder(Bitree t){
    if (t!=nullptr)
    {
        InOrder(t->lchild);
        visit(t);
        InOrder(t->rchild);
    }
}
//非递归中序遍历
void nInOrder(Bitree t){
    Stack s;
    Bitree p = t;
    while(p!=nullptr || !Isempty(s)){
        while(p!=NULL){
            push(s, p);
            p = p->lchild;
        }
        if (!Isempty(s))
        {
            p = pop(s);
            visit(p);
            p=p->rchild;
        }
        
    }
}

void PostOrder(Bitree t){
    if (t!=nullptr)
    {
        PostOrder(t->lchild);
        PostOrder(t->rchild);
        visit(t);
    }
}

void nPostOrder(Bitree t){
    Stack s1;
    Stack s2;
    Bitree p = t;
    while (p||!Isempty(s1)) {
        if (p!=nullptr)
        {
            push(s1, p);
            push(s2, p);
            p = p->rchild;
        }else{
            p = pop(s1);
            p = p->lchild;
        }
    }
    while (!Isempty(s2))
    {
        visit(pop(s2));
    }
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
int i, llen, rlen;
Bitree preincreat(int *a,int *b,int l1,int h1,int l2,int h2){
    //l1,h1是前序的第一和最后一个节点的下标。l2,h2是中序的第一和最后一个节点的下标。
    //初始调用时，l1=l2=1,h1=h2=n
    Bitree root = (BitNode *)malloc(sizeof(BitNode)); 
    root->key = a[l1];                                
    for (i = l2; b[i] != root->key ; i++);            //根节点在中序序列的划分
    llen = i - l2;                                    //左子树长度
    rlen = h2 - i;                                    //右子树长度
    if(llen)//递归建立左子树
        root->lchild = preincreat(a, b, l1 + 1, l1 + llen, l2, l2 + llen - 1);
    else
        root->lchild = NULL;
    if(rlen)//递归建立右子树
        root->rchild = preincreat(a, b, h1 - rlen + 1, h1, h2 - rlen + 1, h2);
    else
        root->rchild = NULL;
    return root;
}

Bitree postincreat(int *a,int *b,int l1,int h1,int l2,int h2){
    //l1,h1是前序的第一和最后一个节点的下标。l2,h2是中序的第一和最后一个节点的下标。
    //初始调用时，l1=l2=1,h1=h2=n
    Bitree root = (BitNode *)malloc(sizeof(BitNode)); 
    root->key = a[h1];                                //根节点
    for (i = l2; b[i] != root->key ; i++);            //根节点在中序序列的划分
    llen = i - l2;                                    //左子树长度
    rlen = h2 - i;                                    //右子树长度
    if(llen)//递归建立左子树
        root->lchild = postincreat(a, b, l1 + 1, l1 + llen, l2, l2 + llen - 1);
    else
        root->lchild = NULL;
    if(rlen)//递归建立右子树
        root->rchild = postincreat(a, b, h1 - rlen + 1, h1, h2 - rlen + 1, h2);
    else
        root->rchild = NULL;
    return root;
}

int main(int argc, char const *argv[])
{
    Bitree root1 = nullptr;
    //PrintPostOrder(0, 0, 9);
    root1 = CreateBTree();//    ABDH##I##E##CF#J##G##
    nPostOrder(root1);
    printf("\n");
    PostOrder(root1);
    return 0;
}


// 由层序序列和中序序列建立二叉树
Bitree leveincreat(int n, char *level, char *mid)
{
    Bitree root;
    char left[20];
    char right[20];
    int i, j, k;
    int l, r;
    int lcnt, rcnt;

    lcnt = 0;
    rcnt = 0;

    if( n == 0 )
        return NULL;

    root = (Bitree)malloc(sizeof(BitNode));
    root->key = level[0];

    // 找到根节点
    for( i = 0; i < n; i++ )
        if( level[0] == mid[i] )
            break;

    // 划分左右子树
    for( k = 0; k < n; k++ )
    {
        for( l = 0; l < i; l++ )
        {
            if( mid[l] == level[k] )
            {

                left[lcnt++] = level[k];
            }
        }
        for( r = 0; r < n-i-1; r++ )
        {
            if( mid[r+i+1] == level[k] )
            {
                right[rcnt++] = level[k];
            }
        }
    }

    root->lchild = leveincreat( lcnt, left, mid );
    root->rchild = leveincreat( rcnt, right, mid+i+1 );

    return root;
}
