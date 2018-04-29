# G. Xor-matic Number of the Graph

## **Description**

> You are given an undirected graph, constisting of n vertices and m edges. Each edge of the graph has some non-negative integer written on it.
>
> Let's call a triple (u, v, s) interesting, if 1 ≤ u < v ≤ n and there is a path (possibly non-simple, i.e. it can visit the same vertices and edges multiple times) between vertices u and v such that xor of all numbers written on the edges of this path is equal to s. When we compute the value s for some path, each edge is counted in xor as many times, as it appear on this path. It's not hard to prove that there are finite number of such triples.
>
> Calculate the sum over modulo 10^9 + 7 of the values of s over all interesting triples.



## **Input**

> The first line of the input contains two integers n and m (1 ≤ n ≤ 100 000, 0 ≤ m ≤ 200 000) — numbers of vertices and edges in the given graph.
>
> The follow m lines contain three integers ui, vi and ti (1 ≤ ui, vi ≤ n, 0 ≤ ti ≤ 10^18, ui ≠ vi) — vertices connected by the edge and integer written on it. It is guaranteed that graph doesn't contain self-loops and multiple edges.



## **Output**

> Print the single integer, equal to the described sum over modulo 10^9 + 7.



## **Examples input**

    4 4
    1 2 1
    1 3 2
    2 3 3
    3 4 1



## **Examples output**

    12



## **题意**

给出一个无向图，求所有的三元组 $(u,v,s)$ 的 $s$ 之和，其中 $s$ 表示 $u$ 到 $v$ 路径的异或和。



## **思路**

图中可能存在多个联通块，我们要对每一部分分别进行处理。

考虑 $s$ 的每一位对结果的贡献，其中第 $i$ 位为 $1$ 对结果的贡献为 $2^i$ ，为 $0$ 对结果的贡献为 $0$ 。

我们用 $dis_i$ 代表从根到节点 $i$ 路径的异或和，则 $u->v$ 路径的异或和为 $dis_u\oplus dis_v$ 

我们知道，$u->v$ 这条路中所有可能的异或值等于他们之间随意一条路的异或值再异或所有可能访问到的环的异或值，因此在 $dfs$ 的过程中我们需要用所有环的异或值来建立线性基，假设当前所构建的线性基大小为 $lbSize$。

对于一条异或值为 $s$ 的路径来说，枚举第 $i$ 位，有两种情况：

1. $s$ 的第 $i$ 位为 $0$
   - 如果线性基中不存在当前位为 $1$ 的元素显然我们无法把它变为 $1$ ，因此这种情况对结果无贡献
   - 如果线性基中存在当前位为 $1$ 的元素，我们可以从中任意组合最多选取 $lbSize-1$ 个元素，而最后那一个元素的选取是固定的（因为总要把当前位改变为 $1$ ），因此共有 $2^{lbSize-1}$ 种取法
2. $s$ 的第 $i$ 位为 $1$
   - 如果线性基中不存在当前位为 $1$ 的元素，即我们无法改变 $1$ 的这一个状态，因此共有 $2^{lbSize}$ 种取法
   - 如果线性基中存在当前位为 $1$ 的元素，同上我们可以任意组合最多选取 $lbSize-1$ 个元素，最后的那一个元素选取也是固定的，因此共有 $2^{lbSize-1}$ 种取法

一种优化的办法是我们只需要统计此次 $dfs$ 遇到所有点的 $dis$ 当前位状态的数量（零和一的个数）

- 我们知道 $00$ 和 $11$ 的异或结果为 $0$ ，即 $u->v$ 这条路径上所有可能的 $s$ 当前位为 $0$ 的情况数共有 $\binom{cnt_0}{2}+\binom{cnt_1}{2}$ 种
- 同理，$u->v$ 这条路径所有可能的 $s$ 当前位为 $1$ 的情况数共有 $cnt_0\times cnt_1$ 种



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;

struct node {
    int from;
    int to;
    int next;
    LL cost;
} edge[maxn << 1];
int head[maxn], tot;
LL two[maxn], dis[maxn];
bool vis[maxn];
vector<int> stk;

void init() {
    memset(head, -1, sizeof(head));
    memset(vis, false, sizeof(vis));
    tot = 0;
    two[0] = 1;
    for (int i = 1; i < maxn; i++) {
        two[i] = two[i - 1] * 2 % mod;
    }
}

void addedge(int u, int v, LL cost) {
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].cost = cost;
    edge[tot].next = head[u];
    head[u] = tot++;
}

class LinearBase {
public:
    const static int maxn = 64 - 1;
    LL d[maxn], p[maxn], tot;
    void clear() {
        tot = 0;
        memset(d, 0, sizeof(d));
        memset(p, 0, sizeof(p));
    }

    bool insert(LL val) {
        for (int i = maxn - 1; i >= 0; i--) {
            if ((val >> i) & 1) {
                if (!d[i]) {
                    d[i] = val;
                    break;
                } else {
                    val ^= d[i];
                }
            }
        }
        return val > 0;
    }

    LL query_max(LL def = 0) {
        LL res = def;
        for (int i = maxn - 1; i >= 0; i--) {
            res = max(res, res ^ d[i]);
        }
        return res;
    }

    LL query_min() {
        for (int i = 0; i < maxn; i++) {
            if (d[i])
                return d[i];
        }
        return 0;
    }

    void rebuild() {
        memset(p, 0, sizeof(p));
        tot = 0;
        for (int i = maxn - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if ((d[i] >> j) & 1) {
                    d[i] ^= d[j];
                }
            }
        }
        for (int i = 0; i < maxn; i++) {
            if (d[i]) {
                p[tot++] = d[i];
            }
        }
    }

    LL query_kth(LL k) {
        if (k >= 1LL << tot) {
            return -1;
        }
        LL res = 0;
        for (int i = 0; i < maxn; i++) {
            if ((k >> i) & 1) {
                res ^= p[i];
            }
        }
        return res;
    }

} lb;

void dfs(int x, LL cost) {
    vis[x] = true;
    dis[x] = cost;
    stk.push_back(x);
    for (int i = head[x]; i != -1; i = edge[i].next) {
        int to = edge[i].to;
        if (vis[to]) {
            lb.insert(cost ^ edge[i].cost ^ dis[to]);
        } else
            dfs(to, cost ^ edge[i].cost);
    }
}

LL fac(LL x) { return x * (x - 1) / 2 % mod; }

LL call() {
    int lbSize = 0;
    LL res = 0, cnt[2];
    for (int i = 0; i < lb.maxn; i++) { // 计算线性基元素的总数
        if (lb.d[i])
            ++lbSize;
    }
    for (int i = 0; i < lb.maxn; i++) {
        bool flag = false;
        cnt[0] = cnt[1] = 0;
        for (int j = 0; j < lb.maxn;
             j++) { // 判断线性基元素当前这一位中是否有 1
            if ((lb.d[j] >> i) & 1) {
                flag = true;
                break;
            }
        }
        for (auto s : stk) { // 统计该次 dfs 结果中第 i 位 01 的分布
            ++cnt[(dis[s] >> i) & 1];
        }
        LL now = (fac(cnt[0]) + fac(cnt[1])) %
                 mod; // 选择 00 与 11 的两个点（需要组合算出）
        if (flag) {
            now *= two[i] * two[lbSize - 1] % mod;
            now %= mod;
            res = (res + now) % mod;
        }
        now = cnt[0] * cnt[1] % mod; // 选择 01 这种情况的点
        if (flag) {
            now *= two[i] * two[lbSize - 1] % mod;
            now %= mod;
        } else {
            now *= two[i] * two[lbSize] % mod;
            now %= mod;
        }
        res = (res + now) % mod;
    }
    return res;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN
    init();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        LL u, v, cost;
        cin >> u >> v >> cost;
        addedge(u, v, cost);
        addedge(v, u, cost);
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            lb.clear();
            stk.clear();
            dfs(i, 0);
            ans = (ans + call()) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}
```

