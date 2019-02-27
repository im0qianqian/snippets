# D. Jongmah

## **Description**

> You are playing a game of Jongmah. You don't need to know the rules to solve this problem. You have $n$ tiles in your hand. Each tile has an integer between $1$ and $m$ written on it.
>
> To win the game, you will need to form some number of triples. Each triple consists of three tiles, such that the numbers written on the tiles are either all the same or consecutive. For example, 7,7,7 is a valid triple, and so is 12,13,14, but 2,2,3 or 2,4,6 are not. You can only use the tiles in your hand to form triples. Each tile can be used in at most one triple.
>
> To determine how close you are to the win, you want to know the maximum number of triples you can form from the tiles in your hand.



## **Input**

> The first line contains two integers integer $n$ and $m$ $(1 \le n,m \le 10^6)$ — the number of tiles in your hand and the number of tiles types.
>
> The second line contains integers $a_1,a_2,…,a_n$ $(1 \le a_i \le m)$, where $a_i$ denotes the number written on the $i$-th tile.



## **Output**

> Print one integer: the maximum number of triples you can form.



## **Examples input**

    10 6
    2 3 3 3 4 4 4 5 5 6



## **Examples output**

    3



## **题意**

寻找最多有多少个不重叠的三元组 $<a,b,c>$ 满足 $a=b=c$ 或者 $a+1=b=c-1$。



## **思路**

首先我们考虑这样一个问题，假如 $a, b, c$ 三种数字连续且其个数都大于 $3$，那么我们在组合满足题意的三元组时，三个 $<a,b,c>$ 可以使用 $<a,a,a>,<b,b,b>,<c,c,c>$ 来代替，也就是说，每一段区间中连续的像 $<a,b,c>$ 这样的组合我们可以将其数量控制在 $3$ 以内

设 $dp[i][j][k]$ 代表以数字 $i$ 结尾且满足存在 $j$ 个三元组 $<i-1,i,i+1>$ 以及 $k$ 个三元组 $<i,i+1,i+2>​$ 的情况下所取得的最优解

显然，数字 $i+1$ 的解可以由 $i$ 推来，设 $l$ 代表三元组 $<i-1,i,i+1>$ 的数目，$j$ 代表三元组 $<i,i+1,i+2>$ 的数目，$k$ 代表三元组 $<i+1,i+2,i+3>$ 的数目

那么我们有 $dp[i + 1][j][k] = \max(dp[i + 1][j][k], dp[i][l][j] + j + (a[i + 1] - l - j - k) / 3)​$

其中，$dp[i][l][j]$ 为前一个状态，$+j$ 代表加上三元组 $<i,i+1,i+2>$ 的数目，而后面的 $(a[i + 1] - l - j - k) / 3$ 则代表使用剩余的数字 $i+1$ 来凑成类似于 $<a,a,a>$ 这样的三元组数目

**注意：记得判断每种数字的数量是否可以满足分别构成 $l,j,k$ 个三元组的要求**

最终的结果便是 $dp​$ 数组中的最大值



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
#define mem(a, x) memset(a, x, sizeof(a))
#define per(x, a, b) for (int x = a; x <= b; x++)
#define rep(x, a, b) for (int x = a; x >= b; x--)

using namespace std;
typedef long long LL;
typedef pair<int, pair<int, int>> P;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;

int n, m;
int a[maxn];

LL dp[maxn][3][3];

void solve() {
    mem(dp, 0);
    LL ans = 0;
    for (int i = 0; i < 3; i++) {
        if (min({a[1], a[2], a[3]}) < i)
            continue;
        dp[1][0][i] = (a[1] - i) / 3;
        ans = max(ans, dp[1][0][i]);
    }
    for (int i = 1; i < maxn - 5; i++) {
        for (int l = 0; l < 3; l++) {         // a[i]
            for (int j = 0; j < 3; j++) {     // a[i+1]
                for (int k = 0; k < 3; k++) { // a[i+2]
                    if (a[i - 1] < l || a[i] < l + j || a[i + 1] < l + j + k ||
                        a[i + 2] < j + k || a[i + 3] < k)
                        continue;
                    dp[i + 1][j][k] =
                        max(dp[i + 1][j][k],
                            dp[i][l][j] + j + (a[i + 1] - l - j - k) / 3);
                    ans = max(ans, dp[i + 1][j][k]);
                }
            }
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    while (cin >> n >> m) {
        mem(a, 0);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[x]++;
        }
        solve();
    }
    return 0;
}
```

