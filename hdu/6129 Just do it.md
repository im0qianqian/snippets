# Just do it

## **Description**

> There is a nonnegative integer sequence a1...n of length n. HazelFan wants to do a type of transformation called prefix-XOR, which means a1...n changes into b1...n, where bi equals to the XOR value of a1,...,ai. He will repeat it for m times, please tell him the final sequence.



## **Input**

> The first line contains a positive integer T(1≤T≤5), denoting the number of test cases.
>
> For each test case:
>
> The first line contains two positive integers n,m(1≤n≤2×10^5,1≤m≤10^9).
>
> The second line contains n nonnegative integers a1...n(0≤ai≤2^30−1).



## **Output**

> For each test case:
>
> A single line contains n nonnegative integers, denoting the final sequence.



## **Sample Input**

    2
    1 1
    1
    3 3
    1 2 3



## **Sample Output**

    1
    1 3 1


## **题意**

有一个长度为 n 的整数序列 $\{a_n\}$ ，对其做 m 次前缀异或和，求最终的序列。



## **思路**

> 可以发现做 m 次后，位置为 x 的初始值对位置为 y 的最终值的贡献次数是一个只和 m 与 y-x 相关的组合式，而我们只关注这个次数的奇偶性。考虑 Lucas 定理， $\binom{b}{a}$ 是奇数当且仅当把 a,b 二进制表达后 a 中 1 的位置是 b 中 1 的位置的子集，于是这里所有满足条件的 a 有很好的性质，对每一个二进制位独立处理就能算出答案。

容易得出，该组合数的计算公式为 $\binom{m+i-2}{i-1}$ ，其中 $m$ 已知，枚举所有的 $i$ ，当 $(i-1)\&(m+i-2)==(i-1)$ 时即说明该组合数的结果为奇数，则每一项对与其间隔为 $i$ 的数字有所贡献，统计更新即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
int a[maxn], b[maxn];

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n,m;
        scanf("%d%d", &n, &m);
        memset(b,0,sizeof(b));
        for(int i=1; i<=n; i++)
            scanf("%d", &a[i]);
        for(int i=1; i<n; i++)
        {
            int x=m+i-2,y=i-1;
            if((x&y)==y)
                for(int j=i; j<=n; j++)
                    b[j]^=a[j-i+1];
        }
        for(int i=1; i<=n; i++)
            printf(i!=n?"%d ":"%d\n",b[i]);
    }
    return 0;
}
```

