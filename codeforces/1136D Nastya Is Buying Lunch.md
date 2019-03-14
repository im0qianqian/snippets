# D. Nastya Is Buying Lunch

## **Description**

> At the big break Nastya came to the school dining room. There are n pupils in the school, numbered from $1$ to $n$. Unfortunately, Nastya came pretty late, so that all pupils had already stood in the queue, i.e. Nastya took the last place in the queue. Of course, it's a little bit sad for Nastya, but she is not going to despond because some pupils in the queue can agree to change places with some other pupils.
>
> Formally, there are some pairs $u$, $v$ such that if the pupil with number $u$ stands directly in front of the pupil with number $v$, Nastya can ask them and they will change places.
>
> Nastya asks you to find the maximal number of places in queue she can move forward.



## **Input**

> The first line contains two integers $n$ and $m$ $(1≤n≤3⋅10^5, 0≤m≤5⋅10^5)​$ — the number of pupils in the queue and number of pairs of pupils such that the first one agrees to change places with the second one if the first is directly in front of the second.
>
> The second line contains $n$ integers $p_1$, $p_2$, ..., $p_n$ — the initial arrangement of pupils in the queue, from the queue start to its end ($1≤p_i≤n$, $p$ is a permutation of integers from $1$ to $n$). In other words, $p_i$ is the number of the pupil who stands on the i-th position in the queue.
>
> The i-th of the following $m$ lines contains two integers $u_i$, $v_i$ $(1≤u_i,v_i≤n,u_i≠v_i)$, denoting that the pupil with number $u_i$ agrees to change places with the pupil with number $v_i$ if $u_i$ is directly in front of $v_i$. It is guaranteed that if $i≠j$, than $v_i≠v_j$ or $u_i≠u_j$. Note that it is possible that in some pairs both pupils agree to change places with each other.
>
> Nastya is the last person in the queue, i.e. the pupil with number $p_n$.



## **Output**

> Print a single integer — the number of places in queue she can move forward.



## **Examples input**

    2 1
    1 2
    1 2



## **Examples output**

    1



## **题意**

给出初始的队列以及一些 $u_i$, $v_i$，代表如果 $u_i$ 恰好位于 $v_i$ 之前的话两者可以进行交换，问队列中最后一个元素最多可以前进多少位。



## **思路**

唔～虚拟赛的时候一直想着用什么样的规则来把最后的元素移动到前面，考虑过前缀的解法，然而时间复杂度只能想到 $O(n^2)​$，无法通过……

再仔细想想如果有两个数字可以相互交换且他们一开始不相邻，要考虑的情况就更多了，然后就，放弃了 QAQ

---

我们反过来想想，考虑从队列尾部一个元素一个元素的增加会发生什么

维护一个列表 $sk$，代表有哪些我们主角无法通过的元素，而当判断到第 $i$ 个元素时，考虑它能否为 $sk$ 中所有元素以及最后的主角让出位置，若可以，显然它可以被交换到主角后面，否则将其加入到 $sk$ 中，最终答案即为 $n-1-sk.size()$



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
typedef pair<int, int> P;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;

int n, m;
int p[maxn];
set<int> to[maxn];
void solve() {
    vector<int> sk;
    int nb = p[n];
    for (int i = n - 1; i >= 1; i--) {
        bool flag = false;
        flag |= !to[nb].count(p[i]);
        for (auto iter = sk.begin(); iter != sk.end() && !flag; iter++) {
            flag |= !to[*iter].count(p[i]);
        }
        if (flag)
            sk.push_back(p[i]);
    }
    cout << n - 1 - sk.size() << endl;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        to[v].insert(u);
    }
    solve();
    return 0;
}
```

