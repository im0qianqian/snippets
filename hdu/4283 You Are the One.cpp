/*
HDU 4283 You Are the One

题意：有一个队列，每个人有一个愤怒值D，如果他是第K个上场，不开心指数就为(K-1)*D。但是边上有一个栈，可以一定程度上调整上场程序，求不开心指数的最小和。

思路：dp[i][j]表示从第i个人到第j个人的最小花费（只考虑这j-i+1个人）

那么我们考虑[i,j]中的第i个人，他可以第1个上场，也可以第j-i+1个上场，设他为第k个出场，则k的范围为[1,j-i+1]。

对于第i个人第k个出场，则有[i+1,i+k-1]在i前面出场，[i+k,j]在i后面出场，于是有了两个子问题。

因为i是第k个出场的，所以其愤怒值是d[i]*(k-1)，另外[i+k,j]等待了k个出场，所以愤怒值加(sum[j]-sum[i+k-1])*k。

状态转移方程：dp[i][j]=min(dp[i][j],dp[i+1][i+k-1]+dp[i+k][j]+d[i]*(k-1)+(sum[j]-sum[i+k-1])*k)    //sum[i]代表前i个累加愤怒值
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stack>
using namespace std;
#define MAXX 105
#define INF (1<<25)
int d[MAXX],dp[MAXX][MAXX],sum[MAXX];
int main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1; ti<=T; ti++)
    {
        int N;
        scanf("%d",&N);
        for(int i=1; i<=N; i++)
        {
            scanf("%d",d+i);
            sum[i]=sum[i-1]+d[i];   //前i个累计愤怒值
        }
        memset(dp,0,sizeof(dp));
        for(int i=1; i<=N; i++)
            fill(dp[i]+i+1,dp[i]+N+1,INF);
        for(int l=1; l<=N; l++)
        {
            for(int i=1; i<=N-l+1; i++)
            {
                int j=i+l-1;
                for(int k=1; k<=l; k++)
                    dp[i][j]=min(dp[i][j],dp[i+1][i+k-1]+dp[i+k][j]+d[i]*(k-1)+(sum[j]-sum[i+k-1])*k);
            }
        }
        printf("Case #%d: %d\n",ti,dp[1][N]);
    }
    return 0;
}
