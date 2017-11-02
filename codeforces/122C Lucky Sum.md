# A. Lucky Sum

## **Description**

> Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.
>
> Let next(x) be the minimum lucky number which is larger than or equals x. Petya is interested what is the value of the expression next(l) + next(l + 1) + ... + next(r - 1) + next(r). Help him solve this problem.



## **Input**

> The single line contains two integers l and r (1 ≤ l ≤ r ≤ 10^9) — the left and right interval limits.



## **Output**

> In the single line print the only number — the sum next(l) + next(l + 1) + ... + next(r - 1) + next(r).
>
> Please do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specificator.



## **Examples input**

    2 7



## **Examples output**

    33



## **题意**

我们定义 $last(i)$ 代表大于等于 $i$ 最小的幸运数字，求 $\sum_{i=l}^rlast(i)$ 。



## **思路**

显然分块可行，于是我们只需要写一个查找某个数字之后最小的幸运数字即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);

using namespace std;
typedef long long LL;
const int maxn = 1e5+10;

LL last(LL x)
{
    int len = int(log10(x)) + 1;    //数字位数
    LL ans = 0,cnt = 0;
    for(int i=0; i<len; i++)        //同等位数最大最小幸运数
        ans = ans*10+4,cnt = cnt*10+7;
    if(x>cnt)                       //位数+1
        return ans*10+4;
    while(ans<x)
    {
        LL res = cnt;
        for(int i=0; i<1<<len; i++)
        {
            LL tmp = 0;
            for(int j=0; j<len; j++)
            {
                if(i&(1<<j))
                    tmp = tmp*10+7;
                else
                    tmp = tmp*10+4;
            }
            if(tmp>=x)
                res = min(res,tmp);
        }
        ans = res;
    }
    return ans;
}

int main()
{
    LL l,r;
    cin>>l>>r;
    LL now = l,ans = 0;
    while(true)
    {
        LL la = last(now);
        if(la>r)
        {
            ans+= la * (r-now+1);
            break;
        }
        else
            ans += la * (la-now+1);
        now = la+1;
    }
    cout<<ans<<endl;
    return 0;
}
```

