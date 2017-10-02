/*
51nod 1051 最大子矩阵和
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
ll a[555][555],c[555],dp[555];

ll solve(int n)
{
    ll ans=0;
    memset(dp,0,sizeof(dp));
    for(int i=1; i<=n; i++)
    {
        dp[i]=max(dp[i-1]+c[i],(ll) 0);
        ans=max(dp[i],ans);
    }
    return ans;
}
int main()
{
    int n,m,i,j,k;
    ll ans=0;
    cin>>m>>n;
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            cin>>a[i][j];
    for(i=1; i<=n; i++)
    {
        memset(c,0,sizeof(c));
        for(j=i; j<=n; j++)
        {
            for(k=1; k<=m; k++)
                c[k]=c[k]+a[j][k];
            ans=max(ans,solve(m));
        }
    }
    cout<<ans<<endl;
}


















