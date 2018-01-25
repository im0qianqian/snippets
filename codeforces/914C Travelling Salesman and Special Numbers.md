# C. Travelling Salesman and Special Numbers

## **Description**

> The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer x and reduce it to the number of bits set to 1 in the binary representation of x. For example for number 13 it's true that $13_{10} = 1101_2$ , so it has 3 bits set and 13 will be reduced to 3 in one operation.
>
> He calls a number special if the minimum number of operations to reduce it to 1 is k.
>
> He wants to find out how many special numbers exist which are not greater than n. Please help the Travelling Salesman, as he is about to reach his destination!
>
> Since the answer can be large, output it modulo 10^9 + 7.



## **Input**

> The first line contains integer n (1 ≤ n < 2^1000).
>
> The second line contains integer k (0 ≤ k ≤ 1000).
>
> Note that n is given in its binary representation without any leading zeros.



## **Output**

> Output a single integer — the number of special numbers not greater than n, modulo 10^9 + 7.



## **Examples input**

    110
    2



## **Examples output**

    3



## **题意**

我们定义一种操作为将一个正整数变化为它二进制 1 的个数，问在小于等于给定二进制数的正整数中，有多少个数可以经过 k 次操作变化为 1 。



## **思路**

从题中我们可以看到，一次操作可以将一个数变化为其二进制 1 的个数，于是我们设 dp[i] 表示二进制中有 i 个 1 的数需要几次变化才能到达 1 。

显然 dp[i] = dp[getNum(i)] + 1 ，其中 getNum 可以得出 i 二进制 1 的个数。

对于 dp[i] == k-1 的 i ，接下来的工作便是找出小于等于给定数且二进制 1 的个数为 i 的数的数量，直接用组合数很方便可以求得。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int mod = 1e9+7;
const int maxn = 1e5+10;

char str[maxn];
LL mul[maxn];
LL inv[maxn];
int dp[maxn];
int len,k;

void init()
{
    mul[0]=1;
    for(int i=1; i<maxn; i++)
        mul[i]=(mul[i-1]*i)%mod;

    inv[0]=inv[1]=1;
    for(int i=2; i<maxn; i++)
        inv[i]=(LL)(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1; i<maxn; i++)
        inv[i]=(inv[i-1]*inv[i])%mod;
}

LL C(int n,int m)
{
    return mul[n]*inv[m]%mod*inv[n-m]%mod;
}

int getNum(int x)
{
    int res = 0;
    while(x)
    {
        res+=x&1;
        x>>=1;
    }
    return res;
}

int call(int x)
{
    int res = 0;
    for(int i=0; i<len; i++)
        if(str[i]-'0')
            res = (res + C(len-i-1,x--))%mod;
    return (res + (x==0))%mod;
}

void solve()
{
    len = strlen(str);
    if(k==0)
        cout<<1<<endl;
    else if(k==1)
        cout<<len-1<<endl;
    else
    {
        int ans = 0;
        for(int i=2; i<=1000; i++)
        {
            dp[i] = dp[getNum(i)] + 1;
            if(dp[i]==k-1)
                ans = (ans + call(i)) % mod;
        }
        cout<<ans<<endl;
    }
}

int main()
{
    IO;
    init();
    cin>>str>>k;
    solve();
    return 0;
}
```

