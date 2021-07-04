#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

typedef struct Linknode{
    ElemType data;         //数据域
    struct Linknode *next; //指针域
} *LiStack;//栈类型定义

//初始化栈
void InitStack(LiStack &S){
    S = NULL;
}

//判断栈空
bool StackEmpty(LiStack S){
    if (S==NULL)
    {
        return true;
    }
    return false;
}

//新元素入栈
void Push(LiStack &S,ElemType x){
    LiStack p = (LiStack)malloc(sizeof(Linknode));
    p->next = S;
    p->data = x;
    S = p;
}

//出栈操作
bool Pop(LiStack &S, ElemType &x){
    if (StackEmpty(S))
    {
        return false;
    }
    LiStack p;
    p = S;
    S = S->next;
    x = p->data;
    free(p);
    return true;
}

//获取栈顶元素
bool GetTop(LiStack S, ElemType &x){
    if (StackEmpty(S))
    {
        return false;
    }
    x = S->data;
    return true;
}

int main(int argc, char const *argv[])
{
    LiStack s;
    InitStack(s);
    for (int i = 0; i < 10; i++)
    {
        Push(s, i);
    }
    printf("\n栈空？%d\n", StackEmpty(s));
    int x=0;
    for (int i = 0; i < 10; i++)
    {
        Pop(s, x);
        printf("%d,", x);
    }
    printf("\n栈空？%d\n", StackEmpty(s));
    return 0;
}
