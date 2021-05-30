#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 16

void tt(int n);
int *fun(int n, int t[]);
int hammingDistance(int x, int y);

int main(int argc, char const *argv[])
{
    // int value = 0;
    // printf("%d\n", 6);
    // tt(6);
    // printf("%d\n", 8);
    // tt(8);
    // value = 6 & 8;
    // printf("%d\n", value);
    // tt(value);
    int a = hammingDistance(1,4);
    printf("\n%d", a);
}


int hammingDistance(int x, int y){
    int value = 0;
    int count = 0;
    value = x ^ y;
    while(value){
        value = value & (value - 1);
        count++;
    }
    return count;
}

void tt(int n)
{
    int binaryNumber = 0;
    int remainder, i = 1;
 
    while (n!=0)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    printf("%08d\n", binaryNumber);
    return;
}

int *fun(int n,int t[]){
    int i = 0;
    while (n!=0)
    {
        t[i] = n % 2;
        n = n / 2;
        i++;
    }
    return t;
}
