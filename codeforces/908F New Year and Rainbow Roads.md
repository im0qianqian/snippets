# F. New Year and Rainbow Roads

## **Description**

> Roy and Biv have a set of n points on the infinite number line.
>
> Each point has one of 3 colors: red, green, or blue.
>
> Roy and Biv would like to connect all the points with some edges. Edges can be drawn between any of the two of the given points. The cost of an edge is equal to the distance between the two points it connects.
>
> They want to do this in such a way that they will both see that all the points are connected (either directly or indirectly).
>
> However, there is a catch: Roy cannot see the color red and Biv cannot see the color blue.
>
> Therefore, they have to choose the edges in such a way that if all the red points are removed, the remaining blue and green points are connected (and similarly, if all the blue points are removed, the remaining red and green points are connected).
>
> Help them compute the minimum cost way to choose edges to satisfy the above constraints.



## **Input**

> The first line will contain an integer n (1 ≤ n ≤ 300 000), the number of points.
>
> The next n lines will contain two tokens pi and ci (pi is an integer, 1 ≤ pi ≤ 10^9, ci is a uppercase English letter 'R', 'G' or 'B'), denoting the position of the i-th point and the color of the i-th point. 'R' means red, 'G' denotes green, and 'B' means blue. The positions will be in strictly increasing order.



## **Output**

> Print a single integer, the minimum cost way to solve the problem.



## **Examples input**

    4
    1 G
    5 R
    10 B
    15 G



## **Examples output**

    23



## **题意**

数轴上有红绿蓝三种颜色的点，现在我们要为这些点之间连一些边，边的权值为两点的距离，要求图中去掉红色点或者蓝色点以后剩余的部分连通，求最小的花费。



## **思路**

显然，红色点与蓝色点都是不稳定的点（可能被去掉），于是总的权值中一定会包含所有相邻的绿色点两两连接所消耗的花费。

对于红色点（不稳定点），我们可以同时观察它与绿色点（稳定点）的分布，显然不去除点的情况下最优解便是数轴最左端的点与最右端的点之间的距离，但是之前我们说过，红色点是不稳定的，因此我们不能完全依赖它，考虑每相邻两个稳定点之间的红色链，我们可以从这一条链中挑出最长的一条边去掉且保证这一段仍然是连通的。

对于蓝色点同上。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10;

LL p[maxn], n;
char c[maxn];
void solve() {
    LL ans = 0;
    LL lastG = -1, lastR = -1, lastB = -1;
    LL leftR = 0, leftB = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] == 'R' || c[i] == 'G') {
            if (lastR != -1) {
                ans += p[i] - p[lastR];
                leftR = max(leftR, p[i] - p[lastR]);
            }
            lastR = i;
        }
        if (c[i] == 'B' || c[i] == 'G') {
            if (lastB != -1) {
                ans += p[i] - p[lastB];
                leftB = max(leftB, p[i] - p[lastB]);
            }
            lastB = i;
        }
        if (c[i] == 'G') {
            if (lastG != -1) {
                ans += min(0LL, p[i] - p[lastG] - leftR - leftB);
            }
            leftR = leftB = 0;
            lastG = i;
        }
    }
    cout << ans << endl;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    IO;
#endif // ONLINE_JUDGE

    while (cin >> n) {
        for (int i = 0; i < n; i++)
            cin >> p[i] >> c[i];
        solve();
    }
    return 0;
}
```

