/*
SCU 1015 History Grading
*/

#include<iostream>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int a[105],b[105];
int dp[105][105];
int solve(int *a,int *b,int n)
{
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
    int t,x;
    cin>>t;
    for(int i=0; i<t; i++)
    {
        cin>>x;
        a[x-1]=i;
    }
    while(cin>>x)
    {
        b[x-1]=0;
        memset(dp,0,sizeof(dp));
        for(int i=1; i<t; i++)
        {
            cin>>x;
            b[x-1]=i;
        }
        cout<<solve(a,b,t)<<endl;
    }
    return 0;
}
