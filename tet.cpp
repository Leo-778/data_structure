#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

struct Student{
    char id[15];
    int score;
    int location_number;
    int local_rank;
}stu[30010];

bool cmp(Student a,Student b){
    if (a.score!=b.score)
    {
        return a.score > b.score;//分数不相同时，按分数从高到低排序
    }
    else
        return strcmp(a.id, b.id) < 0;//分数相同时，按学号从小到大排序
}

int main(int argc, char const *argv[])
{
    int n, k, num = 0;//n为考场数，k为考场内人数，num为总考生数
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; j++)
        {
            scanf("%s %d", stu[num].id, &stu[num].score);
            stu[num].location_number = i;//考生考场号为i
            num++;//总考生数加1
        }
        sort(stu + num - k, stu + num, cmp);//考场内排序
        stu[num - k].local_rank = 1;
        for (int j = num-k+1; j<num; j++)
        {
            if(stu[j].score==stu[j-1].score)
                stu[j].local_rank = stu[j - 1].local_rank;//local_rank相同
            else
                stu[j].local_rank = j + 1 - (num - k);//local_rank为该考生前的人数
        }
    }
    printf("%d\n", num);//输出总排名
    sort(stu, stu + num, cmp);//将所有考生排序
    int r = 1;//当前考生的排名
    for (int i = 0; i < num; i++)
    {
        if (i>0 && stu[i].score != stu[i-1].score)
        {
            r = i + 1;//当前考生与上一个考生分数不同时，让r更新为人数+1
        }
        printf("%s ", stu[i].id);
        printf("%d %d %d\n", r, stu[i].location_number, stu[i].local_rank);
    }
    return 0;
}
