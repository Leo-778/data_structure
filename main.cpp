#include<stdio.h>
#include<vector>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<int> vi;
    for (int i = 1; i <= 5; i++)
    {
        vi.push_back(i);//此时为1，2，3，4，5
    }
    vi.insert(vi.begin() + 2, -1);//将-1插入vi[2]的位置
    for (int i = 0; i < vi.size(); i++)
    {
        printf("%d ", vi[i]);
    }
    return 0;
}
