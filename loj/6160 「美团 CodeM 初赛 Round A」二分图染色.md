# 6160. 「美团 CodeM 初赛 Round A」二分图染色

## **题目描述**

> 给定一个完全二分图，图的左右两边的顶点数目相同。我们要把图中的每条边染成红色、蓝色、或者绿色，并使得任意两条红边不共享端点、同时任意两条蓝边也不共享端点。计算所有满足条件的染色的方案数，并对 $10^9+7$ 取模。



## **输入格式**

> 二分图单边的顶点数目 $n$ 。



## **输出格式**

> 输出一个整数，即所求的答案。



## **样例输入**

    2



## **样例输出**

    35



## **思路**

已知红色与蓝色的边存在限制，因此我们只考虑这两种颜色，完全二分图剩下的边置为绿色。

两边不共享端点的问题可以转化为棋盘模型，即在 $n \times n$ 的棋盘上放红蓝棋子，每个格子至多放一次，同行同列的棋子不能同色，显然，对于每一种颜色我们有 $F_n=\sum_{i=0}^nC_n^i\times A_n^i$ 种放置方案。

考虑两种颜色同时存在，此时 $F_n \times F_n$ 中包含这两种颜色同方格的情况，因此我们考虑容斥减掉这部分，最终结果为： $\sum_{i=0}^{n}(-1)^nC_n^iA_n^i(F_{n-i})^2$ 。

---

我们可以通过预处理最终在 $O(1)$ 的时间内求出组合数与排列数，但是对于每一个 $F$ ，我们需要 $O(n)$ 的时间计算，显然对于这道题是不可取的。

我们考虑 $F_n$ 从前一个状态 $F_{n-1}$ 的转移，即在格子的第 $n$ 行的 $n$ 个空中，我们可以染或者不染某一个方格，该方案数为 $2n \times F_{n-1}$ ，但是第 $n$ 行的染色操作可能会与之前 $n-1$ 行中的某个方案冲突，横向 $n-1$ 个格子，纵向 $n-1$ 行，总方案数 $(n-1)^2 \times F_{n-2}$ 。

因此对于 $F_n$ ，我们有了递推公式 $F_n=2n \times F_{n-1}-(n-1)^2 \times F_{n-2}$ ，于是这道题也便可以正确的写出来啦~



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e7 + 10;
const int mod = 1e9 + 7;

LL mul[maxn];
LL inv[maxn];
LL F[maxn];

void init()
{
    mul[0] = 1;
    for (int i = 1; i < maxn; i++)
        mul[i] = (mul[i - 1] * i) % mod;

    inv[0] = inv[1] = 1;
    for (int i = 2; i < maxn; i++)
        inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i < maxn; i++)
        inv[i] = (inv[i - 1] * inv[i]) % mod;

    F[0] = 1;
    F[1] = 2;
    for (int i = 2; i < maxn; i++)
    {
        F[i] = 2LL * i * F[i - 1] % mod - 1LL * (i - 1) * (i - 1) % mod * F[i - 2] % mod;
        F[i] = (F[i] % mod + mod) % mod;
    }
}

LL C(int n, int m)
{
    return mul[n] * inv[m] % mod * inv[n - m] % mod;
}

LL A(int n, int m)
{
    return mul[n] * inv[n - m] % mod;
}

void solve(int n)
{
    LL ans = 0;
    for (int i = 0; i <= n; i++)
    {
        ans += ((i & 1) ? -1LL : 1LL) * C(n, i) * A(n, i) % mod * F[n - i] % mod * F[n - i] % mod;
        ans = (ans % mod + mod) % mod;
    }
    cout << ans << endl;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    IO;
#endif // ONLINE_JUDGE

    init();
    int n;
    while (cin >> n)
        solve(n);
    return 0;
}
```

