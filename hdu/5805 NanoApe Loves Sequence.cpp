/*
HDU 5805 NanoApe Loves Sequence
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
__int64 a[100500],dp[100500];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        long int N;
        scanf("%ld",&N);
        for(long int i=0; i<N; i++)
            scanf("%I64d",a+i);
        __int64 maxx=0,mainx=0,smax=0;
        for(long int i=1; i<N; i++)
            dp[i]=abs(a[i]-a[i-1]);
        sort(dp+1,dp+N);
        maxx=dp[N-1],mainx=dp[N-2],smax=dp[N-3];
        __int64 s=0;
        for(long int i=0; i<N; i++)
        {
            if(i==0)
            {
                if(abs(a[1]-a[0])==maxx)s+=mainx;
                else s+=maxx;
            }
            else if(i==N-1)
            {
                if(abs(a[N-1]-a[N-2])==maxx)s+=mainx;
                else s+=maxx;
            }
            else
            {
                __int64 t=abs(a[i+1]-a[i-1]);
                __int64 le=abs(a[i]-a[i-1]),ri=abs(a[i]-a[i+1]);
                if(le==maxx||ri==maxx)
                {
                    if(t>=maxx)s+=t;
                    else
                    {
                        if(le==mainx||ri==mainx)
                        {
                            if(t>=mainx)s+=t;
                            else s+=smax;
                        }
                        else
                        {
                            if(t>=mainx)s+=t;
                            else s+=mainx;
                        }
                    }
                }
                else if(t>maxx)s+=t;
                else s+=maxx;
            }
        }
        printf("%I64d\n",s);
    }
    return 0;
}
