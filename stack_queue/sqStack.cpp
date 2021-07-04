#include<stdio.h>
typedef int ElemType;
#define MaxSize 10//定义栈中元素的最大个数
typedef struct{
    ElemType data[MaxSize];//化静态数组存放栈中元素
    int top;               //栈顶指针
} SqStack;


//初始化栈
void InitStack(SqStack &S){
    S.top = -1; //初始化栈顶指针
}

//判断栈空
bool StackEmpty(SqStack S){
    if(S. top==-1)//栈空
        return true;
    else          //不空
        return false;
}

//判断栈满
bool StackFull(SqStack S){
    if(S. top==MaxSize-1)//栈满
        return true;
    else          //不空
        return false;
}

//新元素入栈
bool Push(SqStack &S,ElemType x){
    if(S. top==MaxSize-1)//栈满， 报错
        return false;
    S.top = S.top + 1; //指针先加一
    S.data[S.top] = x; //新元素入栈
    return true;
}

//出栈操作
bool Pop(SqStack &S, ElemType x){
    if(S. top==-1)//栈空，报错
        return false;
    x = S.data[S.top]; //栈顶元素先出栈"
    S.top = S.top - 1; //指针再减1.
    return true;
}

//获取栈顶元素
bool GetTop(SqStack S, ElemType &x){
    if(S. top==-1)//栈空， 报错
        return false;
    x=S. data[S.top];//x记录栈顶元素
    return true;
}

typedef struct{
    ElemType data[MaxSize]; //静态数组存放栈中元素
    int top0;               // 0号栈栈顶指针
    int top1;               //1号栈栈顶指针
} ShStack;
//初始化栈
void InitStack(ShStack &S){
    S.top0 = -1; //初始化栈顶指针
    S.top1 = MaxSize;
}



int main(int argc, char const *argv[])
{
    SqStack s;
    InitStack(s);
    for (int i = 0; i < MaxSize; i++)
    {
        Push(s, i);
    }
    printf("\n栈空？%d\n", StackEmpty(s));
    printf("栈满？%d\n", StackFull(s));
    int x=0;
    for (int i = 0; i < MaxSize; i++)
    {
        GetTop(s, x);
        Pop(s, i);
        printf("%d,", x);
    }
    printf("\n栈空？%d\n", StackEmpty(s));
    printf("栈满？%d\n", StackFull(s));
    return 0;
}
