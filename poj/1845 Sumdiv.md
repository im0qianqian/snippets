# Sumdiv

## **Description**

> Consider two natural numbers A and B. Let S be the sum of all natural divisors of A^B. Determine S modulo 9901 (the rest of the division of S by 9901).



## **Input**

> The only line contains the two natural numbers A and B, (0 <= A,B <= 50000000)separated by blanks.



## **Output**

> The only line of the output will contain S modulo 9901.



## **Sample Input**

    2 3



## **Sample Output**

    15


## **题意**

给出两个数a,b，求a^b的所有的因子之和。



## **思路**

对于任意一个数a，我们都可以将他表示为 $a=P_1^{m_1}*P_2^{m_2}*...*P_n^{m_n}$ ，其中，P1,P2,...Pn均为素数。

此时，对于数a，它的因子个数共有 $(m_1+1)*(m_2+1)*...*(m_n+1)$

所有因子和为 $(P_1^0+P_1^1+...+P_1^{m_1})*(P_2^0+P_2^1+...+P_2^{m_2})*...*(P_n^0+P_n^1+...+P_n^{m_n})$

于是，我们可以对a进行素因子分解，然后利用公式，求得所有因子和。

且 $a^b=P_1^{m_1*b}*P_2^{m_2*b}*...*P_n^{m_n*b}$

无奈这道题当时打算用乘法逆元**计算等比数列前n项和**的时候一直WA，于是只能改用递归咯！




## **AC代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define mod 9901

typedef unsigned long long LL;

LL mult(LL a,LL n)
{
    LL ans=1;
    while(n)
    {
        if(n&1)ans=(a*ans)%mod;
        a=(a*a)%mod;
        n>>=1;
    }
    return ans;
}

/* 乘法逆元求解等比数列前n项和：status WA
LL solve(int a,int b)
{
    return ((mult(a,b+1)-1)*mult(a-1,9901-2))%mod;
}*/

LL sum(LL p,LL n)  //等比求和
{
    if(n==0)return 1;
    if(n&1)return ( (1+mult(p,n/2+1)) * sum(p,n/2) ) % mod;
    return ((1+mult(p,n/2+1)) * sum(p,n/2-1) + mult(p,n/2) )% mod;
}

void numberfixed(LL n,LL m)
{
    LL s=1;
    for(LL i=2; i*i<=n; i++)
        if(n%i==0)
        {
            int b=0;
            while(n%i==0)
            {
                b++;
                n/=i;
            }
            s=(s*sum(i,b*m))%mod;
        }
    if(n!=1)
        s=(s*sum(n,m))%mod;
    printf("%I64d\n",s);
}

int main()
{
    LL a,b;
    while(~scanf("%I64d%I64d",&a,&b))
    {
        if(a==0)printf("0\n");
        else numberfixed(a,b);
    }
    return 0;
}
```

