# Detachment

## **Problem Description**

> In a highly developed alien society, the habitats are almost infinite dimensional space.
>
> In the history of this planet,there is an old puzzle.
>
> You have a line segment with x units’ length representing one dimension.The line segment can be split into a number of small line segments: a1,a2, … (x= a1+a2+…) assigned to different dimensions. And then, the multidimensional space has been established. Now there are two requirements for this space: 
>
> 1．Two different small line segments cannot be equal ( ai≠aj when i≠j).
>
> 2．Make this multidimensional space size s as large as possible (s= a1×a2×...).Note that it allows to keep one dimension.That's to say, the number of ai can be only one.
>
> Now can you solve this question and find the maximum size of the space?(For the final number is too large,your answer will be modulo 10^9+7)



## **Input**

> The first line is an integer T,meaning the number of test cases.
>
> Then T lines follow. Each line contains one integer x. 1≤T≤10^6, 1≤x≤10^9



## **Output**

> Maximum s you can get modulo 10^9+7. Note that we wants to be greatest product before modulo 10^9+7.



## **Sample Input**

    1
    4



## **Sample Output**

    4



## **题意**

把一个数分解成若干不相等的数，使得这若干个数的积最大，输出最大的积 `mod(1e9+7)` 。



## **思路**

对于 `x` ，拆的数越多，积越大，但是因子中不能有 `1` 。

当 `a+b=n` 时，我们知道， `a=b=n/2` 时，乘积最大，题目中要求所有的数不能相等，于是我们只要让这些数互相靠近即可。

**有三种情况：**

1. $x=\sum_{i=2}^{n}i$ ，比如当 $x=20=2+3+4+5+6$ ，所有数的积为 $2×3×4×5×6$ ，此时数中没有 `1` ，并且达到饱和状态，因此乘积最大，最大乘积为 $n!$ 。
2. $x=\sum_{i=2}^{n}i-1$ ，比如当 $x=19=2+3+4+5+6-1$ ，多出的 `-1` 我们没有处理，这时要考虑舍弃掉最小的一个数 `2` ，然后让最大的数加一，也就是 $19=3+4+5+7$ ，因为贪心的思想这样得到的数的个数保证了最大，并且基本靠近，因此乘积最大，最大乘积为 $\frac{(n+1)!}{2×n}$ 。
3. $x=\sum_{i=2}^{n}i-k~(k>1)$ ，比如当 $x=15=2+3+4+5+6-5$ ，同样的道理，数中多出的 `-5` 我们要想办法除掉，方法即抵消掉序列中的两个 `5` ，也就是 $15=2+3+4+6$ ，此时乘积最大，最大乘积为 $\frac{n!}{(\sum_{i=2}^{n}i)-x}$ 。

做题的时候首先预处理出前 `n` 项的和与阶乘 `mod(1e9+7)` ，然后在计算中出现除法的时候要使用逆元，因为 `mod` 的关系，所以不能直接使用除法。



## **AC 代码**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include<iostream>
using namespace std;
#define maxn 50000
const int mod = 1e9+7;
typedef __int64 LL;
LL sum[maxn];
LL mu[maxn];

void init()
{
    mu[1]=1;
    for(int i=2; i<maxn; i++)
    {
        sum[i]=sum[i-1]+i;
        mu[i]=(mu[i-1]*i)%mod;
    }
    sum[1]=1;
}

LL mult(LL a,int n) // 快速幂
{
    LL ans=1;
    while(n)
    {
        if(n&1)ans=(ans*a)%mod;
        a=(a*a)%mod;
        n>>=1;
    }
    return ans;
}

int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        LL x;
        scanf("%I64d",&x);
        int index=lower_bound(sum,sum+maxn,x)-sum;
        LL ans;
        if(sum[index]==x)
            ans=mu[index];
        else
        {
            if(sum[index]==x+1)
                ans=((mu[index+1]*mult(index,mod-2))%mod*mult(2,mod-2))%mod;
            else
                ans=(mu[index]*mult(sum[index]-x,mod-2))%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
```

