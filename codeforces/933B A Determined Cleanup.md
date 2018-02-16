## B. A Determined Cleanup

## **Description**

> In order to put away old things and welcome a fresh new year, a thorough cleaning of the house is a must.
>
> Little Tommy finds an old polynomial and cleaned it up by taking it modulo another. But now he regrets doing this...
>
> Given two integers $p$ and $k$ , find a polynomial $f(x)$ with non-negative integer coefficients strictly less than $k$ , whose remainder is $p$ when divided by $(x + k)$ . That is, $f(x) = q(x)·(x + k) + p$ , where $q(x)$ is a polynomial (not necessarily with integer coefficients).



## **Input**

> The only line of input contains two space-separated integers $p$ and $k$ $(1 ≤ p ≤ 10^{18}, 2 ≤ k ≤ 2 000)$ .



## **Output**

> If the polynomial does not exist, print a single integer $-1$ , or output two lines otherwise.
>
> In the first line print a non-negative integer $d$ — the number of coefficients in the polynomial.
>
> In the second line print $d$ space-separated integers $a_0, a_1, ..., a_{d - 1}$ , describing a polynomial $f(x)=\sum_{i=0}^{d-1}a_i·x^i$ fulfilling the given requirements. Your output should satisfy $0 ≤ a_i < k$ for all $0 ≤ i ≤ d - 1$ , and $a_{d - 1} ≠ 0$ .
>
> If there are many possible solutions, print any of them.



## **Examples input**

    46 2



## **Examples output**

    7
    0 1 0 0 1 1 1



## **题意**

给定正整数 $p,k$ ，我们需要找出一个多项式 $q(x)$ ，使得 $f(x) = q(x)·(x + k) + p$ 的各项系数严格小于 $k$ 且不为负数，输出 $f(x)$ 的各项系数。



## **思路**

仔细想想便可以知道，这样的解一定是存在的，所以没有输出 $-1$ 的可能性

我们可以对原式化简一下： $f(x)=x·q(x)+k·q(x)+p$

假设 $q(x)=a_1+a_2·x+a_3·x^2+\dots+a_n·x^{n-1}$ ，其中 $a_i$ 为某一整数

**现在我们再来讨论 $f(x)$ 各项的系数：**

- 常数项：$k \times a_1+p$
- 一次项：$k \times a_2 + a_1$
- 二次项：$k\times a_3+a_2$
- ...

于是我们有了一个通项不等式：$0≤k\times a_n+a_{n-1}<k$ ，其中 $a_0=p$

从上到下一一解出每一项即可，注意要保证系数不为负数



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 1e5+10;

LL a[maxn];
LL ans[maxn];
LL k,p;

LL get(LL a1,int i)
{
    ans[i] = ((a1 % k) + k) % k;
    return (ans[i] - a1)/k;
}

int main()
{
    IO;
    cin>>p>>k;
    a[0] = p;
    for(int i=1; i<maxn; i++)
    {
        a[i] = get(a[i-1],i);
        if(!a[i])
        {
            cout<<i<<endl;
            for(int j=1; j<=i; j++)
                cout<<ans[j]<<" ";
            cout<<endl;
            break;
        }
    }
    return 0;
}
```

