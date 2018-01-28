# 2216 The Longest Straight

## **Description**

> ZB is playing a card game where the goal is to make straights. Each card in the deck has a number between 1 and M(including 1 and M). A straight is a sequence of cards with consecutive values. Values do not wrap around, so 1 does not come after M. In addition to regular cards, the deck also contains jokers. Each joker can be used as any valid number (between 1 and M, including 1 and M).
>
> You will be given N integers card[1] .. card[n] referring to the cards in your hand. Jokers are represented by zeros, and other cards are represented by their values. ZB wants to know the number of cards in the longest straight that can be formed using one or more cards from his hand.



## **Input**

> The first line contains an integer T, meaning the number of the cases.
>
> For each test case:
>
> The first line there are two integers N and M in the first line (1 <= N, M <= 100000), and the second line contains N integers card[i] (0 <= card[i] <= M).



## **Output**

> For each test case, output a single integer in a line -- the longest straight ZB can get.



## **Sample Input**

    2
    7 11
    0 6 5 3 0 10 11
    8 1000
    100 100 100 101 100 99 97 103



## **Sample Output**

    5
    3



## **题意**

给出 $n$ 张牌，其代表的数字在区间 $[1,m]$ ，且 $0$ 可以充当任意牌，问最长连续递增的区间长度是多少。



## **思路**

首先我们可以对原数组进行处理，处理以后某两个数牌面中间所空缺牌的数量可以由该数组对应的差求得。

然后利用尺取法维护双指针，保证双指针之间代表的牌所空缺的数量小于等于 0 的数量，更新得出最大值即可。



## **AC 代码**

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e6+10;
const int mod = 1e9+7;
typedef long long LL;

int n,m;
int a[maxn];
int s[maxn];

void solve()
{
    for(int i=1; i<=m; i++)
        s[i] = s[i-1] + (a[i]==0);
    int i = 0, j = 0, ans = 0;
    while(j<=m)
    {
        if(s[j]-s[i]<=a[0])
            ans = max(ans,j-i), j++;
        else
            i++;
    }
    cout<<ans<<endl;
}

void init()
{
    memset(a,0,sizeof a);
    memset(s,0,sizeof s);
}

int main()
{
    IO;
    int T;
    cin>>T;
    while(T--)
    {
        init();
        cin>>n>>m;
        for(int i=0; i<n; i++)
        {
            int x;
            cin>>x;
            a[x]++;
        }
        solve();
    }
    return 0;
}
```

