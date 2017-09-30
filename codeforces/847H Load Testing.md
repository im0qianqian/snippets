# H. Load Testing

## **Description**

> Polycarp plans to conduct a load testing of its new project Fakebook. He already agreed with his friends that at certain points in time they will send requests to Fakebook. The load testing will last n minutes and in the i-th minute friends will send ai requests.
>
> Polycarp plans to test Fakebook under a special kind of load. In case the information about Fakebook gets into the mass media, Polycarp hopes for a monotone increase of the load, followed by a monotone decrease of the interest to the service. Polycarp wants to test this form of load.
>
> Your task is to determine how many requests Polycarp must add so that before some moment the load on the server strictly increases and after that moment strictly decreases. Both the increasing part and the decreasing part can be empty (i. e. absent). The decrease should immediately follow the increase. In particular, the load with two equal neigbouring values is unacceptable.
>
> For example, if the load is described with one of the arrays [1, 2, 8, 4, 3], [1, 3, 5] or [10], then such load satisfies Polycarp (in each of the cases there is an increasing part, immediately followed with a decreasing part). If the load is described with one of the arrays [1, 2, 2, 1], [2, 1, 2] or [10, 10], then such load does not satisfy Polycarp.
>
> Help Polycarp to make the minimum number of additional requests, so that the resulting load satisfies Polycarp. He can make any number of additional requests at any minute from 1 to n.



## **Input**

> The first line contains a single integer n (1 ≤ n ≤ 100 000) — the duration of the load testing.
>
> The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 10^9), where ai is the number of requests from friends in the i-th minute of the load testing.



## **Output**

> Print the minimum number of additional requests from Polycarp that would make the load strictly increasing in the beginning and then strictly decreasing afterwards.



## **Examples input**

    5
    1 4 3 2 5



## **Examples output**

    6



## **题意**

给出一个数组，现在我们想让它前半部分递增，后半部分递减，问需要改变数的大小之和。



## **思路**

统计原数组距离最小递增序列的前缀距离与原数组距离最小递减序列的后缀距离。

然后从左到右枚举一遍即可。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 1e5+10;
LL a[maxn],b[maxn];
LL c[maxn],d[maxn];
LL e[maxn],f[maxn];
LL n;

int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i];
    LL lmaxf = a[0];
    e[0] = lmaxf;
    for(int i=1; i<n; i++)
    {
        c[i] = c[i-1];
        if(a[i]<=lmaxf)
        {
            c[i] += lmaxf - a[i] + 1;
            lmaxf += 1;
        }
        else
            lmaxf = max(lmaxf,a[i]);
        e[i] = lmaxf;
    }
    lmaxf = a[n-1];
    f[n-1] = lmaxf;
    for(int i=n-2; i>=0; i--)
    {
        d[i] = d[i+1];
        if(a[i]<=lmaxf)
        {
            d[i] += lmaxf - a[i] + 1;
            lmaxf += 1;
        }
        else
            lmaxf = max(lmaxf,a[i]);
        f[i] = lmaxf;
    }
    LL ans = LLONG_MAX;
    for(int i=0; i<n; i++)
    {
        LL ci = max(e[i],f[i]) - e[i];
        ans = min(ans,c[i]+d[i+1]+ci);
    }
    cout<<ans<<endl;
    return 0;
}
```

