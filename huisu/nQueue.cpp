#include<stdio.h>
//n皇后问题
int count = 0;

bool isvalid(int row,int col,char Q[4][4]){
    for (int i = 0; i < row; i++)
    {
        if (Q[i][col]=='Q'){
            return false;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--,j--)
    {
        if(Q[i][j]=='Q')
            return false;
    }
    for (int i = row-1, j = col+1; i>=0 && j<4; i--,j++)
    {
        if(Q[i][j]=='Q')
            return false;
    }
    return true;
}

void Queue(int row,char Q[4][4]){
    if (row==4)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%c ", Q[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        count++;
        return;
    }
    for (int j = 0; j < 4; j++)
    {
        if (isvalid(row,j,Q))
        {
            Q[row][j] = 'Q';
            Queue(row + 1, Q);
            Q[row][j] = '*';
        }
    }
}
int main(int argc, char const *argv[])
{
    char Q[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Q[i][j] = '*';
        }
    }
    Queue(0, Q);
    return 0;
}
