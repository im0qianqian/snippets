# C. Qualification Rounds

## **Description**

> Snark and Philip are preparing the problemset for the upcoming pre-qualification round for semi-quarter-finals. They have a bank of n problems, and they want to select any non-empty subset of it as a problemset.
>
> k experienced teams are participating in the contest. Some of these teams already know some of the problems. To make the contest interesting for them, each of the teams should know at most half of the selected problems.
>
> Determine if Snark and Philip can make an interesting problemset!



## **Input**

> The first line contains two integers n, k (1 ≤ n ≤ 10^5, 1 ≤ k ≤ 4) — the number of problems and the number of experienced teams.
>
> Each of the next n lines contains k integers, each equal to 0 or 1. The j-th number in the i-th line is 1 if j-th team knows i-th problem and 0 otherwise.



## **Output**

> Print "YES" (quotes for clarity), if it is possible to make an interesting problemset, and "NO" otherwise.
>
> You can print each character either upper- or lowercase ("YeS" and "yes" are valid when the answer is "YES").



## **Examples input**

    5 3
    1 0 1
    1 1 0
    1 0 0
    1 0 0
    1 0 0



## **Examples output**

    NO



## **题意**

在 $n$ 道题目中挑选一些使得所有人对题目的掌握情况不超过一半。



## **思路**

很容易想到，只要我们挑选两道题，然后判断这两道题是否满足题意即可。

对于每道题每个队的掌握我们用一个数的二进制来表示，二进制某位为 $1$ 代表相应队掌握这道题。

假设挑选的这两道题状态分别为 $i,j$ ，如果 $i\&j=0$ 即满足题意。

---

今天这一场 cf 掉分好严重， $C$ 题之前考虑枚举 $k=1,2,3,4$ ，然后写到 $3$ 的时候发现可以合并，于是便有了下面的代码，另外关于 $3$ 的某个判断忘记删掉了，导致终测 $WA$ 。

终测 $D$ 的结果 $MLE$ ，说好的分数又没有了，可能有更好的解法吧！像千千这种 后缀自动机 + 二分 + 随机 都是旁门左道咯~

到最后还是自己不够细心不够努力的锅~



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;

int n,k;
bool mp[maxn][5];
int kkk[maxn];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k;
    for(int i=0; i<n; i++)
        for(int j=0; j<k; j++)
            cin>>mp[i][j];
    bool flag = false;
    for(int i=0; i<n; i++)
    {
        int num = 0;
        for(int j=0; j<k; j++)
            if(mp[i][j])
                num|=1<<j;
        kkk[num]++;
    }
    for(int i=0; i<1<<k; i++)
        for(int j=0; j<1<<k; j++)
            if((i&j)==0&&(kkk[i]&&kkk[j]))
                flag = true;
    cout<<(flag?"YES":"NO")<<endl;
    return 0;
}
```

