# Kanade's sum

## **Description**

> Give you an array $A[1..n]$ of length $n$ . 
>
> Let $f(l,r,k)$ be the k-th largest element of $A[l..r]$ .
>
> Specially , $f(l,r,k)=0$ if $r−l+1<k$ .
>
> Give you $k$ , you need to calculate $\sum^n_{l=1}\sum^n_{r=l}f(l,r,k)$
>
> There are T test cases.
>
> $1≤T≤10$
>
> $k≤min(n,80)$
>
> $A[1..n]$ is a permutation of $[1..n]$
>
> $\sum n≤5∗10^5$



## **Input**

> There is only one integer T on first line.
>
> For each test case,there are only two integers $n,k$ on first line,and the second line consists of n integers which means the array $A[1..n]$



## **Output**

> For each test case,output an integer, which means the answer.



## **Sample Input**

    1
    5 2
    1 2 3 4 5



## **Sample Output**

    30


## **题意**

给出 `n` 和 `k` ，求 `1~n` 排列中每个区间的第 `k` 大数的总和是多少，区间长度小于 `k` 时贡献为 `0` 。



## **思路**

考虑枚举包含某个数字且其为第 `k` 大数的区间有多少个，我们只需要找出它左边最近的 `k` 个比它大的和右边最近的 `k` 个比它大的，然后就可以计算出该数字对最终结果的贡献。

可以从小到大枚举每个数字 `x` ，维护一个链表，链表里只有 `> = x` 的数，在得出该数的结果后删除 `x` 可以使得链表长度减少，从而优化时间。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef __int64 LL;

const int maxn = 5e5+10;
int a[maxn];
int pre[maxn];
int nex[maxn];
int wei[maxn];
int stk1[85];
int stk2[85];
int top1,top2;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,k;
        scanf("%d%d",&n,&k);
        for(int i=1; i<=n; i++)
        {
            scanf("%d",a+i);
            wei[a[i]]=i;
            pre[i]=i-1;
            nex[i]=i+1;
        }
        pre[0]=-1,nex[n+1]=n+2;
        LL ans=0;
        for(int i=1; i<=n; i++)
        {
            int x=wei[i];
            top1=top2=0;
            for(int j=x; j>=0&&top1<=k; j=pre[j])
                stk1[++top1]=j;
            for(int j=x; j<=n+1&&top2<=k; j=nex[j])
                stk2[++top2]=j;
            for(int j=k-top2+2; j<=top1-1; j++)
                ans+=LL(stk1[j]-stk1[j+1])*LL(stk2[k-j+2]-stk2[k-j+1])*i;
            nex[pre[x]]=nex[x];
            pre[nex[x]]=pre[x];
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
```

