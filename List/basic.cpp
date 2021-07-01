#include<stdio.h>
#include<stdlib.h>
//顺序表基本操作

#define MaxSize 10 //定义最大长度

typedef int ElemType;

typedef struct{
    ElemType data[MaxSize]; //用静态的“数组”存放数据元素
    int length; //顺序表的当前长度
}SqList; //顺序表的类型定义（静态分配方式）

#define InitSize 10 //顺序表的初始长度
typedef struct{
    ElemType *data; //指示动态分配数组的指针
    int maxn; //记录顺序表分配的存储容量
    int length; //顺序表的当前长度
} SeqList; //顺序表的类型定义（动态分配方式）

/*********************************静态分配***********************************/
//初始化
void InitList(SqList &l){
    l.length = 0;
}
//插入（增）（在第i个位置插入x）
bool InsertList(SqList &l,int i,int x){
    if (i<1||i>l.length+1)
        return false;
    if(l.length>=MaxSize)
        return false;
    for (int j = l.length; j >= i;j--){
        l.data[j] = l.data[j - 1];
    }
    l.data[i - 1] = x;
    l.length++;
    return true;
}
//删除（删）（删除第i个元素，并将值赋给x）
bool DeleteList(SqList &l,int i,int &x){
    if (i<1||i>l.length)
        return false;
    x = l.data[i - 1];
    for (int j = i; j < l.length;j++)
        l.data[j - 1] = l.data[j];
    l.length--;
    return true;
}
//查找（查）
//按位查找
ElemType GetElem(SqList L, int i){
	return L.data[i-1];
}
//按值查找（在顺序表L中查找第一个元素值等于e的元素，并返回其位序）
int LocateElem(SqList L,ElemType e){
    for(int i=0;i<L.length;i++){
    	if(L.data[i]==e)
    		return i+1; //数组下标为i的元素值等于e，返回其位序i+1
    }
    return 0; //退出循环，说明查找失败
}

//修改（改）(将elem修改为x)
bool AmendList(SqList &l,int elem,int x){
    int i = LocateElem(l, elem);
    if (i==0)
        return false;
    l.data[i - 1] = x;
    return true;
}

/*********************************静态分配***********************************/

/*********************************动态分配***********************************/

//初始化
void InitList(SeqList &l){
    l.data = (int *)malloc(InitSize * sizeof(int));
    l.length = 0;
    l.maxn = InitSize;
}
//插入（增）
bool InsertList(SeqList &l,int i,int x){
    if (i<1||i>l.length+1)
        return false;
    if(l.length>=MaxSize)
        return false;
    for (int j = l.length; j >= i;j--){
        l.data[j] = l.data[j - 1];
    }
    l.data[i - 1] = x;
    l.length++;
    return true;
}
//删除（删）
bool DeleteList(SeqList &l,int i,int &x){
    if (i<1||i>l.length)
        return false;
    x = l.data[i - 1];
    for (int j = i; j < l.length;j++)
        l.data[j - 1] = l.data[j];
    l.length--;
    return true;
}
//查找（查）
//按位查找
ElemType GetElem(SeqList L, int i){
	return L.data[i-1];
}
//按值查找（在顺序表L中查找第一个元素值等于e的元素，并返回其位序）
int LocateElem(SeqList L,ElemType e){
    for(int i=0;i<L.length;i++)
    if(L.data[i]==e)
    return i+1; //数组下标为i的元素值等于e，返回其位序i+1
    return 0; //退出循环，说明查找失败
}
//修改（改）
bool AmendList(SeqList &l,int elem,int x){
    int i = LocateElem(l, elem);
    if (i==0)
        return false;
    l.data[i - 1] = x;
    return true;
}

/*********************************动态分配***********************************/

void printlist(SqList t) {
    int i;
    for (i = 0; i < t.length; i++) {
        printf("%d ", t.data[i]);
    }
    printf("\n");
}

int main() {
    int i, x;
    SqList l1;
    InitList(l1);
    for (i = 1; i <= MaxSize; i++) {
        l1.data[i - 1] = i;
        l1.length++;
    }
    printf("原顺序表：\n");
    printlist(l1);
    printf("删除元素1:\n");
    DeleteList(l1, 1, x);
    printlist(l1);
    printf("在第2的位置插入元素5:\n");
    InsertList(l1, 2, 5);
    printlist(l1);
    printf("查找元素3的位置:\n");
    x = LocateElem(l1, 3);
    printf("%d\n", x);
    printf("将元素3改为6:\n");
    AmendList(l1, 3, 6);
    printlist(l1);
    return 0;
}
