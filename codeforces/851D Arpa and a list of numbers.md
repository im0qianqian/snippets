# D. Arpa and a list of numbers

## **Description**

> Arpa has found a list containing n numbers. He calls a list bad if and only if it is not empty and gcd (see notes section for more information) of numbers in the list is 1.
>
> Arpa can perform two types of operations:
>
> Choose a number and delete it with cost x.
>
> Choose a number and increase it by 1 with cost y.
>
> Arpa can apply these operations to as many numbers as he wishes, and he is allowed to apply the second operation arbitrarily many times on the same number.
>
> Help Arpa to find the minimum possible cost to make the list good.



## **Input**

> First line contains three integers n, x and y (1 ≤ n ≤ 5·10^5, 1 ≤ x, y ≤ 10^9) — the number of elements in the list and the integers x and y.
>
> Second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 10^6) — the elements of the list.



## **Output**

> Print a single integer: the minimum possible cost to make the list good.



## **Examples input**

    4 23 17
    1 17 17 16



## **Examples output**

    40



## **题意**

有一个序列，我们有两种操作：

- 删除某个数，代价为 $x$ 。
- 将某个数的值加一，代价为 $y$ 。

现在我们想让这个序列所有数的 $\gcd$ 大于 $1$ ，求最小的代价。



## **思路**

要让序列所有数的 $\gcd$ 大于 $1$ ，我们可以枚举所有的素因子。

对于每一个素因子 $i$ ，计算当前情况下所需要的最小代价，假设有一个数为 $x$ ，且 $i$ 不是 $x$ 的因子，当 $1 \times x>(i-x\%i) \times y$ 时显然我们可以选择将 $x$ 加到 $i$ 的倍数，否则删除这个数。

找最小值即可。

不过这里我们还需要做点剪枝，当不含有 $i$ 这个因子的数的个数乘以 $\min(x,y)$ 大于当前已知的最小结果时可以不做处理。

显然， $\min(x,y)$ 中的 $x$ 相当于删除所有数，而 $y$ 相当于我们对序列中的每一个数执行最多一次操作让其变成偶数（或者特殊的奇数），此时的 $\gcd$ 至少为 $2$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
typedef __int64 LL;
#define INF __INT64_MAX__

LL n,x,y;
LL sum[maxn];
LL a[maxn];
bool vis[maxn];
int main()
{
    cin>>n>>x>>y;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
        sum[a[i]]++;
    }
    LL ans = INF;
    for(int i=2; i<maxn; i++)   //枚举素数
    {
        if(!vis[i])             //素数筛法
        {
            LL cnt = sum[i];
            for(int j=i+i; j<maxn; j+=i)
            {
                vis[j]=true;
                cnt+=sum[j];
            }
            if((n-cnt)*min(x,y)<ans)    //剪
            {
                LL val = 0;
                for(int j=1; j<=n; j++)
                    if(a[j]%i)
                        val+=(x>y*(i-a[j]%i))?y*(i-a[j]%i):x;
                ans = min(ans,val);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
