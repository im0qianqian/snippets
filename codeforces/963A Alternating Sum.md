# A. Alternating Sum

## **Description**

> You are given two integers $a$ and $b$. Moreover, you are given a sequence $s_0, s_1, \dots, s_{n}$. All values in $s$ are integers $1$ or $-1$. It's known that sequence is $k$-periodic and $k$ divides $n+1$. In other words, for each $k \leq i \leq n$ it's satisfied that $s_{i} = s_{i - k}$.
>
> Find out the non-negative remainder of division of $\sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i}$ by $10^{9} + 9$.
>
> Note that the modulo is unusual!



## **Input**

> The first line contains four integers $n, a, b$ and $k$ $(1 \leq n \leq 10^{9}, 1 \leq a, b \leq 10^{9}, 1 \leq k \leq 10^{5})$.
>
> The second line contains a sequence of length $k$ consisting of characters '+' and '-'.
>
> If the $i$-th character (0-indexed) is '+', then $s_{i} = 1$, otherwise $s_{i} = -1$.
>
> Note that only the first $k$ members of the sequence are given, the rest can be obtained using the periodicity property.



## **Output**

> Output a single integer — value of given expression modulo $10^{9} + 9$.



## **Examples input**

    2 2 3 3
    +-+



## **Examples output**

    7



## **题意**

给定数据 $n, a, b, k$ 以及 $s$ ，求解公式的结果。



## **思路**

因为 $s$ 中每 $k$ 段是一样的，于是原公式便等价于一个公比为 $a^{-k}b^k$ 的等比数列前 $(n+1)/k$ 项和。

配合逆元求解即可。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
const int mod = 1e9 + 9;

LL a, b, n, k;
char str[maxn];
LL mult(LL a, LL n) {
    LL ans = 1;
    while (n) {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

void solve() {
    LL ans = 0, res = 0;
    LL inva = mult(a, mod - 2);
    LL pw = mult(a, n);
    LL lun = (n + 1) / k;
    for (int i = 0; i < k; i++) {
        res += (str[i] == '+' ? 1 : -1) * pw % mod;
        res %= mod;
        pw = pw * inva % mod * b % mod;
    }
    LL q = mult(inva, k) * mult(b, k) % mod;
    if (q == 1) {
        ans = res * lun % mod;
    } else {
        LL di = mult((q - 1 + mod) % mod, mod - 2);
        LL de = (mult(q, lun) - 1 + mod) % mod;
        ans = res * de % mod * di % mod;
    }
    ans = ((ans % mod) + mod) % mod;
    cout << ans << endl;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    IO;
#endif // ONLINE_JUDGE

    cin >> n >> a >> b >> k;
    cin >> str;
    solve();
    return 0;
}
```

