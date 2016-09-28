/*
POJ 1306 Combinations

题意：求组合数
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

__int64 c[1005][1005];
void init() //组合数打表
{
    for(int i=0; i<1000; i++)
    {
        c[i][0]=1;
        for(int j=1; j<=i; j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    }
}
int main()
{
    int n,m;
    init();
    while(~scanf("%d%d",&n,&m)&&(n||m))
        printf("%d things taken %d at a time is %I64d exactly.\n",n,m,c[n][m]);
    return 0;
}
