/*
51nod 1134 最长递增子序列
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
__int64 a[50005];
__int64 dp[50005];
void solve(int n)
{
    fill(dp,dp+50005,1e9+5);
    for(int i=0; i<n; i++)
        *lower_bound(dp,dp+n,a[i])=a[i];
    cout<<lower_bound(dp,dp+n,1e9+5)-dp<<endl;
}
int main()
{
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i];
    solve(n);
    return 0;
}
