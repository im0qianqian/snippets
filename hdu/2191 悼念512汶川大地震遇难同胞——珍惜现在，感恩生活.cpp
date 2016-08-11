/*
HDU 2191 悼念512汶川大地震遇难同胞——珍惜现在，感恩生活
*/

#include<cstdio>
#include<cstring>
#include<iostream>
#define max(a,b) (a>b?a:b)
using namespace std;
int p[105],h[105],c[105];
int dp[105];
void solve(int pi,int hi,int n)
{
    for(int i=n; i>=pi; i--)
        dp[i]=max(dp[i],dp[i-pi]+hi);
}
void mult(int pi,int hi,int ci,int n)
{
    int k=1;
    while(k<=ci)
    {
        solve(k*pi,k*hi,n);
        ci-=k;
        k<<=1;
    }
    solve(ci*pi,ci*hi,n);
}
int main()
{
    int C;
    scanf("%d",&C);
    while(C--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0; i<m; i++)
            scanf("%d%d%d",p+i,h+i,c+i);
        memset(dp,0,sizeof(dp));
        for(int i=0; i<m; i++)
            mult(p[i],h[i],c[i],n);
        printf("%d\n",dp[n]);
    }
    return 0;
}
