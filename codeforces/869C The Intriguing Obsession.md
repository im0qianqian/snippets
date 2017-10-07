# C. The Intriguing Obsession

## **Description**

> With hands joined, go everywhere at a speed faster than our thoughts! This time, the Fire Sisters — Karen and Tsukihi — is heading for somewhere they've never reached — water-surrounded islands!
>
> There are three clusters of islands, conveniently coloured red, blue and purple. The clusters consist of a, b and c distinct islands respectively.
>
> Bridges have been built between some (possibly all or none) of the islands. A bridge bidirectionally connects two different islands and has length 1. For any two islands of the same colour, either they shouldn't be reached from each other through bridges, or the shortest distance between them is at least 3, apparently in order to prevent oddities from spreading quickly inside a cluster.
>
> The Fire Sisters are ready for the unknown, but they'd also like to test your courage. And you're here to figure out the number of different ways to build all bridges under the constraints, and give the answer modulo 998 244 353. Two ways are considered different if a pair of islands exist, such that there's a bridge between them in one of them, but not in the other.



## **Input**

> The first and only line of input contains three space-separated integers a, b and c (1 ≤ a, b, c ≤ 5 000) — the number of islands in the red, blue and purple clusters, respectively.



## **Output**

> Output one line containing an integer — the number of different ways to build bridges, modulo 998244353.



## **Examples input**

    1 1 1



## **Examples output**

    8



## **题意**

在三种颜色的岛屿之间建立桥梁，每一种颜色的岛屿分别有 $a,b,c$ 个，且相同颜色的岛屿之间距离不能小于 $3$ ，问总共有多少种情况。



## **思路**

显然，最终桥的排列一定类似于 $abcabcabc...$ 这样的，我们将这三种颜色点的集合抽象为空间中的一个三棱柱。

每条侧棱代表一种颜色，每个侧面上布着相邻两条侧棱之间的连线（桥），显然这样保证了相同颜色岛屿之间的距离。



我们现在只考虑一个侧面，假如相邻的两种颜色分别有 $a,b$ 个：

- 首先，一种颜色不可以与相同的颜色相连，也就是每条侧棱中的点之间不能有连线。
- 第二，不能有相同两个颜色的点连接到同一个点上，也就是左右两条侧棱之间点的连线无共同起点与终点，显然这样的边最多有 $\min(a,b)$ 个。
- 第三，桥的数量最少为 $0$ 个，最多为 $\min(a,b)$ 个，对于数量为 $i$ 的桥，我们可以从左边选取共 $\binom{a}{i}$ 种方式，从右边选取共 $\binom{b}{i}$ 种方式，考虑它们之间的排列共 $i!$ 种，于是共有 $\binom{a}{i} \times \binom{b}{i} \times i!$ 种组合。
- 因此，对于每一个侧面，其贡献 $f(a,b)=\sum_{i=0}^{i=\min(a,b)}\binom{a}{i}\binom{b}{i}i!$ 。



因为三个侧面之间的连线是互不干扰的，因此最终的结果为 $f(a,b) \times f(b,c) \times f(c,a)$ 。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 5e3+10;
const int mod = 998244353;
LL mul[maxn];
LL inv[maxn];

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

LL mult(int a,int b)
{
    int len = min(a,b);
    LL ans = 0;
    for(int i=0; i<=len; i++)
        ans += C(a,i) * C(b,i) % mod * mul[i] % mod,ans %= mod;
    return ans;
}

int32_t main()
{
    init();
    int a,b,c;
    cin>>a>>b>>c;
    LL ans = mult(a,b) * mult(b,c) %mod * mult(c,a) %mod;
    cout<<ans<<endl;
    return 0;
}
```

