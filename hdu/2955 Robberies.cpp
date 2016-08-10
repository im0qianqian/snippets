/*
HDU 2955 Robberies
*/

#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#define max(a,b) (a>b?a:b)
using namespace std;
struct po
{
    int vi;
    double p;
} a[10010];
double dp[10010];
int main()
{
    int T;
    scanf("%d",&T);
    double m,n;
    while(T--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%lf%lf",&m,&n);
        int sum=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d%lf",&a[i].vi,&a[i].p);
            sum+=a[i].vi;
        }
        dp[0]=1;
        for(int i=0; i<n; i++)
            for(int j=sum; j>=a[i].vi; j--)
                dp[j]=max(dp[j],dp[j-a[i].vi]*(1.0-a[i].p));
        for(int i=sum; i>=0; i--)
            if(dp[i]>1-m)
            {
                printf("%d\n",i);
                break;
            }
    }
    return 0;
}
