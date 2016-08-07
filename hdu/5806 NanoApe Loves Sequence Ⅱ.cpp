/*
HDU 5806 NanoApe Loves Sequence Ⅱ
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
__int64 a[200005];
int main()
{
    __int64 T;
    scanf("%I64d",&T);
    while(T--)
    {
        __int64 n,m,k,t;
        scanf("%I64d%I64d%I64d",&n,&m,&k);
        for(int i=0; i<n; i++)
        {
            scanf("%I64d",&t);
            a[i]=(t>=m)?1:0;
        }
        __int64 l=0,r=0,sum=a[0],ans=0;
        while(r<n)
        {
            if(sum==k)
            {
                ans+=n-r;
                sum-=a[l++];
            }
            else sum+=a[++r];
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
