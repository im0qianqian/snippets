# D. The Beatles

## **Description**

> Recently a Golden Circle of Beetlovers was found in Byteland. It is a circle route going through $n⋅k$ cities. The cities are numerated from $1$ to $n⋅k$, the distance between the neighboring cities is exactly $1$ km.
>
> Sergey does not like beetles, he loves burgers. Fortunately for him, there are n fast food restaurants on the circle, they are located in the $1$-st, the $(k+1)$-st, the $(2k+1)$-st, and so on, the $((n−1)k+1)$-st cities, i.e. the distance between the neighboring cities with fast food restaurants is $k$ km.
>
> Sergey began his journey at some city $s$ and traveled along the circle, making stops at cities each $l$ km $(l>0)$, until he stopped in $s$ once again. Sergey then forgot numbers $s$ and $l$, but he remembers that the distance from the city $s$ to the nearest fast food restaurant was $a$ km, and the distance from the city he stopped at after traveling the first $l$ km from $s$ to the nearest fast food restaurant was $b$ km. Sergey always traveled in the same direction along the circle, but when he calculated distances to the restaurants, he considered both directions.
>
> Now Sergey is interested in two integers. The first integer $x$ is the minimum number of stops (excluding the first) Sergey could have done before returning to $s$. The second integer $y$ is the maximum number of stops (excluding the first) Sergey could have done before returning to $s$.



## **Input**

> The first line contains two integers $n$ and $k$ $(1≤n,k≤100000)$ — the number of fast food restaurants on the circle and the distance between the neighboring restaurants, respectively.
>
> The second line contains two integers $a$ and $b$ $(0≤a,b≤\frac{k}{2})$ — the distances to the nearest fast food restaurants from the initial city and from the city Sergey made the first stop at, respectively.



## **Output**

> Print the two integers $x$ and $y$.



## **Examples input**

    2 3
    1 1



## **Examples output**

    1 6



## **题意**

哇！这道题看了好几遍才看懂，是一道读题半小时做题两分钟的示例了 QAQ

---

题目说有一条长度为 $n \times k$ 的链，其中每隔 $k$ 个就有一个餐厅，共有 $n$ 个餐厅。

然后主人公可以每次走 $l$ 的距离，且已知初始状态距离最近的餐厅有 $a$ 的距离，走完第一个 $l$ 后距离最近的餐厅有 $b$ 的距离。

问在所有满足要求的 $l$ 中，走完一个循环（回到起点，可能会转多个圈）最少与最多需要多少步。



## **思路**

嗯～我们假设 $1$, $1+k$, $1+2k$...$1+(n-1)k$ 都为餐厅的位置

初始位置在 $[1,1+k]$ 之间，显然我们可以根据 $a$ 得出最多两个起始坐标，即 $1+a$ 与 $1+k-a$

设起始坐标为 $start$ ，然后我们根据 $b$ 便可以得出两个较小的可行解 $l$ 了，即 $k+1+b-start$ 与 $2 \times k + 1 - b - start$，这里跳到别的区间也没关系，因为我们之后会把他们缩回来

现在我们有了几个合法的 $l$，显然，所有 $l+k \times x$ 当 $x$ 为整数，且 $l+k \times x$ 为正整数时都满足条件，为了方便，我们先对之前得出的 $l$ 做预处理，即 $l=(l\%k+k)\%k$，这样之后的 $x$ 便只需要考虑非负整数即可

对于一个合法的 $l+k \times x$，显然它需要走 $\frac{n \times k}{\gcd(l+k \times x,n \times k)}$ 步才能回到起点

于是，我们直接在区间 $[0,n)$ 中枚举 $x$ 统计答案即可，时间复杂度 $O(n\log n)$



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
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
const double eps = 1e-8;

LL n, k, a, b;
vector<LL> l;

void getl(LL start) {
    l.push_back(k + 1 + b - start);
    l.push_back(2 * k + 1 - b - start);
}
void solve() {
    l.clear();
    if (k % 2 == 0 && k / 2 == a) {
        getl(1 + a);
    } else {
        getl(1 + a);
        getl(k + 1 - a);
    }
    int len = l.size();
    for (int i = 0; i < len; i++) {
        l[i] = (l[i] % k + k) % k;
    }
    LL minn = LLONG_MAX;
    LL maxx = LLONG_MIN;
    LL nk = 1LL * n * k;
    for (auto s : l) {
        for (int i = 0; i < n; i++) {
            LL now = __gcd(s + 1LL * i * k, nk);
            minn = min(minn, nk / now);
            maxx = max(maxx, nk / now);
        }
    }
    cout << minn << " " << maxx << endl;
}
int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    while (cin >> n >> k >> a >> b) {
        solve();
    }
    return 0;
}
```

