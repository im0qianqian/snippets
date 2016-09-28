/*
HDU 1436 排列组合（二）

题意：有N个字母，每个字母的数量不定。用这N个字母组成一个长为M的串，并且规定这个串中每个字母能出现的次数。求这样的串的总数。

递推式：d[g[i][k]+j] += d[j]*c[m-j][g[i][k]];
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

__int64 c[1005][1005],d[1005];  //d[i]表示字符串长度为i的时候用所给字符串构成的满足条件的情况数
int g[1005][1005];
void solve(int n,int m)
{
    memset(d,0,sizeof(d));
    for(int i=1; i<=g[0][0]; i++)
        if(g[0][i]<=m)
            d[g[0][i]] = c[m][g[0][i]]; //C m g[0][i]
    for(int i=1; i<n; i++)
        if(g[i][0])                     //当前字母有出现的种数
            for(int j=m; j>=0; j--)
                if(d[j])
                    for(int k=1; k<=g[i][0]&&j+g[i][k]<=m; k++) //j+g[i][k]在m范围内
                        if(g[i][k])
                            d[g[i][k]+j]+=d[j]*c[m-j][g[i][k]];
    printf("%I64d\n",d[m]);
}
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
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d",&g[i][0]);
            for(int j=1; j<=g[i][0]; j++)
                scanf("%d",&g[i][j]);
        }
        solve(n,m);
    }
    return 0;
}
