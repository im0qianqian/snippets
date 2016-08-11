/*
POJ 2785 4 Values whose Sum is 0
*/

#include<cstdio>
#include<math.h>
#include<iostream>
#include<algorithm>
#define max(a,b) (a>b?a:b)
using namespace std;
__int64 a[4005],b[4005],c[4005],d[4005];
__int64 cd[4005*4005];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%I64d%I64d%I64d%I64d",a+i,b+i,c+i,d+i);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cd[i*n+j]=c[i]+d[j];
    sort(cd,cd+n*n);
    __int64 ans=0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            __int64 ab=-(a[i]+b[j]);
            ans+=upper_bound(cd,cd+n*n,ab)-lower_bound(cd,cd+n*n,ab);
        }
    printf("%I64d\n",ans);
    return 0;
}
