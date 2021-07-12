#include <stdio.h>
#include <string.h>

//朴素模式匹配算法,B为主串，A为子串
int Bf(char *B,char *A){
    int i=0, j=0;
    while (i<int(strlen(B))&&j<int(strlen(A)))
    {
        if (B[i]==A[j])
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
    //跳出循环有两种可能，i=strlen(B)说明已经遍历完主串，匹配失败；
    //j=strlen(A),说明子串遍历完成，在主串中成功匹配
    if (j==int(strlen(A)))
    {
        return i - int(strlen(A)) + 1;
    }
    return 0;
}
int main() {
    int number=Bf("aabcabcacbab", "abcac");
    printf("%d",number);
    return 0;
}