# 2214 Knapsack problem

## **Description**

> Given a set of n items, each with a weight w[i] and a value v[i], determine a way to choose the items into a knapsack so that the total weight is less than or equal to a given limit B and the total value is as large as possible. Find the maximum total value. (Note that each item can be only chosen once).



## **Input**

> The first line contains the integer T indicating to the number of test cases.
>
> For each test case, the first line contains the integers n and B.
>
> Following n lines provide the information of each item.
>
> The i-th line contains the weight w[i] and the value v[i] of the i-th item respectively.
>
> 1 <= number of test cases <= 100
>
> 1 <= n <= 500
>
> 1 <= B, w[i] <= 1000000000
>
> 1 <= v[1]+v[2]+...+v[n] <= 5000
>
> All the inputs are integers.



## **Output**

> For each test case, output the maximum value.



## **Sample Input**

    1
    5 15
    12 4
    2 2
    1 1
    4 10
    1 2



## **Sample Output**

    15



## **题意**

n 件物品放入容量为 B 的背包，每件物品都有它的权重和体积，问所能获得的最大权值。



## **思路**

一眼看去只是普通的 01背包，然而数据范围让人无法下手。

之前我们考虑前 $i$ 件物品装入容量为 $v$ 的背包所能获得的最大价值，换位思考一下，我们考虑前 $i$ 件物品组成价值为 $w$ 的最小体积，于是这道题就可以解出来啦~



## **AC 代码**

```cpp
#include <iostream>
#include<cstring>
#include<algorithm>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e5+10;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
LL n,b;
LL w[maxn],v[maxn];
LL dp[5100];

void solve()
{
    memset(dp,inf,sizeof(dp));
    dp[0] = 0;
    for(int i=1; i<=n; i++)
        for(int j=5000; j>=v[i]; j--)
            dp[j] = min(dp[j],dp[j-v[i]]+w[i]);
    for(int i=5000; i>=0; i--)
        if(dp[i]<=b)
        {
            cout<<i<<endl;
            break;
        }
}

int main()
{
    IO;
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>b;
        for(int i=1; i<=n; i++)
            cin>>w[i]>>v[i];
        solve();
    }
    return 0;
}
```

