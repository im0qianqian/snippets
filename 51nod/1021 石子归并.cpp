/*
51nod 1021 石子归并
*/

#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define INF (1<<30)
int dp[1005][1005];
int a[1005],sum[1005];
int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=1; i<=n; i++)
        for(int start=1; start<=n-i; start++)
        {
            int end=start+i,minn=INF;
            for(int k=start; k<end; k++)
                minn=min(minn,dp[start][k]+dp[k+1][end]+sum[end]-sum[start-1]);
            dp[start][end]=minn;
        }
    cout<<dp[1][n]<<endl;
    return 0;
}
