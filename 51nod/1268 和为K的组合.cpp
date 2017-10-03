/*
51nod 1268 和为K的组合
*/

#include <stdio.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<list>
#include<map>
using namespace std;

__int64 a[25],dp[10000000];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0; i<n; i++)
        scanf("%I64d",a+i);
    for(int i=n-1; i>=0; i--)
        for(int j=k; j>=a[i]; j--)
            dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
    if(dp[k]!=k)printf("No\n");
    else printf("Yes\n");
    return 0;
}
