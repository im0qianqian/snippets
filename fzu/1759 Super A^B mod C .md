# 1759 Super A^B mod C 

## **Description**

> Given A,B,C, You should quickly calculate the result of A^B mod C. (1<=A,C<=1000000000,1<=B<=10^1000000).



## **Input**

> There are multiply testcases. Each testcase, there is one line contains three integers A, B and C, separated by a single space.



## **Output**

> For each testcase, output an integer, denotes the result of A^B mod C.



## **Sample Input**

    3 2 4
    2 10 1000



## **Sample Output**

    1
    24



## **思路**

一道指数非常可怕的题目，显然快速幂是无法直接求解的，这里我们需要用到降幂。

$A^Bmod~C=A^{B~mod~\phi(C)+\phi(C)}mod~C$ ，当且仅当 $B>=\phi(C)$ 时公式成立，这时我们采用降幂处理，其他情况直接快速幂求解。

$\phi$ 代表欧拉函数。



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn = 1e6+10;
typedef __int64 LL;
LL pr[maxn],a,c;
bool prime[maxn];
char b[maxn];

void getprime()         //筛法素数表
{
    int i,j,k=0;
    memset(prime,true,sizeof(prime));
    for(i=2; i<maxn; i++)
    {
        if(prime[i])
        {
            pr[k++]=i;
            for(j=i+i; j<maxn; j+=i)
                prime[j]=false;
        }
    }
}

LL phi(LL n)      //求欧拉函数
{
    LL rea=n;
    for(int i=0; pr[i]*pr[i]<=n; i++)
    {
        if(n%pr[i]==0)
        {
            rea=rea-rea/pr[i];
            while(n%pr[i]==0)
                n/=pr[i];
        }
    }
    if(n>1)
        rea=rea-rea/n;
    return rea;
}

LL mult(LL a,LL b,LL mod)
{
    LL res = 1;
    a%=mod;
    while(b)
    {
        if(b&1)res = (res*a)%mod;
        a = (a*a)%mod;
        b>>=1;
    }
    return res;
}

void solve()
{
    LL ph = phi(c);
    a%=c;
    int len = strlen(b);
    if(len>LL(log10(ph)))
    {
        LL res = 0;
        for(int i=0; i<len; i++)
            res = (res * 10 + b[i] - '0')%ph;
        printf("%I64d\n",mult(a,res + ph,c));
    }
    else
    {
        LL mb;
        sscanf(b,"%I64d",&mb);
        printf("%I64d\n",mult(a,mb,c));
    }
}

int main()
{
    getprime();
    while(~scanf("%I64d%s%I64d",&a,b,&c))
        solve();
    return 0;
}
```