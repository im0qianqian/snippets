# TrickGCD

## **Description**

> You are given an array $A$ , and Zhu wants to know there are how many different array $B$ satisfy the following conditions?
>
> - $1≤B_i≤A_i$
> - For each pair(l,r) $(1≤l≤r≤n)$ , $gcd(b_l,b_{l+1}...b_r)≥2$



## **Input**

> The first line is an integer $T(1≤T≤10)$ describe the number of test cases.
>
> Each test case begins with an integer number n describe the size of array $A$ .
>
> Then a line contains n numbers describe each element of $A$
>
> You can assume that $1≤n,A_i≤10^5$



## **Output**

> For the kth test case , first output "Case #k: " , then output an integer as answer in a single line . because the answer may be large , so you are only need to output answer $mod~10^9+7$



## **Sample Input**

    1
    4
    4 4 4 4



## **Sample Output**

    Case #1: 17


## **题意**

给出数组 $A$ ，问有多个种 $B$ 数组满足所给条件。



## **思路**

针对条件，我们可以枚举 $\gcd$ ，显然对于每一个素因子 $i$ 在范围 $[i,j]$ 下共有 $\frac{j}{i}$ 个数可以整除它，假设 $A$ 中共有 $cnt$ 个数字处于 $[j,j+i-1]$ 这个范围内，这也就相当于有 $cnt$ 个位置的数可以在 $\frac{j}{i}$ 个因子中随意变动，共有 $(\frac{j}{i})^{cnt}$ 种方案，而对于每一个因子，其结果为 $\sum_{i|j}(\frac{j}{i})^{cnt}$ 。

最终通过容斥或者莫比乌斯去掉重复部分即可。



## **AC 代码**

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include<iostream>
using namespace std ;

#define inf 0x3f3f3f
typedef __int64 LL;
const int maxn = 1e5+10;
const int mod = 1e9+7;
LL mu[maxn];
LL sum[maxn<<1];
LL cnt[maxn<<1];

void init()
{
    mu[1]=1;
    for(int i=1; i<maxn; i++)
        for(int j=i+i; j<maxn; j+=i)
            mu[j]-=mu[i];
}

LL mult(LL a,LL n)
{
    LL res=1;
    while(n)
    {
        if(n&1)res=(res*a)%mod;
        a=(a*a)%mod;
        n>>=1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int T;
    cin>>T;
    for(int ti=1; ti<=T; ti++)
    {
        int n,minn=inf;
        memset(cnt,0,sizeof(cnt));
        cin>>n;
        for(int i=0; i<n; i++)
        {
            int x;
            cin>>x;
            cnt[x]++;
            minn=min(minn,x);
        }
        LL ans=0;
        for(int i=1; i<maxn*2; i++)
            sum[i]=sum[i-1]+cnt[i];
        for(int i=2; i<=minn; i++)
        {
            LL temp=1LL;
            if(mu[i])
            {
                for(int j=i; j<maxn; j+=i)
                    temp=(temp*mult(j/i,sum[j+i-1]-sum[j-1]))%mod;
            }
            ans=(ans-temp*mu[i]+mod)%mod;
        }
        cout<<"Case #"<<ti<<": "<<ans<<endl;
    }
    return 0;
}
```

