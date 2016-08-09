/*
51 nod 1179 最大的最大公约数
*/

#include<bits/stdc++.h>
using namespace std;
#define maxn 1001000
int num[maxn];
int main()
{
    int n,i,j,sum,t,mmax=0;
    cin>>n;
    for(i=1; i<=n; i++)
    {
        cin>>t;
        num[t]++;
        if(t>mmax)mmax=t;
    }
    for(i=mmax; i>=1; i--)
    {
        sum=0;
        for(j=i; j<=mmax; j+=i)
        {
            sum+=num[j];
            if(sum>=2)break;
        }
        if(sum>=2)break;
    }
    printf("%d\n",i);
    return 0;
}

