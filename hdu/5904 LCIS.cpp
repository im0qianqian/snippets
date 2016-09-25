/*
HDU 5904 LCIS

题意：给定两个序列，求它们的最长公共递增子序列的长度, 并且这个子序列的值是连续的。

分析：我们可以先处理a,b的每个数的最长连续长度，最终取两者最小值的最大值
    状态转移方程：dp[a[i]] = max(dp[a[i]], dp[a[i]-1] + 1);
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
#define MMAX 110000
int a[MMAX],b[MMAX],dpa[MMAX],dpb[MMAX];
int main()
{
    cout.sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        int n,m;
        cin>>n>>m;
        memset(dpa,0,sizeof(dpa));
        memset(dpb,0,sizeof(dpb));
        int maxx=0;
        for(int i=1; i<=n; i++)
        {
            cin>>a[i];
            dpa[a[i]]=dpa[a[i]-1]+1;
            maxx=max(maxx,a[i]);
        }
        for(int i=1; i<=m; i++)
        {
            cin>>b[i];
            dpb[b[i]]=dpb[b[i]-1]+1;
            maxx=max(maxx,b[i]);
        }
        int ans=0;
        for(int i=1; i<=maxx; i++)
            ans=max(ans,min(dpa[i],dpb[i]));
        cout<<ans<<endl;
    }
}
