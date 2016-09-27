/*
HDU 3037 Saving Beans

题意：求n个数的和不超过m的方案数。


思路：题目可以转换成  x1+x2+……+xn=m 有多少组解，m在题中可以取0~m。

利用插板法可以得出x1+x2+……+xn=m解的个数为C（n+m-1，m）；

则题目解的个数可以转换成求 sum=C（n+m-1，0）+C（n+m-1，1）+C（n+m-1，2）……+C（n+m-1，m）

利用公式C（n，r）=C（n-1，r）+C（n-1，r-1）  == >  sum=C（n+m，m）。

现在就是要求C（n+m，m）%p。

因为n，m很大，这里可以直接套用Lucas定理的模板即可。
*/

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef __int64 LL;

LL exp_mod(LL a, LL b, LL p)
{
    LL res = 1;
    while(b != 0)
    {
        if(b&1) res = (res * a) % p;
        a = (a*a) % p;
        b >>= 1;
    }
    return res;
}

LL Comb(LL a, LL b, LL p)
{
    if(a < b)return 0;
    if(a == b)return 1;
    if(b > a - b)b = a - b;

    LL ans = 1, ca = 1, cb = 1;
    for(LL i = 0; i < b; ++i)
    {
        ca = (ca * (a - i))%p;
        cb = (cb * (b - i))%p;
    }
    ans = (ca*exp_mod(cb, p - 2, p)) % p;
    return ans;
}

LL Lucas(int n, int m, int p)
{
    LL ans = 1;

    while(n&&m&&ans)
    {
        ans = (ans*Comb(n%p, m%p, p)) % p;
        n /= p;
        m /= p;
    }
    return ans;
}

int main()
{
    int n, m, p,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d", &n, &m, &p);
        printf("%I64d\n", Lucas(n+m, m, p));    //C(n+m,m)%p
    }
    return 0;
}
