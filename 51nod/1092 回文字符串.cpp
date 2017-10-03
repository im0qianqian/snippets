/*
51nod 1092 回文字符串
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
char a[1005],b[1005];
int dp[1005][1005];
int solve()
{
    int n=strlen(a);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {
            if(a[i-1]==b[j-1])dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    return dp[n][n];
}
int main()
{
    gets(a);
    int n=strlen(a);
    for(int i=0; i<n; i++)
        b[n-i-1]=a[i];
    int ans=solve();
    cout<<n-ans<<endl;
    return 0;
}
