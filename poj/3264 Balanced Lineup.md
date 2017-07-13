# Balanced Lineup

## **Description**

> For the daily milking, Farmer John's N cows (1 ≤ N ≤ 50,000) always line up in the same order. One day Farmer John decides to organize a game of Ultimate Frisbee with some of the cows. To keep things simple, he will take a contiguous range of cows from the milking lineup to play the game. However, for all the cows to have fun they should not differ too much in height.
>
> Farmer John has made a list of Q (1 ≤ Q ≤ 200,000) potential groups of cows and their heights (1 ≤ height ≤ 1,000,000). For each group, he wants your help to determine the difference in height between the shortest and the tallest cow in the group.



## **Input**

> Line 1: Two space-separated integers, N and Q. 
>
> Lines 2..N+1: Line i+1 contains a single integer that is the height of cow i 
>
> Lines N+2..N+Q+1: Two integers A and B (1 ≤ A ≤ B ≤ N), representing the range of cows from A to B inclusive.



## **Output**

> Lines 1..Q: Each line contains a single integer that is a response to a reply and indicates the difference in height between the tallest and shortest cow in the range.



## **Sample Input**

    6 3
    1
    7
    3
    4
    2
    5
    1 5
    4 6
    2 2



## **Sample Output**

    6
    3
    0


## **题意**

给出 `n` 个数，然后有 `q` 次查询，每次查询是一个区间，输出该区间最大值与最小值的差。



## **思路**

`RMQ` 问题，可使用 `ST` 算法解决， $O(n\log n)$ 的预处理， $O(1)$ 的查询，其实也就是一个区间dp啦~

`dp[i][j]` 代表以 `j` 为起点，区间长度为 $2^i$ 的特值，针对这一道题，我们有两个特值（最大值与最小值）。

于是很容易得出状态转移方程： `dp[i][j]=op(dp[i-1][j],dp[i-1][j+1<<(i-1)])`

记得初始化 `dp[0][j]` 为对应的每个数。



查询时候也很方便，找出最大的不可覆盖查询区间的区间长度，然后选取首段与尾段取最优即可。



## **AC 代码**

```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 51000;
const int inf = 0x3f3f3f;
int maxx[20][maxn];
int minn[20][maxn];
int n,q;

void rmq()
{
    for(int i=1; (1<<i)<=n; i++)
    {
        for(int j=0; j+(1<<i)<=n; j++)
        {
            maxx[i][j]=max(maxx[i-1][j],maxx[i-1][j+(1<<(i-1))]);
            minn[i][j]=min(minn[i-1][j],minn[i-1][j+(1<<(i-1))]);
        }
    }
}

int main()
{
    while(~scanf("%d%d",&n,&q))
    {
        int x,y;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&x);
            maxx[0][i]=minn[0][i]=x;
        }
        rmq();
        for(int i=0; i<q; i++)
        {
            scanf("%d%d",&x,&y);
            int len=0;
            for(int i=0; 1<<(len+1)<=y-x+1; i++,len++);
            int maxs = max(maxx[len][x-1],maxx[len][y-(1<<len)]);
            int mins = min(minn[len][x-1],minn[len][y-(1<<len)]);
            printf("%d\n",maxs-mins);
        }
    }
    return 0;
}
```

