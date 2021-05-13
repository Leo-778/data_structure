#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
// 串的基本操作，顺序存储。
#define MAXLEN 255
typedef struct 
{
    char elem[MAXLEN];
    int length;
}Str;// 静态数组
typedef struct
{
    char *ch[MAXLEN];
    int length;
}HString;//动态数组

void StrAssign(Str *s, const char *chars);//初始化串
void StrCpy(Str *s, Str *t);              //拷贝串
int Getlength(Str *s);//获取串的长度
void Clear(Str *s);//清空串s
bool Inset(Str *s,int pos,Str *t);//在串s的pos位置插入串t
void Show(Str *s) ;//打印串
int BF(Str *s,Str *sub,int pos);//在串s里找第一个串sub，并返回串sub的第一个元素的下标
int BF(Str *s, Str *sub);      //查找子串在串中的位置，并换回下标。
bool DeletePos(Str* s,int pos,int len);//在串中的pos位置开始删除len长度个元素
bool Delete(Str *s,int pos,Str *t);//在串中的pos位置开始删除串t
bool Replace(Str *s,Str *t,Str *v,int pos);//用v替换从pos位置开始的第一个t
bool RepIaceAll(Str *s,Str *t,Str *v);//在串s中查找到串t并用串v替换

int main(int argc, char const *argv[])
{
    Str str1,str2;
    char const *ch1 = "heoooooo,world";
    char const *ch2 = ",";
    StrAssign(&str1, ch1);
    StrAssign(&str2, ch2);
    Show(&str1);
    Show(&str2);

    int i = BF(&str1, &str2);
    printf("%d\n", i);

    printf("hello world");

    return 0;
}


// int main()
// {
//     Str s;
//     char const *s1 = "abcdecdfcd";
//     StrAssign(&s, s1);
//     Show(&s);

//     // Str t;
//     // char *t1 = "cd";
//     // StrAssign(&t, t1);
//     // Show(&t);
//     /*
//     Inset(&s, 2, &t);
//     Show(&s);

//     Inset(&s, 7, &t);
//     Show(&s);*/

//     /*int index = BF(&s,&t,0);
//     printf("index = %d\n",index);*/

//     /*DeletePos(&s,3,2);
//     Show(&s);*/

//     /*Str v;
//     char *v1 = "zkr";
//     StrAssign(&v, v1);
//     Show(&v);
//     Replace(&s,&t,&v,0);
//     Show(&s);*/

//     // Str v;
//     // char *v1 = "zkr";
//     // StrAssign(&v, v1);
//     // Show(&v);
//     // RepIaceAll(&s,&t,&v);
//     // Show(&s);
//     // system("pause");
//     return 0;
// }


void StrAssign(Str *t,const char *a){ //初始化串
    int len = strlen(a);
    t->length = len;
    for (int i = 0; i < len; i++)
        t->elem[i] = a[i];
    return;
}

void StrCpy(Str*s, Str*t)//拷贝串
{
    for(int i = 0;i<t->length;i++)
    {
        s->elem[i] = t->elem[i];
    }
    s->length = t->length;
}

int Getlength(Str *s)//获取串的长度
{
    return s->length ;
}

void Clear(Str *s)//清空串s
{
    s->length = 0;
}

bool SubStr(Str *sub,Str *s,int pos,int len)//空白字符不拷贝
{
    if(pos < 0 || len < 1||pos >=s->length||pos+len>s->length-1)
    {
        return false;
    }
    for(int i = pos;i<pos+len;i++)
    {
        sub->elem[i-pos] = s->elem[i];
    }
    sub->length = len;
    return true;
}

bool Inset(Str *s,int pos,Str *t)//在串s的pos位置插入串t
{
    assert(s!=NULL);
    assert(t!=NULL);
    if(pos<0||pos>s->length||pos+t->length>MAXLEN)
    {
        return false;
    }
    for(int i = s->length-1;i>=pos;i--)
    {
        s->elem[i+t->length] = s->elem[i];  
    }
    for(int j = 0;j<t->length;j++)
        {
            s->elem[j+pos] = t->elem[j];
        }
    s->length +=t->length;
    return true;
}

int BF(Str *s,Str *sub){//查找子串在串中的位置，并换回下标。
    int i = 0,j=0,t,k=0;
    while (1)
    {
        if (s->elem[i]==sub->elem[j]){
            t = i;
            if (s->length-i<sub->length)
                return -1;
            for (k = 0; k < sub->length; k++){
                if (s->elem[i]==sub->elem[j]){
                    i++;
                    j++;
                }
                else{
                    i = t;
                    j = 0;
                    break;
                }
            }
            if (k==sub->length)
            {
                return t;
            }
        }
        i++;
        if (i>s->length)
            break;
    }
    return -1;
}

int BF(Str *s,Str *sub,int pos)//在串s里找第一个串sub，并返回串sub的第一个元素的下标
{
    if(pos<0||pos>s->length)
    {
        return -1;
    }

    int i = pos;
    int j = 0;

    int lens = s->length;
    int lensub = sub->length;

    while (i < lens && j < lensub)
    {
        if (s->elem[i] == sub->elem[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= lensub)
        {
            return i - j;
        }
        else 
            return -1;
}

bool DeletePos(Str* s,int pos,int len)//从pos位置开始删除len个长度
{
    assert(s!=NULL);
    if(pos<0||pos+len>s->length||len<0)
    {
        return false;
    }
    //for(int i = pos;i<len+pos;i++)
    for(int i = pos;i<s->length-len;i++)
    {
        s->elem[i] = s->elem[i+len];
    }
    s->length -= len;
    return true;
}

bool Delete(Str *s,int pos,Str *t)//在串中的pos位置开始删除串t
{
    assert(s!=NULL);
    assert(t!=NULL);
    if(pos<0||pos>s->length||t->length>s->length)
    {
        return false;
    }
    int index = BF(s,t,pos);
    if(index < 0)
    {
        return false;
    }
    return DeletePos(s,index,t->length);
}
bool Replace(Str *s,Str *t,Str *v,int pos)//用v替换从pos位置开始的第一个t
{
    assert(s!=NULL);
    assert(t!=NULL);
    assert(v!=NULL);

    int index = BF(s,t,pos);
    if(index < 0)
    {
        return false;
    }
    DeletePos(s,index,t->length);
    return Inset(s,index,v);
}
bool RepIaceAll(Str *s,Str *t,Str *v)//在串s中查找到串t并用串v替换
{
    assert(s!=NULL);
    assert(t!=NULL);
    assert(v!=NULL);

    while(Replace(s,t,v,0));
    return true;
}
void Show(Str *s) //打印  
{
    for(int i=0;i<Getlength(s);i++)
    {
        printf("%c",s->elem[i]); 
    }
    printf("\n");
}  


// void StrAssign(SString *s,const char *chars);//初始化串
// void StrCpy(SString*s, SString*t);//拷贝串
// int Getlength(SString *s);//获取串的长度
// void Clear(SString *s);//清空串s
// bool Inset(SString *s,int pos,SString *t);//在串s的pos位置插入串t
// void Show(SString *s) ;//打印串
// int BF(SString *s,SString *sub);//查找子串在串中的位置，并换回下标。
// bool DeletePos(SString* s,int pos,int len);//在串中的pos位置开始删除len长度个元素
// bool Delete(SString *s,int pos,SString *t);//在串中的pos位置开始删除串t
// bool Replace(SString *s,SString *t,SString *v,int pos);//用v替换从pos位置开始的第一个t
// bool RepIaceAll(SString *s,SString *t,SString *v);//在串s中查找到串t并用串v替换





// int Getlength(SString *s){//获取串的长度
//     return s->length;
// }

// void Clear(SString *s)//清空串s
// {
//     s->length = 0;
//     return;
// }
// bool Inset(SString *s,int pos,SString *t){//在串s的pos位置插入串t
//     if (pos<0||pos>s->length||s->length+t->length>MAXLEN){
//         return false;
//     }
//     for (int i = s->length-1; i > pos-1; i--)
//         s->ch[i + t->length] = s->ch[i];
//     for (int i = pos,j=0; i < t->length; i++,j++)
//     {
//         s->ch[i] == t->ch[j];
//     }
//     s->length = s->length + t->length;
//     return true;
// }
// void Show(SString *s) {//打印串
//     for (int i = 0; i < s->length; i++)
//     {
//         printf("%c", s->ch);
//     }
//     printf("\n");
// }

// bool DeletePos(SString* s,int pos,int len){//在串中的pos位置开始删除len长度个元素

// }
// bool Delete(SString *s,int pos,SString *t);//在串中的pos位置开始删除串t
// bool Replace(SString *s,SString *t,SString *v,int pos);//用v替换从pos位置开始的第一个t
// bool RepIaceAll(SString *s,SString *t,SString *v);//在串s中查找到串t并用串v替换