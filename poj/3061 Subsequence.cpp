/*
POJ 3061 Subsequence
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include<string.h>
#include<stack>
#define INF 1e6+5
using namespace std;
__int64 a[100500];
int main()
{
    __int64 T;
    scanf("%I64d",&T);
    while(T--)
    {
        __int64 n,m;
        scanf("%I64d%I64d",&n,&m);
        for(__int64 i=0; i<n; i++)
            scanf("%I64d",a+i);
        __int64 sum=0,i=0,j=0,s=INF;
        while(j<n)
        {
            while(sum<m&&i<n)sum+=a[i++];
            if(sum>=m)s=min(i-j,s);
            sum-=a[j++];
        }
        printf("%I64d\n",s==INF?0:s);
    }
    return 0;
}
