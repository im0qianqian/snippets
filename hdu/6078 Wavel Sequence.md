# Wavel Sequence

## **Description**

> Have you ever seen the wave? It's a wonderful view of nature. Little Q is attracted to such wonderful thing, he even likes everything that looks like wave. Formally, he defines a sequence a1,a2,...,an as ''wavel'' if and only if a1 < a2 > a3 < a4 > a5 < a6...
>
> ![img](http://acm.hdu.edu.cn/data/images/C762-1012-1.jpg)
>
> Now given two sequences a1,a2,...,an and b1,b2,...,bm, Little Q wants to find two sequences f1,f2,...,fk(1≤fi≤n,fi<fi+1) and g1,g2,...,gk(1≤gi≤m,gi<gi+1), where afi=bgi always holds and sequence af1,af2,...,afk is ''wavel''.
>
> Moreover, Little Q is wondering how many such two sequences f and g he can find. Please write a program to help him figure out the answer.



## **Input**

> The first line of the input contains an integer T(1≤T≤15), denoting the number of test cases.
>
> In each test case, there are 2 integers n,m(1≤n,m≤2000) in the first line, denoting the length of a and b.
>
> In the next line, there are n integers a1,a2,...,an(1≤ai≤2000), denoting the sequence a.
>
> Then in the next line, there are m integers b1,b2,...,bm(1≤bi≤2000), denoting the sequence b.



## **Output**

> For each test case, print a single line containing an integer, denoting the answer. Since the answer may be very large, please print the answer modulo 998244353.



## **Sample Input**

    1
    3 5
    1 5 3
    4 1 1 5 3



## **Sample Output**

    10



## **题意**

定义波浪序列为满足 a1< a2 > a3 < a4 ... 的序列，现给出两个数组 a 和 b ，从 a 中选出满足波浪序列的一个子序列 f ， b 中选出满足波浪序列的子序列 g ，求有多少种选法满足 f = g 。



## **思路**

`dp[0][j]` 代表以 `b[j]` 结尾且最后为波谷的情况数目。

`dp[1][j]` 代表以 `b[j]` 结尾且最后为波峰的情况数目。

显然，结尾为波谷的情况可以由 **波峰 + 一个小的数** 转移而来，而结尾为波峰的情况可以由 **波谷 + 一个大的数** 转移而来。

因此我们定义 `ans0、ans1` 分别表示在该轮中相对于 `a[i]` 来说 `b[j]` 可作为波谷与波峰的数目。



枚举每一个 `a[i]` ，并且判断其与 `b[j]` 的大小关系：

- 若 `a[i] < b[j]` ，则说明 `b[j]` 可作为一个波峰出现
- 若 `a[i] > b[j]` ，则说明 `b[j]` 可作为一个波谷出现
- 若 `a[i] = b[j]` ，则说明找到一个对 `f = g` 有贡献的值，更新答案



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef __int64 LL;

const int mod = 998244353;
const int maxn = 2100;

int a[maxn],b[maxn];
LL dp[2][maxn];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0; i<n; i++)
            scanf("%d",a+i);
        for(int i=0; i<m; i++)
            scanf("%d",b+i);
        memset(dp,0,sizeof(dp));
        LL ans=0;
        for(int i=0; i<n; i++)
        {
            LL ans1=1,ans0=0;   // 该轮最后一个为波峰/波谷的数量
            for(int j=0; j<m; j++)
            {
                if(a[i]==b[j])  // 当前位有两种状态（波峰、波谷），可分别由之前的波谷、波峰转移而来
                {
                    dp[1][j]+=ans0;
                    dp[0][j]+=ans1;
                    ans=(ans+ans0+ans1)%mod;
                }
                else if(a[i]<b[j])  //  b[j] 可相对于 a[i] 做波峰
                    ans1=(ans1+dp[1][j])%mod;
                else ans0=(ans0+dp[0][j])%mod;  // 反之亦然
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
```

