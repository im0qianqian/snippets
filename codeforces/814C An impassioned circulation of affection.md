# C. An impassioned circulation of affection

## **Description**

> Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!
>
> Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has n pieces numbered from 1 to n from left to right, and the i-th piece has a colour si, denoted by a lowercase English letter. Nadeko will repaint at most m of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour c — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.
>
> For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of 3. Thus the Koyomity of this garland equals 3.
>
> But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has q plans on this, each of which can be expressed as a pair of an integer mi and a lowercase letter ci, meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.



## **Input**

> The first line of input contains a positive integer n (1 ≤ n ≤ 1 500) — the length of the garland.
>
> The second line contains n lowercase English letters s1s2... sn as a string — the initial colours of paper pieces on the garland.
>
> The third line contains a positive integer q (1 ≤ q ≤ 200 000) — the number of plans Nadeko has.
>
> The next q lines describe one plan each: the i-th among them contains an integer mi (1 ≤ mi ≤ n) — the maximum amount of pieces to repaint, followed by a space, then by a lowercase English letter ci — Koyomi's possible favourite colour.



## **Output**

> Output q lines: for each work plan, output one line containing an integer — the largest Koyomity achievable after repainting the garland according to it.



## **Examples input**

    6
    koyomi
    3
    1 o
    4 o
    4 m



## **Examples output**

    3
    6
    5



## **题意**

给定一个字符串，有 $q$ 次查询，每次查询告诉你最喜欢的字符以及将其他字符替换为它的次数，问字符串中连续最喜欢的字符最大有多长。



## **思路**

$dp[i][j]$ 代表 $i$ 这一个字符在可以替换 $j$ 次的条件下所能组成的最大长度。

然后我们便可以在 $O(n^2)$ 的时间复杂度下打表出所有的情况，根据查询一一输出即可。

---

当然这道题尺取法也可行，时间复杂度 $O(n \times q)$ 。



## **AC 代码**

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e5+10;
const int mod = 1e9+7;
typedef long long LL;

char str[maxn];
int dp[26][maxn],n;

void init()
{
    for(int ch=0; ch<26; ch++)
    {
        for(int i=0; i<n; i++)
        {
            int now = 0;
            for(int j=i; j<n; j++)
            {
                if(str[j]!='a'+ch)
                    now++;
                dp[ch][now] = max(dp[ch][now],j-i+1);
            }
        }
        for(int i=1; i<=n; i++)
            dp[ch][i] = max(dp[ch][i],dp[ch][i-1]);
    }
}

int main()
{
    int q;
    cin>>n>>str>>q;
    init();
    while(q--)
    {
        int m;
        char c;
        cin>>m>>c;
        cout<<dp[c-'a'][m]<<endl;
    }
    return 0;
}
```

