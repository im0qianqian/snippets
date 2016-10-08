/*
HDU 1576 A/B

题意：求(A/B)%9973，已知n(n=A%9973)，gcd(B,9973) = 1

在求解除法取模问题(a/b)%m时，我们可以转化为(a%(b*m))/b，但从题目来看这种解法并不可行。

逆元：满足a*k≡1(mod p)的k值就是a关于p的乘法逆元。

当我们要求 (a/b)%p 的值，且a很大，无法直接求得a/b的值时，我们就要用到乘法逆元。

我们可以通过求b关于p的乘法逆元k，然后 (a*k)%p ，与 (a/b)%p 是等价的。

因为9973是素数，所以我们可以采用费马小定理来求解逆元。

费马小定理：
    在p是素数的情况下，对任意整数x都有x^p≡x(mod p)
    如果x无法被p整除，则有x^(p−1)≡1(mod p)
    可以在p为素数的情况下求出一个数的逆元，x*x^(p−2)≡1(mod p)，x^(p−2)即为逆元。
*/

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

#define mod 9973
typedef __int64 ll;

ll mult(ll a,ll n)  //求a^n%mod
{
    ll s=1;
    while(n)
    {
        if(n&1)s=s*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return s;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ll n,b;
        scanf("%I64d%I64d",&n,&b);
        printf("%I64d\n",(n*mult(b,9973-2))%mod);
    }
    return 0;
}
