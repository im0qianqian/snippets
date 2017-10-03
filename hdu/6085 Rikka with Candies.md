# Rikka with Candies

## **Description**

> As we know, Rikka is poor at math. Yuta is worrying about this situation, so he gives Rikka some math tasks to practice. There is one of them:
>
> There are n children and m kinds of candies. The ith child has Ai dollars and the unit price of the ith kind of candy is Bi. The amount of each kind is infinity. 
>
> Each child has his favorite candy, so he will buy this kind of candies as much as possible and will not buy any candies of other kinds. For example, if this child has 10 dollars and the unit price of his favorite candy is 4 dollars, then he will buy two candies and go home with 2 dollars left.
>
> Now Yuta has q queries, each of them gives a number k. For each query, Yuta wants to know the number of the pairs (i,j)(1≤i≤n,1≤j≤m) which satisfies if the ith child’s favorite candy is the jth kind, he will take k dollars home.
>
> To reduce the difficulty, Rikka just need to calculate the answer modulo 2.
>
> But It is still too difficult for Rikka. Can you help her?



## **Input**

> The first line contains a number t(1≤t≤5), the number of the testcases. 
>
> For each testcase, the first line contains three numbers n,m,q(1≤n,m,q≤50000). 
>
> The second line contains n numbers Ai(1≤Ai≤50000) and the third line contains m numbers Bi(1≤Bi≤50000).
>
> Then the fourth line contains q numbers ki(0≤ki<maxBi) , which describes the queries.
>
> It is guaranteed that Ai≠Aj,Bi≠Bj for all i≠j.



## **Output**

> For each query, print a single line with a single 01 digit -- the answer.



## **Sample Input**

    1
    5 5 5
    1 2 3 4 5
    1 2 3 4 5
    0 1 2 3 4



## **Sample Output**

    0
    0
    0
    0
    1



## **题意**

$A$ 数组有 $n$ 个数， $B$ 数组有 $m$ 个数，随后有 $q$ 个查询，每次输入一个 $k$ ，询问有多少对 $(i,j)$ ， 使得 $A_i\%B_j=k$ ， 输出结果模 $2$ 的值。



## **思路**

考虑枚举 $k$ ，显然只有当 $B_j>k,A_i>=k$ 时才可能满足 $A_i\%B_j=k$ 。

$A_i\%B_j=k$ 又等价于 $A_i-k=B_j \times x$ ，其中 $x$ 为某一整数。

我们用 $bitset$ 来存放 $A$ ，于是 $bitsetA>>k$ 相当于 $A$ 中所有元素减去 $k$ ，舍弃小于 $0$ 的元素。

用 $bitsetCNT$ 来存放 $B$ 的倍数， $bitsetCNT_i=1$ 代表有奇数个 $j$ 满足 $i\%B_j=0$ ，之所以只统计奇偶数是因为最终对结果模 $2$ 。

此时 $bitsetA>>k$ 相当于 $A_i-k$ ，然后 $(bitsetA>>k)\&bitsetCNT.count()\&1$ 相当于原问题的答案。



## **AC 代码**

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10;

bitset<maxn>a,b;
bitset<maxn>ans,cnt;

void slove(int maxK)
{
    cnt.reset();
    ans.reset();
    for(int i=maxK; i>=0; --i)  //枚举k
    {
        ans[i]=(cnt&(a>>i)).count()&1;   //存在多少个(a-i)%b=0
        if(b[i])        //枚举 i 的倍数
            for(int j=0; j<maxn; j+=i)
                cnt.flip(j);
    }
}

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9');
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0'), c = getchar();
    }
}

int main()
{
    int T;
    scan_d(T);
    while(T--)
    {
        int n,m,q;
        scan_d(n);
        scan_d(m);
        scan_d(q);
        a.reset();
        b.reset();
        int maxK=0;
        for(int i=0; i<n; ++i)
        {
            int x;
            scan_d(x);
            a.set(x);
        }
        for(int i=0; i<m; ++i)
        {
            int x;
            scan_d(x);
            b.set(x);
            maxK=max(maxK,x);
        }
        slove(maxK);
        while(q--)
        {
            int x;
            scan_d(x);
            puts(ans[x]?"1":"0");
        }
    }
    return 0;
}
```

