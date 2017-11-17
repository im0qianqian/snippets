# D. Boxes And Balls

## **Description**

> Ivan has n different boxes. The first of them contains some balls of n different colors.
>
> Ivan wants to play a strange game. He wants to distribute the balls into boxes in such a way that for every i (1 ≤ i ≤ n) i-th box will contain all balls with color i.
>
> In order to do this, Ivan will make some turns. Each turn he does the following:
>
> Ivan chooses any non-empty box and takes all balls from this box;
>
> Then Ivan chooses any k empty boxes (the box from the first step becomes empty, and Ivan is allowed to choose it), separates the balls he took on the previous step into k non-empty groups and puts each group into one of the boxes. He should put each group into a separate box. He can choose either k = 2 or k = 3.
>
> The penalty of the turn is the number of balls Ivan takes from the box during the first step of the turn. And penalty of the game is the total penalty of turns made by Ivan until he distributes all balls to corresponding boxes.
>
> Help Ivan to determine the minimum possible penalty of the game!



## **Input**

> The first line contains one integer number n (1 ≤ n ≤ 200000) — the number of boxes and colors.
>
> The second line contains n integer numbers a1, a2, ..., an (1 ≤ ai ≤ 10^9), where ai is the number of balls with color i.



## **Output**

> Print one number — the minimum possible penalty of the game.



## **Examples input**

    3
    1 2 3



## **Examples output**

    6



## **题意**

将总和为 sum 的数字拆分为给定数列，每次只能拆分为两堆或者三堆，其花费为当前堆的大小，求最小花费。



## **思路**

我们发现，给定的数列最终作为树的叶子节点存在，所有非叶子节点权值和即为此次分解的花费。

想要花费最小，小节点要尽可能的在下，像不像哈夫曼树呢？

- 对于 n 为奇数的情况，我们每次挑选最小的三个节点合并然后加入到队列。
- 对于 n 为偶数的情况，我们可以增加一个权值为 0 的节点转化为奇数方案。

统计每次的权值贡献和即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 2e5+10;
const double eps = 1e-8;

priority_queue<LL,vector<LL>,greater<LL> >q;

void solve()
{
    LL ans = 0;
    while(q.size()>1)
    {
        LL tmp = 0;
        for(int i=0; i<3; i++)
        {
            if(!q.empty())
            {
                tmp+=q.top();
                q.pop();
            }
        }
        q.push(tmp);
        ans+=tmp;
    }
    cout<<ans<<endl;
}

int main()
{
    IO;
    int n;
    cin>>n;
    if(n%2==0)q.push(0);
    for(int i=1; i<=n; i++)
    {
        LL x;
        cin>>x;
        q.push(x);
    }
    solve();
    return 0;
}
```

