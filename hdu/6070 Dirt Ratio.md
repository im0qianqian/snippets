# Dirt Ratio

## **Description**

> In ACM/ICPC contest, the ''Dirt Ratio'' of a team is calculated in the following way. First let's ignore all the problems the team didn't pass, assume the team passed X problems during the contest, and submitted Y times for these problems, then the ''Dirt Ratio'' is measured as X/Y. If the ''Dirt Ratio'' of a team is too low, the team tends to cause more penalty, which is not a good performance.
>
> ![img](https://www.dreamwings.cn/wp-content/uploads/2017/08/C762-1004-1.png)
>
> Little Q is a coach, he is now staring at the submission list of a team. You can assume all the problems occurred in the list was solved by the team during the contest. Little Q calculated the team's low ''Dirt Ratio'', felt very angry. He wants to have a talk with them. To make the problem more serious, he wants to choose a continuous subsequence of the list, and then calculate the ''Dirt Ratio'' just based on that subsequence.
>
> Please write a program to find such subsequence having the lowest ''Dirt Ratio''.



## **Input**

> The first line of the input contains an integer T(1≤T≤15), denoting the number of test cases.
>
> In each test case, there is an integer n(1≤n≤60000) in the first line, denoting the length of the submission list.
>
> In the next line, there are n positive integers a1,a2,...,an(1≤ai≤n), denoting the problem ID of each submission.



## **Output**

> For each test case, print a single line containing a floating number, denoting the lowest ''Dirt Ratio''. The answer must be printed with an absolute error not greater than 10^−4.



## **Sample Input**

    1
    5
    1 2 1 2 3



## **Sample Output**

    0.5000000000



## **题意**

有一个长度为 $n$ 的序列，求所有区间 $[l,r]$ 的数字种类 / 区间长度 的最小值。



## **思路**

二分答案 $mid$ ，检验是否存在一个区间满足 $\frac{size(l,r)}{r-l+1}<=mid$

即 $size(l,r)+mid×l<=mid×(r+1)$

线段树保存 $size(l,r)+mid×l$ ，然后我们可以枚举右端点 $r$ ，而在右端点加入时带来了自己的一份颜色，标记它上一次的出现位置，则 $r$ 对这段区间有贡献



## **AC 代码**

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef __int64 LL;
const double eps = 1e-6;
const int maxn = 61000;
#define inf 0x3f3f3f

int last_appear[maxn];
int a[maxn],n;
double val[maxn << 2], laz[maxn << 2];

void pushUp(int rt)
{
    val[rt] = min(val[rt << 1], val[rt << 1 | 1]);
}

void pushDown(int rt)
{
    val[rt << 1] += laz[rt];
    laz[rt << 1] += laz[rt];
    val[rt << 1 | 1] += laz[rt];
    laz[rt << 1 | 1] += laz[rt];
    laz[rt] = 0;
}

void build(int l, int r, int rt, double v)
{
    laz[rt] = 0;
    if (l == r)
    {
        val[rt] = v * l;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1, v);
    build(mid + 1, r, rt << 1 | 1, v);
    pushUp(rt);
}

void update(int L, int R, int v, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        val[rt] += v;
        laz[rt] += v;
        return;
    }
    if (laz[rt] != 0)
        pushDown(rt);
    int mid = (l + r) >> 1;
    if (L <= mid)
        update(L, R, v, l, mid, rt << 1);
    if (mid < R)
        update(L, R, v, mid + 1, r, rt << 1 | 1);
    pushUp(rt);
}

double query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
        return val[rt];
    if (laz[rt] != 0)
        pushDown(rt);
    int mid = (l + r) >> 1;
    double ret = inf;
    if (L <= mid)
        ret = query(L, R, l, mid, rt << 1);
    if (mid < R)
        ret = min(ret, query(L, R, mid + 1, r, rt << 1 | 1));
    return ret;
}

bool judge(double mid)
{
    build(1, n, 1, mid);
    memset(last_appear, 0, sizeof(last_appear));    // 该数字上一次的出现位置
    for (int i = 1; i <= n; i++)
    {
        update(last_appear[a[i]] + 1, i, 1, 1, n, 1);
        last_appear[a[i]] = i;
        if (query(1, i, 1, n, 1) < mid * (i + 1))
            return true;
    }
    return false;
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        double low = 0, high = 1, ans;
        while (high - low > eps)        // 二分答案
        {
            double mid = (low + high) / 2.0;
            if (judge(mid))
                high = (ans = mid) - eps;
            else
                low = mid + eps;
        }
        printf("%.9lf\n", ans);
    }
    return 0;
}
```

