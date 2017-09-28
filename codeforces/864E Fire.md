# E. Fire

## **Description**

> Polycarp is in really serious trouble — his house is on fire! It's time to save the most valuable items. Polycarp estimated that it would take ti seconds to save i-th item. In addition, for each item, he estimated the value of di — the moment after which the item i will be completely burned and will no longer be valuable for him at all. In particular, if ti ≥ di, then i-th item cannot be saved.
>
> Given the values pi for each of the items, find a set of items that Polycarp can save such that the total value of this items is maximum possible. Polycarp saves the items one after another. For example, if he takes item a first, and then item b, then the item a will be saved in ta seconds, and the item b — in ta + tb seconds after fire started.



## **Input**

> The first line contains a single integer n (1 ≤ n ≤ 100) — the number of items in Polycarp's house.
>
> Each of the following n lines contains three integers ti, di, pi (1 ≤ ti ≤ 20, 1 ≤ di ≤ 2000, 1 ≤ pi ≤ 20) — the time needed to save the item i, the time after which the item i will burn completely and the value of item i.



## **Output**

> In the first line print the maximum possible total value of the set of saved items. In the second line print one integer m — the number of items in the desired set. In the third line print m distinct integers — numbers of the saved items in the order Polycarp saves them. Items are 1-indexed in the same order in which they appear in the input. If there are several answers, print any of them.



## **Examples input**

    3
    3 7 4
    2 6 5
    3 7 6



## **Examples output**

    11
    2
    2 3



## **题意**

有 $n$ 个文件，第 $i$ 个文件拯救它需要 $t_i$ 时间，该文件会在 $d_i$ 时间自动销毁，它的价值是 $p_i$ ，问最终可以拯救的最大价值，并且输出路径。



## **思路**

简单 01 背包问题

$dp[i][j]$ 代表对于前 $i$ 件物品在第 $j$ 秒时所能拯救的最大价值

则当 $t_i>j$ 或 $j>=d_i$ 时，当前物品无法被选择，因此 $dp[i][j]=dp[i-1][j]$

对于其他时间： $dp[i][j]=\max(dp[i-1][j],dp[i-1][j-t_i]+p_i)$ 

顺便记录一下路径就好了



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 110;
int n;
int dp[maxn][maxn*25];
bool path[maxn][maxn*25];
struct node
{
    int t,d,p,id;
    bool operator<(const node &x)
    {
        return d<x.d;
    }
} a[maxn];

void solve()
{
    int maxx = 0,maxj = 0;
    for(int i=a[0].t; i<min(2000,a[0].d); i++)
        dp[0][i] = a[0].p,path[0][i] = 1,maxx = a[0].p,maxj = i;
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<=2000; j++)
        {
            if(j<a[i].t||j>=a[i].d)
                dp[i][j] = dp[i-1][j];
            else
            {
                dp[i][j] = dp[i-1][j];
                if(dp[i-1][j-a[i].t]+a[i].p>dp[i][j])
                {
                    path[i][j] = true;
                    dp[i][j] = dp[i-1][j-a[i].t]+a[i].p;
                }
            }
            if(dp[i][j]>=maxx)
            {
                maxx = dp[i][j];
                maxj = j;
            }
        }
    }
    vector<int> ans;
    for(int i=n-1,j=maxj; i>=0; i--)
    {
        if(path[i][j])
        {
            ans.push_back(i);
            j-=a[i].t;
        }
    }
    cout<<maxx<<endl;
    cout<<ans.size()<<endl;
    int len = ans.size();
    for(int i=len-1; i>=0; i--)
        cout<<a[ans[i]].id<<(i!=0?" ":"\n");
}

int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i].t>>a[i].d>>a[i].p,a[i].id = i+1;
    sort(a,a+n);
    solve();
    return 0;
}
```

