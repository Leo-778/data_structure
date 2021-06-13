#include<stdio.h>
#include<stdlib.h>
void RadixSort(int*a,int n)
{
	int max=a[0];
    int i;
    for(int i=1;i<n;i++)//找出最大值
 	{
	 	 if(a[i]>max)
	 	 {
	  	 	max=a[i];
	  	 }
	 }
 	int base=1;
 	int *b=(int*)malloc(sizeof(int)*n);//每次操作后元素的排序状态都会保存在这个中间过度数组中
 	while(max/base>0)//循环的次数为最大值的位数，比如520是三位数，则循环三次
 	{
  		int t[10]={0};//声明并定义一个“桶数组”
 	for(int i=0;i<n;i++)//实现上面第一个小图的功能
  	{
  		 t[a[i]/base%10]++;
  	}
  	for(i=1;i<10;i++)//实现上面第二个小图的功能
 	{
  		 t[i]+=t[i-1];
  	}
 	for(i=n-1;i>=0;i--)
  	{
  		 b[t[a[i]/base%10]-1]=a[i];
  		 t[a[i]/base%10]--;
  	}
  	for(i=0;i<n;i++)//赋值
  	{
   		a[i]=b[i];
  	}
  	base=base*10;
 	}
}
int main(int argc, char const *argv[])
{
    int a[10] = {3, 2, 7, 6, 5, 8, 4, 1, 9, 0};
    RadixSort(a, 10);
    for (int i = 0; i < 10; i++)
    {
        if(i==9)
            printf("%d", a[i]);
        else
            printf("%d, ", a[i]);
    }
    
    return 0;
}