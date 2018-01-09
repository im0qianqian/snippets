# C. Party Lemonade

## **Description**

> A New Year party is not a New Year party without lemonade! As usual, you are expecting a lot of guests, and buying lemonade has already become a pleasant necessity.
>
> Your favorite store sells lemonade in bottles of n different volumes at different costs. A single bottle of type i has volume $2^{i - 1}$ liters and costs ci roubles. The number of bottles of each type in the store can be considered infinite.
>
> You want to buy at least L liters of lemonade. How many roubles do you have to spend?



## **Input**

> The first line contains two integers n and L (1 ≤ n ≤ 30; 1 ≤ L ≤ 10^9) — the number of types of bottles in the store and the required amount of lemonade in liters, respectively.
>
> The second line contains n integers c1, c2, ..., cn (1 ≤ ci ≤ 10^9) — the costs of bottles of different types.



## **Output**

> Output a single integer — the smallest number of roubles you have to pay in order to buy at least L liters of lemonade.



## **Examples input**

    4 12
    20 30 70 90



## **Examples output**

    150



## **题意**

有 $n$ 种物品，其大小分别为 $2^{i-1}$ ，花费分别为 $c_i$ ，物品的个数无限，现要组成大小至少为 $L$ 的货物，问最小的花费。



## **思路**

因为 $2^{n-1} \times 2 = 2^n$ ，所以我们可以想到小物品组成大物品是否可以带来更小的花费。

于是从小到大扫一遍计算出组成当前大小为 $2^i$ 所需要的最小花费，记为 $a_i$ 。

然后针对大小 $L$ ，我们可以将其转换为二进制，从高位往低位开始枚举，

用 $now$ 记录已访问的高位中所需要的花费，若当前位为 $1$ ， $now+=a[i]$ ，因为我们不能通过这一位组合出大小大于 $L$ 的货物，

若当前位为 $0$ ，记录 $now+a[i]$ ，因为此时我们只需要将该位填充为 $1$ 即可组出大于 $L$ 的货物。

然后找最小值即可。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e5+10;
const int mod = 1e9+7;
typedef long long LL;

LL n,l,a[maxn];
bitset<32> sk;
set<LL> ans;
int main()
{
    IO;
    cin>>n>>l;
    for(int i=0; i<n; i++)
        cin>>a[i];
    LL now = a[0];
    for(int i=1; i<32; i++)
    {
        now <<= 1;
        a[i] = i<n?min(a[i],now):now;
        now = a[i];
    }
    sk = l;
    now = 0;
    for(int i=31; i>=0; i--)
        if(sk[i])
            now +=a[i];
        else
            ans.insert(now+a[i]);
    ans.insert(now);
    cout<<*ans.begin()<<endl;
    return 0;
}
```

