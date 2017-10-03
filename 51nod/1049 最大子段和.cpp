/*
51nod 1049 最大子段和
*/
#include<iostream>
using namespace std;
__int64 a[50005],dp[50005],s;
int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    for(int i=1; i<=n; i++)
    {
        if(dp[i-1]>0)dp[i]=dp[i-1]+a[i];
        else dp[i]=a[i];
        s=max(dp[i],s);
    }
    cout<<s<<endl;
    return 0;
}
