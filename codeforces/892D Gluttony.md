# D. Gluttony

## **Description**

> You are given an array a with n distinct integers. Construct an array b by permuting a such that for every non-empty subset of indices S = {x1, x2, ..., xk} (1 ≤ xi ≤ n, 0 < k < n) the sums of elements on that positions in a and b are different, i. e.
>
> $$
> \sum_{i=1}^ka_{x_i} \not= \sum_{i=1}^kb_{x_i}
> $$
>



## **Input**

> The first line contains one integer n (1 ≤ n ≤ 22) — the size of the array.
>
> The second line contains n space-separated distinct integers a1, a2, ..., an (0 ≤ ai ≤ 10^9) — the elements of the array.



## **Output**

> If there is no such array b, print -1.
>
> Otherwise in the only line print n space-separated integers b1, b2, ..., bn. Note that b must be a permutation of a.
>
> If there are multiple answers, print any of them.



## **Examples input**

    2
    1 2



## **Examples output**

    2 1



## **题意**

寻找给定排列的一个置换，满足任意一个下标集合在 a 与 b 之间选中值的和都不同（不包括全集）。



## **思路**

结论题，首先对原序列进行排序，然后循环左移一位，此时这两个排列满足题目中所说的要求，然后我们把新得到的序列按照原来的下标填入进去即可。

**证明：**

我们设 $t=\{x_1,x_2,\dots,x_k\}$ ，$a$ 为排序后的序列， $b$ 为 $a$ 循环左移一位得到的结果。

显然，循环左移一位会使得 $b_1...b_{n-1}>a_1...a_{n-1}$ ，此时关键讨论 $n$ 是否在 $t$ 中：

- 当 $n \not\in t$ ，显然 $\forall x \in t,b_x>a_x$ ，则 $\sum_{i=1}^kb_{x_i}>\sum_{i=1}^ka_{x_i}$ 。
- 当 $n \in t$ ，我们考虑其逆事件，因为 $\sum_{i=1}^na_i=\sum_{i=1}^nb_i$ ，于是 $\sum_{i=1}^kb_{x_i}<\sum_{i=1}^ka_{x_i}$ 。

因此， $\sum_{i=1}^kb_{x_i}\not =\sum_{i=1}^ka_{x_i}$ ，证毕。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 1e5+10;

int a[maxn];
typedef pair<int,int> P;
P p[maxn];
int main()
{
    IO;
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i],p[i] = P(a[i],i);
    sort(p,p+n);
    for(int i=0; i<n; i++)
        a[p[(i+1)%n].second] = p[i].first;
    for(int i=0; i<n; i++)
        cout<<a[i]<<" ";
    return 0;
}
```

