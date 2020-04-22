# D. Constant Palindrome Sum

## Description

> You are given an array $a$ consisting of $n$ integers (it is guaranteed that $n$ is even, i.e. divisible by $2$). All $a_i$ does not exceed some integer $k$.
>
> Your task is to replace the **minimum** number of elements (replacement is the following operation: choose some index $i$ from $1$ to $n$ and replace $a_i$ with some integer in range $[1,k]$) to satisfy the following conditions:
>
> - after all replacements, all $a_i$ are positive integers not greater than $k$.
> - for all $i$ from $1$ to $\frac{n}{2}$ the following equation is true: $a_i + a_{n - i + 1} = x$, where $x$ should be **the same** for all $\frac{n}{2}$ pairs of elements.
> - You have to answer $t$ independent test cases.



## Input

> The first line of the input contains one integer $t$ $(1\le t \le 10^4)$ — the number of test cases. Then $t$ test cases follow.
>
> The first line of the test case contains two integers $n$ and $k$ $(2 \le n \le 2 \cdot 10^5, 1 \le k \le 2 \cdot 10^5)$ — the length of $a$ and the maximum possible value of some $a_i$ correspondingly. It is guratanteed that $n$ is even (i.e. divisible by $2$). The second line of the test case contains $n$ integers $a_1, a_2, \dots, a_n$ $(1 \le a_i \le k)$, where $a_i$ is the $i$-th element of $a$.
>
> It is guaranteed that the sum of $n$ (as well as the sum of $k$) over all test cases does not exceed $2 \cdot 10^5$ ($\sum n \le 2 \cdot 10^5$, $\sum k \le 2 \cdot 10^5$).



## Output

> For each test case, print the answer — the **minimum** number of elements you have to replace in $a$ to satisfy the conditions from the problem statement.



## Example input

    4
    4 2
    1 2 1 2
    4 3
    1 2 2 1
    8 7
    6 1 1 7 6 3 4 6
    6 6
    5 2 6 1 3 4



## Example output

    0
    1
    4
    2



## 题意

给定一个有 $n$ 个元素的数组 $a$，有一个操作是将 $a$ 中的任意一个元素替换为 $[1, k]$ 之间的任意一个数。

问，最少多少次操作可以让所有的 $a[i] + a[n-i-1] = x$。



## 思路

我们考虑每一对 $a[i]$ 与 $a[n-i-1]$，有三种情况：

1. 此时 $a[i] + a[n-i-1]=x$，则在这对中不需要操作
2. 每一对中最多操作一次的情况下，和的范围是 $[\min(a[i], a[n-i-1]) + 1,\max(a[i], a[n-i-1]) + k]$
3. 每一对中最多操作两次的情况下，和的范围是 $[2, k+k]$

既然有了这些信息，遍历所有的『对』，将它可组合出每种的和所需要的花费维护起来。

最后在 $[2,k+k]$ 范围内遍历 $x$ 找最小花费的点即可。

维护的操作可以用线段树、差分数组或者树状数组做。



## AC 代码

### 差分数组

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
typedef pair<int, int> P;
const int maxn = 4e5 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;

int n, k;
int a[maxn];
int cnt[maxn];
void solve() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n / 2; i++) {
        int x = a[i];
        int y = a[n - i - 1];
        int line1 = min(x, y) + 1;
        int line2 = max(x, y) + k;
        cnt[2] += 2; // 最多两次操作的情况，花费 2
        cnt[k + k + 1] -= 2;
        cnt[line1] += -1; // 最多一次的情况，从 2 中 -1
        cnt[line2 + 1] -= -1;
        cnt[x + y] += -1; // 不操作的情况，再 -1
        cnt[x + y + 1] -= -1;
    }
    int ans = INT_MAX;
    for (int i = 2; i <= k + k; i++) {
        cnt[i] += cnt[i - 1];
        ans = min(cnt[i], ans);
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

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        solve();
    }
    return 0;
}
```



### 线段树

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
typedef pair<int, int> P;
const int maxn = 4e5 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;
#define default_setv -1
int sumv[maxn << 2]; //四倍空间
int minv[maxn << 2];
int maxv[maxn << 2];
int addv[maxn << 2];
int setv[maxn << 2]; //初始值：-1
int a[maxn];

void maintain(int o, int L, int R) {
    int lc = o << 1, rc = o << 1 | 1;
    sumv[o] = minv[o] = maxv[o] = 0;
    if (setv[o] != default_setv) {
        sumv[o] = setv[o] * (R - L + 1);
        minv[o] = maxv[o] = setv[o];
    } else if (R > L) {
        sumv[o] = sumv[lc] + sumv[rc];
        minv[o] = min(minv[lc], minv[rc]);
        maxv[o] = max(maxv[lc], maxv[rc]);
    }
    minv[o] += addv[o];
    maxv[o] += addv[o];
    sumv[o] += addv[o] * (R - L + 1);
}

void pushdown(int o) {
    int lc = o << 1, rc = o << 1 | 1;
    if (setv[o] != default_setv) {
        setv[lc] = setv[rc] = setv[o];
        addv[lc] = addv[rc] = 0;
        setv[o] = default_setv;
    }
    if (addv[o] != 0) {
        addv[lc] += addv[o];
        addv[rc] += addv[o];
        addv[o] = 0;
    }
}

/*
 * o: 当前节点(1)，修改区间：[y1,y2] ，添加值：v_add，总区间：[L,R]
 * (这里的L,R必须是2的幂次)
 */
void update_add(int o, int L, int R, int y1, int y2, int v_add) {
    int lc = o << 1, rc = o << 1 | 1;
    if (y1 <= L && y2 >= R)
        addv[o] += v_add;
    else {
        pushdown(o);
        int M = L + (R - L) / 2;
        if (y1 <= M)
            update_add(lc, L, M, y1, y2, v_add);
        else
            maintain(lc, L, M);
        if (y2 > M)
            update_add(rc, M + 1, R, y1, y2, v_add);
        else
            maintain(rc, M + 1, R);
    }
    maintain(o, L, R);
}

/*
 * o: 当前节点(1)，修改区间：[y1,y2] ，修改值：v_set，总区间：[L,R]
 * (这里的L,R必须是2的幂次)
 */
void update_set(int o, int L, int R, int y1, int y2, int v_set) {
    int lc = o << 1, rc = o << 1 | 1;
    if (y1 <= L && y2 >= R) {
        setv[o] = v_set;
        addv[o] = 0;
    } else {
        pushdown(o);
        int M = L + (R - L) / 2;
        if (y1 <= M)
            update_set(lc, L, M, y1, y2, v_set);
        else
            maintain(lc, L, M);
        if (y2 > M)
            update_set(rc, M + 1, R, y1, y2, v_set);
        else
            maintain(rc, M + 1, R);
    }
    maintain(o, L, R);
}

/*
 * o: 当前节点(1)，查询区间：[y1,y2] ，初始累加(0)，总区间：[L,R]
 * (这里的L,R必须是2的幂次)
 */
int _min, _max, _sum;
void query(int o, int L, int R, int y1, int y2, int add) {
    if (setv[o] != default_setv) {
        _sum += (add + setv[o] + addv[o]) * (min(R, y2) - max(L, y1) + 1);
        _min = min(_min, setv[o] + addv[o] + add);
        _max = max(_max, setv[o] + addv[o] + add);
    } else if (y1 <= L && y2 >= R) {
        _sum += sumv[o] + add * (R - L + 1);
        _min = min(_min, minv[o] + add);
        _max = max(_max, maxv[o] + add);
    } else {
        int M = L + (R - L) / 2;
        if (y1 <= M)
            query(o * 2, L, M, y1, y2, add + addv[o]);
        if (y2 > M)
            query(o * 2 + 1, M + 1, R, y1, y2, add + addv[o]);
    }
}

/*
 * o: 当前节点(1)，总区间：[L,R] (这里的L,R必须是2的幂次)
 * 所有 setv 初始化为 -1，所有叶子节点 addv 为当前值
 */
void build(int o, int L, int R) {
    if (L == R) {
        setv[o] = default_setv;
        addv[o] = sumv[o] = maxv[o] = minv[o] = a[L];
    } else {
        int M = L + (R - L) / 2;
        int lc = o << 1, rc = o << 1 | 1;
        build(lc, L, M);
        build(rc, M + 1, R);

        addv[o] = 0;
        setv[o] = default_setv;
        sumv[o] = sumv[lc] + sumv[rc];
        maxv[o] = max(maxv[lc], maxv[rc]);
        minv[o] = min(minv[lc], minv[rc]);
    }
}

/*
 * 测试函数，R 代表叶子节点个数
 */
void test(int R, int n) {
    cout << "----------" << endl;
    auto init = [&]() {
        _sum = 0;
        _min = INT_MAX;
        _max = INT_MIN;
    };
    for (int i = 1; i <= n; i++) {
        init();
        query(1, 1, R, i, i, 0);
        cout << i << " --> " << _sum << "\t " << _min << "\t " << _max << endl;
    }
    init();
    query(1, 1, R, 1, R, 0);
    cout << "total: " << _sum << endl;
    cout << "----------" << endl;
}

int n, k, R;
void solve() {
    map<int, int> cnt;
    for (int i = 0; i < n / 2; i++) {
        cnt[a[i] + a[n - i - 1]]++;
        int x = a[i];
        int y = a[n - i - 1];
        int line1 = max(x, y) + k;
        int line2 = min(x, y) + 1;
        update_add(1, 1, R, line2, line1, 1);
        update_add(1, 1, R, x + y, x + y, -1);
        if (line1 < k + k)
            update_add(1, 1, R, line1 + 1, k + k, 2);
        if (line2 > 2)
            update_add(1, 1, R, 2, line2 - 1, 2);
    }
    _min = INT_MAX;
    query(1, 1, R, 2, k + k, 0);
    cout << _min << endl;
}
int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        memset(a, 0, sizeof(a));
        R = 1;
        while (R < k + k)
            R <<= 1;
        build(1, 1, R);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        solve();
    }
    return 0;
}
```

