/*
51nod 1083 矩阵取数问题
*/
#include <iostream>
using namespace std;
int a[550][550],dp[550][550];
int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            cin>>a[i][j];
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            dp[i][j]=a[i][j]+max(dp[i-1][j],dp[i][j-1]);
    cout<<dp[n][n]<<endl;
    return 0;
}
