# B. Wrath

## **Description**

> Hands that shed innocent blood!
>
> There are n guilty people in a line, the i-th of them holds a claw with length Li. The bell rings and every person kills some of people in front of him. All people kill others at the same time. Namely, the i-th person kills the j-th person if and only if j < i and j ≥ i - Li.
>
> You are given lengths of the claws. You need to find the total number of alive people after the bell rings.



## **Input**

> The first line contains one integer n (1 ≤ n ≤ 10^6) — the number of guilty people.
>
> Second line contains n space-separated integers L1, L2, ..., Ln (0 ≤ Li ≤ 10^9), where Li is the length of the i-th person's claw.



## **Output**

> Print one integer — the total number of alive people after the bell rings.



## **Examples input**

    4
    0 1 0 10



## **Examples output**

    1



## **题意**

每个人都有一个长度为 $l_i$ 的武器，相邻的两个人之间距离为 1 ，同一时间所有人使用武器攻击左边的人，问最后存活下来的人数。



## **思路**

看完题意，我的心情是这样的：

![img](https://www.dreamwings.cn/wp-content/uploads/2017/11/20171118112912.png)

显然，最右侧的人一定是可以存活下来的。

我们维护一个 $cnt$ 代表右侧延伸到当前位置的武器长度，

- 若 $cnt>0$ 说明当前位置在别人的攻击范围内，否则 $ans+1$ 。
- 更新 $cnt$ 为 $\max(cnt-1,a_i)$ 看对于 $i$ 来说是否可以攻击到更远的位置。

时间复杂度 $\mathcal{O}(n)$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 2e6+10;

LL a[maxn],n;

void solve()
{
    LL cnt = a[n-1],ans = 1;
    for(int i=n-2; i>=0; i--)
    {
        if(!cnt)ans++;
        cnt = max(cnt-1,a[i]);
    }
    cout<<ans<<endl;
}

int main()
{
    IO;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i];
    solve();
    return 0;
}
```

