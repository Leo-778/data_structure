#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
//无重叠区域
int n = 4;

// 按照区间右边界排序
bool cmp (const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

int eraseOverlapIntervals1(vector<vector<int> > intervals){
    if(intervals.empty())// 如果长度为0则返回0
        return 0;

    sort(intervals.begin(), intervals.end(), cmp);// 按照首元素进行升序排序
    int n = intervals.size();
    int ans = 1;
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        if (intervals[i][0]>=intervals[j][1])
        {
            ans++;
            j = i;
        }
    }
    return n - ans;
}


int main(int argc, char const *argv[])
{
    vector<vector<int>> intervals = {{1,100}, {11,22}, {1,11}, {2,12}};
    
    printf("%d", eraseOverlapIntervals1(intervals));
    return 0;
}
