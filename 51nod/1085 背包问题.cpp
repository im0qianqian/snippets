/*
51nod 1085 背包问题
*/
#include <iostream>
using namespace std;
int dp[105][10005];
int w[105], h[105];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        cin>>h[i]>>w[i];
    for(int i=1; i<=n; i++)
        for(int j=0; j<=m; j++)
        {
            if(j<h[i])dp[i][j]=dp[i-1][j];
            else dp[i][j]=max(dp[i-1][j],dp[i-1][j-h[i]]+w[i]);
        }
    cout<<dp[n][m]<<endl;
    return 0;
}
