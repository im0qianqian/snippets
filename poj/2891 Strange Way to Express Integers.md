# Strange Way to Express Integers

## **Description**

> Elina is reading a book written by Rujia Liu, which introduces a strange way to express non-negative integers. The way is described as following:
>
> Choose k different positive integers a1, a2, …, ak. For some non-negative m, divide it by every ai (1 ≤ i ≤ k) to find the remainder ri. If a1, a2, …, ak are properly chosen, m can be determined, then the pairs (ai, ri) can be used to express m.
>
> “It is easy to calculate the pairs from m, ” said Elina. “But how can I find m from the pairs?”
>
> Since Elina is new to programming, this problem is too difficult for her. Can you help her?



## **Input**

> The input contains multiple test cases. Each test cases consists of some lines.
>
> Line 1: Contains the integer k.
>
> Lines 2 ~ k + 1: Each contains a pair of integers ai, ri (1 ≤ i ≤ k).



## **Output**

> Output the non-negative integer m on a separate line for each test case. If there are multiple possible values, output the smallest one. If there are no possible values, output -1.



## **Sample Input**

    2
    8 7
    11 9



## **Sample Output**

    31



## **题意**

给出一组 $m_i,r_i$ ，求最小的一个正整数 $X$ ，使得 $X\%m_i=r_i$ ，如果不存在这样的 $X$ 则输出 $-1$ 。（不满足除数之间两两互质）



## **思路**

因为除数之间不满足两两互质，所以就不能直接套用中国剩余定理的模板咯！

这里我们采用合并 *不定方程* 的方法，即先合并前两个方程，然后用合并的结果与第三个方程进行合并，最终合并完之后计算得到的 $X$ 便是答案。



我们假设 $m_i$ 是除数， $r_i$ 是余数，先看前两个方程。

$X\%m_0=r_0$ 与 $X\%m_1=r_1$ ，等价于 $X=m_0×k_0+r_o=m_1×k_1+r_1$ ，其中 $k_i$ 为一整数。

联立可得 $m_0×k_0+m_1×k_1=r_1-r_0$ （因为 $k_i$ 为一整数，所以移项之后前面的符号便不重要啦）



**扩展欧几里得算法中说：**存在整数对 $(x,y)$ 使得 $ax+by=\gcd(a,b)$

于是我们可以根据上面联立得出的式子构造出 $m_0x+m_1y=\gcd(m_0,m_1)$



通过 $ex\_gcd$ 可以求出 $\gcd(m_0,m_1)$ 以及 $x,y$  。

于是便有 $k_0=x×\frac{r_1-r_0}{\gcd(m_0,m_1)}$ 

带回原来的式子可以解得 $X=m_0×k_0+r_0$ ，此时 $X$ 的通解为 $X'=X+k×lcm(m_0,m_1)$ （ $k$ 为一整数，想要让 $X'\%m_0=r_0,X'\%m_1=r_1$ 这两个式子同时成立，$X$ 每次增加的步长应该是 $lcm(m_0,m_1)$ ）

**上式可转化成：** $X'\%lcm(m_0,m_1)=X$



于是这两个方程便合并啦~

合并完所有的方程以后，输出最小的正整数 $X'$ 就可以啦~

---

**关于代码中求 $k_0$ 时为什么要** $mod\frac{m_i}{\gcd(M,m_i)}$

$a×x_0+b×y_0=\gcd(a,b)$ 等同于 $a×x_0+\frac{a×b}{\gcd(a,b)}k+b×y_0-\frac{a×b}{\gcd(a,b)}k=\gcd(a,b)$

即 $a×(x_0+\frac{b}{\gcd(a,b)}k)+b×(y_0-\frac{a}{\gcd(a,b)}k)=\gcd(a,b)$

通解为 $x=x_0+\frac{b}{\gcd(a,b)}k$ ， $y=y_0-\frac{a}{\gcd(a,b)}k$ ，其中 $k=...-2,-1,0,1,2...$

于是在所有解中 $x$ 的最小正整数解为 $(x_0+\frac{b}{\gcd(a,b)})\%\frac{b}{\gcd(a,b)}$ ， $y$ 也一样。

所以 $mod\frac{m_i}{\gcd(M,m_i)}$ 保证了 $k_0$ 落在了一个指定的合理区间内。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define INF (1<<25)

typedef __int64 LL;
#define maxn 10005
LL m[maxn],r[maxn];
int n;

LL ex_gcd(LL a, LL b, LL &x, LL &y)
{
    LL d = a;
    if(b != 0)
    {
        d  = ex_gcd(b, a % b, y, x);
        y -= (a/b) * x;
    }
    else x = 1, y = 0;
    return d;
}

LL solve()
{
    LL M=m[0],R=r[0],gcd,x,y;
    for(int i=1; i<n; i++)
    {
        gcd=ex_gcd(M,m[i],x,y); // 扩展欧几里得求系数 x y gcd
        if((r[i]-R)%gcd)return -1;  // 如果无法整除即无解
        LL k=(r[i]-R)/gcd*x%(m[i]/gcd); // 求k0
        LL X=k*M+R;     // 代回原式求X
        M=M/gcd*m[i];   // M变为lcm
        R=(X+M)%M;      // R变为此时最小的X
    }
    return R;
}

int main()
{
    while (~scanf("%d",&n))
    {
        for (int i = 0; i < n; ++i)
            scanf("%I64d%I64d", &m[i], &r[i]);
        printf("%I64d\n",solve());
    }
    return 0;
}
```

