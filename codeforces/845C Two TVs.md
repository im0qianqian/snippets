# C. Two TVs

## **Description**

> Polycarp is a great fan of television.
>
> He wrote down all the TV programs he is interested in for today. His list contains n shows, i-th of them starts at moment li and ends at moment ri.
>
> Polycarp owns two TVs. He can watch two different shows simultaneously with two TVs but he can only watch one show at any given moment on a single TV. If one show ends at the same moment some other show starts then you can't watch them on a single TV.
>
> Polycarp wants to check out all n shows. Are two TVs enough to do so?



## **Input**

> The first line contains one integer n (1 ≤ n ≤ 2·10^5) — the number of shows.
>
> Each of the next n lines contains two integers li and ri (0 ≤ li < ri ≤ 10^9) — starting and ending time of i-th show.



## **Output**

> If Polycarp is able to check out all the shows using only two TVs then print "YES" (without quotes). Otherwise, print "NO" (without quotes).



## **Examples input**

    3
    1 2
    2 3
    4 5



## **Examples output**

    YES



## **题意**

给定所有电视节目的播放时间，有两台电视，问能否完整收看所有的电视节目。（同一个电视无法完整收看两个连续时间的节目）



## **思路**

模拟出两台电视观看节目的结束时间，然后排序枚举一遍所有的节目即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 2e5+10;

struct node
{
    int l,r;
} a[maxn];
int n;

bool judge()
{
    int tv1 = INT_MIN;
    int tv2 = INT_MIN;
    for(int i=0; i<n; i++)
    {
        if(a[i].l>tv1)
            tv1 = a[i].r;
        else if(a[i].l>tv2)
            tv2 = a[i].r;
        else
            return false;
    }
    return true;
}

int main()
{
    IO;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>a[i].l>>a[i].r;
    }
    sort(a,a+n,[](const node &x,const node &y)
    {
        if(x.l==y.l)
            return x.r<y.r;
        return x.l<y.l;
    });
    cout<<(judge()?"YES":"NO")<<endl;
    return 0;
}
```

