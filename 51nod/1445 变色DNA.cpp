/*
51nod 1445 变色DNA
*/
/*
到最后还是一道最短路的问题，只不过建图的时候mapp[i][j]的数值为第i行从0~j-1中Y的数量，其他点设为INF
mapp指当前这种状态变成另一种状态所需要付出的代价！
因为测试用例范围不大，所以写一个最简单的Floyd就可以了
mapp[0][n-1]就代表从0变成n-1所付出的最小代价，若为INF，则无解
*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<set>
#include<string.h>
#define INF (1<<25)
using namespace std;
int mapp[55][55];
int n;
void floyd()
{
    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                mapp[i][j]=min(mapp[i][j],mapp[i][k]+mapp[k][j]);
    printf("%d\n",mapp[0][n-1]==INF?-1:mapp[0][n-1]);
}
int main()
{
    int T;
    char c;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%*c",&n);
        for(int i=0; i<n; i++)
            fill(mapp[i],mapp[i]+n,INF);
        for(int i=0; i<n; i++)
        {
            int s=0;
            for(int j=0; j<n; j++)
            {
                scanf("%c",&c);
                if(c=='Y')mapp[i][j]=s,s++;
            }
            getchar();
        }
        floyd();
    }
    return 0;
}
