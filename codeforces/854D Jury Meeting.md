# D. Jury Meeting

## **Description**

> Country of Metropolia is holding Olympiad of Metrpolises soon. It mean that all jury members of the olympiad should meet together in Metropolis (the capital of the country) for the problem preparation process.
>
> There are n + 1 cities consecutively numbered from 0 to n. City 0 is Metropolis that is the meeting point for all jury members. For each city from 1 to n there is exactly one jury member living there. Olympiad preparation is a long and demanding process that requires k days of work. For all of these k days each of the n jury members should be present in Metropolis to be able to work on problems.
>
> You know the flight schedule in the country (jury members consider themselves important enough to only use flights for transportation). All flights in Metropolia are either going to Metropolis or out of Metropolis. There are no night flights in Metropolia, or in the other words, plane always takes off at the same day it arrives. On his arrival day and departure day jury member is not able to discuss the olympiad. All flights in Megapolia depart and arrive at the same day.
>
> Gather everybody for k days in the capital is a hard objective, doing that while spending the minimum possible money is even harder. Nevertheless, your task is to arrange the cheapest way to bring all of the jury members to Metrpolis, so that they can work together for k days and then send them back to their home cities. Cost of the arrangement is defined as a total cost of tickets for all used flights. It is allowed for jury member to stay in Metropolis for more than k days.



## **Input**

> The first line of input contains three integers n, m and k (1 ≤ n ≤ 10^5, 0 ≤ m ≤ 10^5, 1 ≤ k ≤ 10^6).
>
> The i-th of the following m lines contains the description of the i-th flight defined by four integers di, fi, ti and ci (1 ≤ di ≤ 10^6, 0 ≤ fi ≤ n, 0 ≤ ti ≤ n, 1 ≤ ci ≤ 10^6, exactly one of fi and ti equals zero), the day of departure (and arrival), the departure city, the arrival city and the ticket cost.



## **Output**

> Output the only integer that is the minimum cost of gathering all jury members in city 0 for k days and then sending them back to their home cities.
>
> If it is impossible to gather everybody in Metropolis for k days and then send them back to their home cities, output "-1" (without the quotes).



## **Examples input**

    2 6 5
    1 1 0 5000
    3 2 0 5500
    2 2 0 6000
    15 0 2 9000
    9 0 1 7000
    8 0 2 6500



## **Examples output**

    24500



## **题意**

n 名议员需要参加一场持续 k 天的会议，有 m 次航班，每一次的航班都有相应的费用，现在我们要将这 n 名议员送到 0 号城市，参加完会议后送他们回原来的城市，求最小的花费。



## **思路**

假设有航班序列： $[1,2,2,1,1,3,...,3,2,1]$ ，其中数字代表它所 起飞 / 抵达 的城市，横向代表航班的出发时间。

显然，要参加一场持续 $k$ 天的会议需要所有人到场，即在 $3$ 未出现之前我们可以随意选择 $1,2$ 的出发时间使得总花费最小。

我们令 $res[i]$ 代表从 $i$ 城市出发所需的最小花费， $a[i]$ 代表截至到第 $i$ 天所有议员都可以抵达的最小花费。

我们知道，所有城市所需的航班未出现之前， $a[i]$ 是没有意义的。

通过上面所说的我们可以正向遍历所有出发时间算得 $a$ 数组。

同理，返程航班也可以这样处理，最终得到 $b$ 数组。

通过 $a,b$ 数组的性质我们可以正推反推得到所有时间的 去程 / 返程 最小花费。

然后只需要找出间隔为 $k$ 的 $a_i+b_{i+k+1}$ 的最小值即可，若无，输出 $-1$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,c=0,f=1;
    for(; c<'0'||c>'9'; c=getchar())f=c!='-';
    for(; c>='0'&&c<='9'; c=getchar())x=x*10+c-'0';
    return f?x:-x;
}
template <typename T>
inline bool scan_d(T &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9') )
    {
        if((c = getchar()) == EOF) return 0;
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
template<typename T>
void print(T x)
{
    static char s[33], *s1;
    s1 = s;
    if (!x) *s1++ = '0';
    if (x < 0) putchar('-'), x = -x;
    while(x) *s1++ = (x % 10 + '0'), x /= 10;
    while(s1-- != s) putchar(*s1);
}
template<typename T>
void println(T x)
{
    print(x);
    putchar('\n');
}

typedef __int64 LL;
const int maxn = 1e5+10;
const LL inf = __INT64_MAX__;

struct node
{
    int d,f,t,c;
    bool operator<(const node &x)
    {
        return d<x.d;
    }
} edge[maxn];


int n,m,k;
LL a[maxn*10];
LL b[maxn*10];
LL res[maxn];
LL d[maxn];
int maxr;

void tode()
{
    LL ans=inf;
    for(int i=maxr; i>=1; i--)
    {
        if(!b[i])
            b[i]=b[i+1];
        else if(b[i+1])
            b[i]=min(b[i],b[i+1]);
    }
    for(int i=1; i<=maxr; i++)
    {
        if(!a[i])
            a[i]=a[i-1];
        else if(a[i-1])
            a[i]=min(a[i],a[i-1]);
    }
    for(int i=1; i<=maxr-k-1; i++)
        if(a[i]&&b[i+k+1])
            ans=min(ans,a[i]+b[i+k+1]);
    println((ans!=inf?ans:-1));
}

void solve()
{
    LL now = inf;
    int cnt = n;
    for(int i=1; i<=m; i++)     //出发
    {
        int nod = edge[i].d;
        if(edge[i].f)
        {
            if(!res[edge[i].f])
            {
                res[edge[i].f]=edge[i].c;
                if(!(--cnt))    // cnt = 0 代表所有的城市都已经出现过了
                {
                    now=0;      // 计算一个 now 代表当前花费
                    for(int i=1; i<=n; i++)
                        now+=res[i];
                    a[nod]=now;
                }
            }
            else if(res[edge[i].f]>edge[i].c)
            {
                if(!cnt)        // 试探以当前位置结尾的最小花费
                {
                    now-=res[edge[i].f];
                    res[edge[i].f]=edge[i].c;
                    now+=edge[i].c;
                    a[nod]=now;
                }
                else res[edge[i].f]=edge[i].c;  //更新最小花费
            }
        }
    }
    now=inf,cnt=n;
    for(int i=m; i>=1; i--)     //返回
    {
        int nod=edge[i].d;
        if(edge[i].t)
        {
            if(!d[edge[i].t])
            {
                d[edge[i].t]=edge[i].c;
                if(!(--cnt))
                {
                    now=0;
                    for(int i=1; i<=n; i++)
                        now+=d[i];
                    b[nod]=now;
                }
            }
            else if(d[edge[i].t]>edge[i].c)
            {
                if(!cnt)
                {
                    now-=d[edge[i].t];
                    d[edge[i].t]=edge[i].c;
                    now+=edge[i].c;
                    b[nod]=now;
                }
                else d[edge[i].t]=edge[i].c;;
            }
        }
    }
    tode();
}

int main()
{
    scan_d(n);
    scan_d(m);
    scan_d(k);
    for(int i=1; i<=m; i++)
    {
        scan_d(edge[i].d);
        scan_d(edge[i].f);
        scan_d(edge[i].t);
        scan_d(edge[i].c);
        maxr = max(maxr,edge[i].d);
    }
    sort(edge+1,edge+m+1);      //按时间排序
    solve();
    return 0;
}
```

