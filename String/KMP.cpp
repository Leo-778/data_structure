#include<stdio.h>
#include<string.h>

void get_next(char *T,int *next){
    int i=1,j=0;
    next[1]=0;
    while(i<int(strlen(T))){
        if(j==0 || T[i]==T[j]){
            ++i;++j;
            next[i]=j;
        }
        else
            j=next[j];
    }
}
int KMP(char *B,char *A){
    int i = 0, j = 0;
    int next[int(strlen(A))+1];
    get_next(A,next);
    while (i<int(strlen(B))&&j<int(strlen(A)))
    {
        if (j==0 || B[i]==A[j])
        {
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    if (j==int(strlen(A)))
    {
        return i - j + 1;
    }
    return 0;
}

int main() {
    int number=KMP("aabcabcacbab", "abcac");
    printf("%d",number);
    return 0;
}