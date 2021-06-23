#include<stdio.h>
int count = 0;
bool isvalid(int row,int col,char Q[4][4]){//检查位置是否合法
    //检查列
    for (int i = 0; i < row; i++)
    {
        if(Q[i][col]=='Q')
            return false;
    }
    //检查左上角
    for (int i = row - 1, j = col - 1; i >=0 && j >= 0; i--, j--)
    {
        if(Q[i][j]=='Q')
            return false;
    }
    //检查右上角
    for(int i = row - 1, j = col + 1; i >= 0 && j < 4; i--, j++)
    {
        if(Q[i][j]=='Q')
            return false;
    }
    return true;
}
void Queue(int row,char Q[4][4]){
    if (row==4)
    {
        for(int i=0; i<4; i++){
            for(int k=0; k<4; k++)
                printf("%c ", Q[i][k]);//得到一个解，在屏幕上显示
            printf("\n");
        }
        printf("\n");
        count++;
        return ;
    }
    for (int i = 0; i < 4; i++)
    {
        if (isvalid(row,i,Q))
        {
            Q[row][i] = 'Q';//放置皇后
            Queue(row + 1, Q);
            Q[row][i] = '*';
        }
        
    }
    
}

int main()
{
    char Q[4][4];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            Q[i][j] = '*';
    Queue(0, Q);
    printf("摆放的方式有 %d 种\n", count);
    return 0;
}
