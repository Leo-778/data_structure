#include<stdio.h>

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

