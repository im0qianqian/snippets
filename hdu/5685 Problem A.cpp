/*
HDU 5685 Problem A

题意：求字符串[a,b]之中字符ASCIL-28的乘积mod9973(素数)

思路：建立二叉索引树，然后求得[1,b]与[1,a]，再利用乘法逆元求得[1,b] / [1,a] 便是答案
*/

#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define mod 9973
#define lowbit(x) (x&-x)    //索引
using namespace std;

typedef __int64 LL;

char c[110000];
int cs[110000],n;

void add(int x,int s)   //树状数组中增加元素
{
    while(x<=n)
    {
        cs[x]=(cs[x]*s)%mod;
        x+=lowbit(x);
    }
}

LL mult(int a,int s)    //快速幂取模
{
    LL ans=1;
    while(s)
    {
        if(s&1)ans=ans*a%mod;
        a=a*a%mod;
        s>>=1;
    }
    return ans;
}

LL sum(int x)           //求区间[1,x]的 ∏ (各项连乘)
{
    LL ans=1;
    while(x>0)
    {
        ans=ans*cs[x]%mod;
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    int t;
    while(~scanf("%d%*c",&t))
    {
        gets(c);
        n=strlen(c);
        for(int i=0; i<=n; i++)
            cs[i]=1;
        for(int i=0; i<(int)strlen(c); i++)
            add(i+1,c[i]-28);
        int start,en;
        while(t--)
        {
            scanf("%d%d",&start,&en);
            LL smax=sum(en),mmax=sum(start-1);  //分别求[1,start-1]与[1,en]的∏ ,答案为smax/mmax
            LL nmax=mult(mmax,9971);            //求mmax的逆元，然后(smax / mmax)%mod == (smax * nmax) %mod
            cout<<smax*nmax%mod<<endl;
        }
    }
    return 0;
}
