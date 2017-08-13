# D. Winter is here

## **Description**

> Winter is here at the North and the White Walkers are close. John Snow has an army consisting of n soldiers. While the rest of the world is fighting for the Iron Throne, he is going to get ready for the attack of the White Walkers.
>
> He has created a method to know how strong his army is. Let the i-th soldier’s strength be ai. For some k he calls i1, i2, ..., ik a clan if i1 < i2 < i3 < ... < ik and gcd(ai1, ai2, ..., aik) > 1 . He calls the strength of that clan k·gcd(ai1, ai2, ..., aik). Then he defines the strength of his army by the sum of strengths of all possible clans.
>
> Your task is to find the strength of his army. As the number may be very large, you have to print it modulo 1000000007 (10^9 + 7).
>
> Greatest common divisor (gcd) of a sequence of integers is the maximum possible integer so that each element of the sequence is divisible by it.



## **Input**

> The first line contains integer n (1 ≤ n ≤ 200000) — the size of the army.
>
> The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 1000000) — denoting the strengths of his soldiers.



## **Output**

> Print one integer — the strength of John Snow's army modulo 1000000007 (10^9 + 7).



## **Example input**

    4
    2 3 4 6



## **Example output**

    39



## **题意**

给出一个序列，求其中所有 $\gcd$ 大于 1 的子序列乘以序列长度之和。



## **思路**

题意转化为公式即 $\sum k×\gcd(a_1,a_2,...,a_k)$ （其中 $\gcd$ 大于 1）

等价于 $\sum_{d=2}^{max}d×\sum k×[\gcd(a_1,a_2,...,a_k)=d]$

我们设 $f(x)=\sum k×[gcd(a_1,a_2,...,a_k)=x]$

设 $F(x)=\sum_{x|d}f(d)$ ，它也代表我们从整个数列所有 $x$ 的倍数中挑选 $k$ 个组成的情况，因此我们设 $v$ 为数列中 $x$ 倍数的个数，则结果为 $1×C_v^1+2×C_v^2+...+v×C_v^v$ ，即 $v×2^{v-1}$ 。

反演以后得到 $f(x)=\sum_{x|d}μ(\frac{d}{x})F(d)$ ，最终结果 $ans=\sum_{d=2}^{max}d×f(d)$ 。

---

考虑枚举每一个 $\gcd​$ ，找出序列中所有包含该因子的数有 $V_{gcd}​$ 个，则此时该数对结果的贡献为 $V_{gcd}×2^{V_{gcd}-1}-S​$ ，其中 $S​$ 为其所有倍数所带来的贡献。

最终结果 $ans=\sum_{d=2}^{max}d×(V_{d}×2^{V_{d}-1}-S)$ 



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

const int mod = 1e9+7;
const int maxn = 1e6+10;
LL sk[maxn],b[maxn],z[maxn];

void solve()
{
    LL ans=0;
    for (int i=2; i<=maxn; i++)
    {
        LL v=0;
        for (int j=i; j<=maxn; j+=i)
            v+=sk[j];
        if (!v) continue;
        ans += (v * z[i]) % mod * b[v-1] % mod;
    }
    cout << (ans+mod)%mod << endl;
}

void init()
{
    b[0]=1;
    for (int i=1; i<=maxn; i++)
        b[i]=b[i-1]*2%mod,z[i]=i;
    for (int i=2; i<=maxn; i++)
        for (int j=i+i; j<=maxn; j+=i)
            z[j]-= z[i];
}

int main()
{
    init();
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n)
    {
        memset(sk,0,sizeof(sk));
        for (int i=1,x; i<=n; i++)
        {
            cin>>x;
            sk[x]++;
        }
        solve();
    }
    return 0;
}
```

