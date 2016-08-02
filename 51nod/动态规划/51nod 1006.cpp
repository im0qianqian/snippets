/*
51nod 1006 最长公共子序列Lcs
*/
#include <stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
char a[1005],b[1005],ans[1005];
int dp[1005][1005];
int main()
{
    gets(a);
    gets(b);
    int n=strlen(a);
    int m=strlen(b);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
        {
            if(a[i-1]==b[j-1])dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    int k=dp[n][m]-1;
    int i=n,j=m;
    while(i>0&&j>0)
    {
        if(a[i-1]==b[j-1])
        {
            ans[k--]=a[i-1];
            i--;
            j--;
        }
        else if(dp[i-1][j]>dp[i][j-1])i--;
        else j--;
    }
    cout<<ans<<endl;
    return 0;
}
