# E. New Year and the Acquaintance Estimation

## **Description**

> Bob is an active user of the social network Faithbug. On this network, people are able to engage in a mutual friendship. That is, if a is $a$ friend of $b$, then $b$ is also a friend of $a$. Each user thus has a non-negative amount of friends.
>
> This morning, somebody anonymously sent Bob the following link: graph realization problem and Bob wants to know who that was. In order to do that, he first needs to know how the social network looks like. He investigated the profile of every other person on the network and noted down the number of his friends. However, he neglected to note down the number of his friends. Help him find out how many friends he has. Since there may be many possible answers, print all of them.



## **Input**

> The first line contains one integer $n$ $(1≤n≤5⋅10^5)$, the number of people on the network excluding Bob.
>
> The second line contains $n$ numbers $a_1,a_2,…,a_n$ $(0≤a_i≤n)$, with $a_i$ being the number of people that person $i$ is a friend of.



## **Output**

> Print all possible values of $a_{n+1}$ — the amount of people that Bob can be friend of, in increasing order.
>
> If no solution exists, output $−1$.



## **Examples input**

    4
    1 1 1 1



## **Examples output**

    0 2 4 



## **题意**

在一个具有 $n+1$ 个点的无向图中，给出其中 $n$ 个点的度，问最后一个点可能的度的大小有哪些？



## **思路**

根据 [Erdős–Gallai theorem](https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem) 我们很容易知道最后一个点度的奇偶性。

且对于一个合法的度数，有
$$
\sum_{i=1}^{k}d_i\leq k(k-1)+\sum_{i=k+1}^{n}\min(d_i,k)
$$
成立，其中 $d_1\geq\dots\geq d_n$, $1\leq k\leq n$

---

我们假设 $x$ 为满足题意最小可能的答案，假设图中存在边 $u-v$ ，我们可以保证不改变图中其他点度的情况下将这条边更改为 $u-k$, $k-v$ ，显然点 $k$ 的度增加了 $2$，且这种方法适用于其他所有边，因此答案 $x$ 是连续的且具有相同的奇偶性。

仔细观察上面的式子我们可以发现，每个点的度 $d_i$ 不可能同时对式子左右两端都产生贡献，因此考虑二分寻找合法的边界。

假设当前二分值 $mid$ 在排序后的度序列的位置为 $pos$ ，枚举 $k$ ，显然当第一个不合法的位置 $k$ 在 $pos$ 之前，则说明 $mid$ 太小（此时 $mid$ 对 $\sum_{i=k+1}^{n}\min(d_i,k)$ 有贡献），否则 $mid$ 太大（此时对 $\sum_{i=1}^{k}d_i$ 有贡献）。

---

从没有想过题目的答案居然在题面里 QAQ



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 5e5 + 10;

int a[maxn];
int b[maxn];
int n, parity;

int judge(int mid) {
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; i++)
        ++b[a[i]];
    ++b[mid];
    LL left = 0, right = 0, les = 0;
    for (int i = 0, k = 0; k <= n; k++) {
        int now = (i == k && (i == n || a[i] < mid)) ? mid : a[i++];
        left += now;
        --b[now];
        les += b[k];
        right += n - k - les - min(now, k);
        if (left > right + 1LL * k * (k + 1))
            return i == k ? 1 : -1;
    }
    return 0;
}

bool solve() {
    sort(a, a + n, greater<int>());
    int low = 0, high = (n - parity) >> 1;
    int alow = -1, ahigh = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (judge(mid * 2 + parity) == -1)
            low = mid + 1;
        else
            high = mid - 1, alow = mid;
    }
    low = alow, high = (n - parity) >> 1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (judge(mid * 2 + parity) == 1)
            high = mid - 1;
        else
            low = mid + 1, ahigh = mid;
    }
    if (alow == -1 || ahigh == -1)
        return false;
    for (int i = alow; i <= ahigh; i++)
        cout << i * 2 + parity << " ";
    cout << endl;
    return true;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    while (cin >> n) {
        parity = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            parity ^= a[i];
        }
        parity &= 1;
        if (!solve())
            cout << "-1" << endl;
    }
    return 0;
}

```

