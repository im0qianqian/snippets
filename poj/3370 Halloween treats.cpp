/*
POJ 3370 Halloween treats
*/

#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
int pri[110000],sum[110000];
int main()
{
    int c,n,a;
    while(~scanf("%d%d",&c,&n)&&(c||n))
    {
        memset(pri,-1,sizeof(pri));
        memset(sum,0,sizeof(sum));
        pri[0]=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d",&a);
            sum[i]=(sum[i-1]+a)%c;
        }
        for(int i=1; i<=n; i++)
        {
            int *temp=pri+sum[i];
            if(*temp==-1)
                *temp=i;
            else
            {
                for(int j=*temp+1; j<=i; j++)
                    printf(j!=i?"%d ":"%d\n",j);
                break;
            }
        }
    }
    return 0;
}
