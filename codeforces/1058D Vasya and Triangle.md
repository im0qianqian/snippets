# D. Vasya and Triangle

## **Description**

> Vasya has got three integers $n$, $m$ and $k$. He'd like to find three integer points $(x_1,y_1)$, $(x_2,y_2)$, $(x_3,y_3)$, such that $0≤x_1,x_2,x_3≤n$, $0≤y_1,y_2,y_3≤m$ and the area of the triangle formed by these points is equal to $\frac{nm}{k}$.
>
> Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.



## **Input**

> The single line contains three integers $n$, $m$, $k$ $(1≤n,m≤10^9, 2≤k≤10^9)$.



## **Output**

> If there are no such points, print "NO".
>
> Otherwise print "YES" in the first line. The next three lines should contain integers $x_i$,$y_i$ — coordinates of the points, one point per line. If there are multiple solutions, print any of them.
>
> You can print each letter in any case (upper or lower).



## **Note**

> In the first example area of the triangle should be equal to $\frac{nm}{k}=4$. The triangle mentioned in the output is pictured below:
>
> ![img](https://www.dreamwings.cn/wp-content/uploads/2018/10/d18d412ca0f3dfee039ccab59869d1c2940c05dc.png)
>
> In the second example there is no triangle with area $\frac{nm}{k}=\frac{16}{7}$.



## **Examples input**

    4 3 3



## **Examples output**

    YES
    1 0
    2 3
    4 1



## **题意**

给定矩形的长和宽，以及一个大于 $1$ 的整数 $k$，问能否在矩形内找到三个点，且这三点所围成的三角形面积等于 $\frac{nm}{k}$。



## **思路**

显然，不论最终找到的三角形处于什么形态，我们都可以通过平移旋转将其一个顶点设置为原点，且满足三角形位于矩形内部。

我们设这三点分别为 $A(0,0),B(x_1,y_1),C(x_2,y_2)$，由此得到两条向量，根据叉乘求得三角形面积为 $\frac{|x_1y_2-x_2y_1|}{2}$。

于是我们只需要找到合适的两个点使得 $|x_1y_2-x_2y_1|=\frac{2nm}{k}$ 即可。

左端必为整数，因此假若 $2nm\%k\not=0$，则无解，对于其他情况必有解存在。

我们假设 $B,C$ 两点都位于坐标轴，即 $x_2=y_1=0$，$|x_1y_2-x_2y_1|=x_1y_2$，相当于我们只需将 $\frac{2nm}{k}$ 分解为两个满足题意的整数乘积即可。

因为 $2nm\%k=0$，则 $2nm$ 必包含 $k$ 所有的素因子，求得 $u=\gcd(2n,k)$

若 $u=1$，显然 $m$ 可以整除 $k$，令 $x_1=n,y_2=2\times m/k$ 即可；

否则令 $x_1=2\times n/u,y_2=m\times u/k$ 即可。



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

LL n, m, k;

bool solve() {
    if (2LL * n * m % k != 0)
        return false;
    cout << "YES" << endl;
    LL a, b, gc = __gcd(2LL * n, k);
    if (gc == 1)
        b = 2LL * m / k, a = n;
    else
        a = 2LL * n / gc, b = m * gc / k;
    cout << "0 0" << endl;
    cout << 0 << " " << b << endl;
    cout << a << " " << 0 << endl;
    return true;
}

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    cin >> n >> m >> k;
    if (!solve()) {
        cout << "NO" << endl;
    }
    return 0;
}
```

