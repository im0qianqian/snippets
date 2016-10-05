/*
POJ 3641 Pseudoprime numbers

题意：判断(a^p%p)是否a，满足输出yes，否则输出no。
*/
#include <iostream>
#include<stdio.h>
using namespace std;
#define LL __int64
bool isprime(__int64 n) //判断是否是素数
{
    if(n<2)return false;
    for(int i=2; i*i<=n; i++)
        if(n%i==0)return false;
    return true;
}

LL mult(LL a,LL n,LL mod)   //(a^n)%mod
{
    LL s=1;
    while(n)
    {
        if(n&1)s=((s%mod)*(a%mod))%mod;
        a=((a%mod)*(a%mod))%mod;
        n>>=1;
    }
    return s;
}

int main()
{
    LL a,p;
    while(~scanf("%I64d%I64d",&p,&a)&&(a||p))
        printf((!isprime(p)&&mult(a,p,p)==a)?"yes\n":"no\n");
    return 0;
}
