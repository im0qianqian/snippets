/*
HDU 5804 Price List
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
__int64 a[100005],b[100005];
int main()
{
    __int64 T;
    scanf("%I64d",&T);
    while(T--)
    {
        __int64 n,m,t,s=0;
        scanf("%I64d%I64d",&n,&m);
        for(__int64 i=1; i<=n; i++)
        {
            scanf("%I64d",a+i);
            s+=a[i];
        }
        for(__int64 i=1; i<=m; i++)
        {
            scanf("%I64d",&t);
            if(t>s)printf("1");
            else printf("0");
        }
        puts("");
    }
    return 0;
}