#include<stdio.h>
typedef char ElemType;
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
bool Pop(SqStack &S, ElemType &x){
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

bool brackCheck(char str[],int length){
    SqStack s;
    InitStack(s);
    for (int i = 0; i < length; i++)
    {
        if(str[i]=='(' || str[i]=='{' || str[i]=='['){
            Push(s, str[i]);
        }
            
        else{
            if (StackEmpty(s))
                return false;
            char topelem;
            Pop(s, topelem);
            if (str[i] == '(' && topelem != ')')
                return false;
            if (str[i] == '[' && topelem != ']')
                return false;
            if (str[i] == '{' && topelem != '}')
                return false;
        }
    }
    return StackEmpty(s);
}

int main(int argc, char const *argv[])
{
    char str[6]= {'(',')','(',')','(',')'};
    printf("%d", brackCheck(str, 5));
    return 0;
}
