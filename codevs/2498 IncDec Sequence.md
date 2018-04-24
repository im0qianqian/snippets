# 2498 IncDec Sequence

## **Description**

> 给定一个长度为 n 的数列 {a1,a2...an} ，每次可以选择一个区间 [l,r] ，使这个区间内的数都加一或者都减一。
>
> 问至少需要多少次操作才能使数列中的所有数都一样，并求出在保证最少次数的前提下，最终得到的数列有多少种。



## **Input**

> 第一行一个正整数 n
>
> 接下来 n 行，每行一个整数，第 i+1 行的整数表示 ai 。



## **Output**

> 第一行输出最少操作次数
>
> 第二行输出最终能得到多少种结果



## **Sample Input**

    4
    1
    1
    2
    2


## **Sample Output**

    1
    2



## **思路**

差分数组，我们令 $d$ 为 $a$ 的差分数组，则对区间 `[l,r]` 加 $c$ 的操作即可转化为 `d[l]+c, d[r+1]-c` 这两步。

令 $s_1$ 代表差分数组中除 $d_0$ 以外的正数和，$s_2$ 代表差分数组中除 $d_0$ 以外的负数和的绝对值。

因为 $c$ 的大小为 $+1$ 或者 $-1$，我们想要把除 $d_0$ 以外的其他元素（$d_1\dots d_{n-1}$）全部调整为 $0$ 显然需要 $\max(s_1,s_2)$ 步操作（多余的那些操作可以附加到 $d_0$ 或者 $d_{n}$ 之中）。

于是，原数列的值便全部与 $d_0$ 相等了，第二问即 $d_0$ 的变化区间大小，因为我们说多余的操作可以附加到 $d_0$ 或者 $d_n$ 之中，其中 $d_n$ 已经超出了我们的判断范围，因此对它的操作是无意义的，可以忽略不计，则最终结果为 $abs(s_1-s_2)+1$ 。



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

int n;
LL a[maxn];
LL d[maxn];

int main() {
#ifdef LOCAL_IM0QIANQIAN
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#else
    IO;
#endif // LOCAL_IM0QIANQIAN

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    LL s1 = 0, s2 = 0;
    d[0] = a[0];
    for (int i = 1; i < n; i++) {
        d[i] = a[i] - a[i - 1];
        if (d[i] > 0)
            s1 += d[i];
        else if (d[i] < 0)
            s2 -= d[i];
    }
    cout << max(s1, s2) << endl;
    cout << abs(s1 - s2) + 1 << endl;
    return 0;
}
```

