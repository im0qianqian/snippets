# E. Buy Low Sell High

## **Description**

> You can perfectly predict the price of a certain stock for the next N days. You would like to profit on this knowledge, but only want to transact one share of stock per day. That is, each day you will either buy one share, sell one share, or do nothing. Initially you own zero shares, and you cannot sell shares when you don't own any. At the end of the N days you would like to again own zero shares, but want to have as much money as possible.



## **Input**

> Input begins with an integer N (2 ≤ N ≤ 3·10^5), the number of days.
>
> Following this is a line with exactly N integers p1, p2, ..., pN (1 ≤ pi ≤ 10^6). The price of one share of stock on the i-th day is given by pi.



## **Output**

> Print the maximum amount of money you can end up with at the end of N days.



## **Examples input**

    9
    10 5 4 7 9 12 6 2 10



## **Examples output**

    20



## **题意**

我们知道股票每一天的价格，当我们手中没有股票的时候不可以出售，问最后所能获得的最大价值。



## **思路**

考虑贪心，用小顶堆维护整个序列。

假如当前输入为 $x$ ，且堆空或者堆顶元素大于 $x$ 时，将 $x$ 插入堆中；

否则删除堆顶元素，将 $x$ 在堆中插入两遍，这一步的操作含义为：我们买入之前堆顶元素所代表的股票，然后以 $x$ 的价格卖出，此时相当于给之前的元素升值至 $x$ ，再插入的 $x$ 和第一种操作一样。（ $-4+7-5+9-7+12-2+10=20$ ）

统计所有卖出的价值和即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;

multiset<int> sk;
int main()
{
    int n;
    LL ans = 0;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int x;
        cin>>x;
        if(!sk.empty()&&*sk.begin()<x)
        {
            ans+=x-*sk.begin();
            sk.erase(sk.begin());
            sk.insert(x);
            sk.insert(x);
        }
        else
            sk.insert(x);
    }
    cout<<ans<<endl;
    return 0;
}
```

