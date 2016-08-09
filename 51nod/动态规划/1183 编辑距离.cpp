/*
51nod 1183 编辑距离  
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
char a[1405],b[1405];
int dp[1405][1405];
int main()
{
    while(~scanf("%s %s",a,b))
    {
        memset(dp,0,sizeof(dp));
        int n=strlen(a),m=strlen(b);
        for(int i=0; i<=n; i++)
            dp[i][0]=i;
        for(int j=0; j<=m; j++)
            dp[0][j]=j;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                dp[i][j]=min(dp[i-1][j]+1,min(dp[i][j-1]+1,dp[i-1][j-1]+((a[i-1]==b[j-1])?0:1)));
        cout<<dp[n][m]<<endl;
    }
    return 0;
}
