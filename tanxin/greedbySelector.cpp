#include<stdio.h>

const int n = 11;
int used[n]={false};//数组used用来记录那个活动进行过

void greedySelector(int *start,int *end){
	used[0] = true;
	int j = 0;
	for (int i = 1; i < n; i++)
	{
		if (start[i]>end[j])//相容
		{
			used[i] = true;//标记使用
			j = i;
		}
	}
}

int main(int argc, char const *argv[])
{
	int start[11]={1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	int end[11]={4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	greedySelector(start, end);
	for (int i = 0; i < n; i++)
	{
		if (used[i]==true)
		{
			printf("活动 %d ", i+1);
			printf("开始时间：%d ;结束时间：%d \n", start[i], end[i]);
		}
		
	}
	return 0;
}