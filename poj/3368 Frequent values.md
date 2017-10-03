# Frequent values

## **Description**

> You are given a sequence of n integers a1 , a2 , ... , an in non-decreasing order. In addition to that, you are given several queries consisting of indices i and j (1 ≤ i ≤ j ≤ n). For each query, determine the most frequent value among the integers ai , ... , aj.



## **Input**

> The input consists of several test cases. Each test case starts with a line containing two integers n and q (1 ≤ n, q ≤ 100000). The next line contains n integers a1 , ... , an (-100000 ≤ ai ≤ 100000, for each i ∈ {1, ..., n}) separated by spaces. You can assume that for each i ∈ {1, ..., n-1}: ai ≤ ai+1. The following q lines contain one query each, consisting of two integers i and j (1 ≤ i ≤ j ≤ n), which indicate the boundary indices for the query.
>
> The last test case is followed by a line containing a single 0.



## **Output**

> For each query, print one line with one integer: The number of occurrences of the most frequent value within the given range.



## **Sample Input**

    10 3
    -1 -1 1 1 1 1 3 10 10 10
    2 3
    1 10
    5 10
    0



## **Sample Output**

    1
    4
    3



## **题意**

求区间某个数字出现的最大次数。



## **思路**

题目中有一个很重要的性质，即原序列是不下降的，因此相等的数字一定是挨着的。

以样例来说吧： `-1 -1 1 1 1 1 3 10 10 10` 。

从左到右扫一遍记录每一个元素左边（包含）连续的相同数字有多少个，则处理后的序列为 `1 2 1 2 3 4 1 1 2 3` 。

根据这个序列 RMQ 建立 ST 表，我们将其记为 $ST$ 。

另外我们还需要一个序列 $tmp$ 从右往左扫一遍记录每个数值右端点的位置，即 `1 1 5 5 5 5 6 9 9 9` 。



**对于每一个查询 $l,r$ ：**

- 假如 $a_l=a_r$ ，说明查询区间都为同一数字，此时区间长度 $r-l+1$ 即为结果。
- 假如 $a_l=a_{l-1}$ ，说明区间左边截断了某种数字的一部分，此时的结果为 $\max(tmp_l-l+1,\max(ST[tmp_l+1],ST[r]))$
- 对于其他情况，结果为 $\max(ST[l],ST[r])$



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 2e5+10;
int maxx[30][maxn];
int a[maxn];
int tmp[maxn];
int n,q;

void rmq()
{
    for(int i=1; (1<<i)<=n; i++)
        for(int j=0; j+(1<<i)<=n; j++)
            maxx[i][j]=max(maxx[i-1][j],maxx[i-1][j+(1<<(i-1))]);
}

int query(int l,int r)
{
    int len=0;
    for(int i=0; 1<<(len+1)<=r-l+1; i++,len++);
    return max(maxx[len][l-1],maxx[len][r-(1<<len)]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>n&&n)
    {
        cin>>q;
        for(int i=0; i<n; i++)
            cin>>a[i];
        for(int i=0; i<n; i++)
        {
            if(i==0||a[i]!=a[i-1])
                maxx[0][i] = 1;
            else maxx[0][i] = maxx[0][i-1]+1;
        }
        int ind = n-1;
        for(int i=n-1; i>=0; i--)
        {
            if(a[ind]!=a[i])
                ind = i;
            tmp[i] = ind;
        }
        rmq();
        for(int i=0; i<q; i++)
        {
            int l,r,ans = 0;
            cin>>l>>r;
            --l,--r;
            if(a[l]==a[r])
                ans = r-l+1;
            else if(l>0&&a[l]==a[l-1])
                ans = max(tmp[l]-l+1,query(tmp[l]+2,r+1));
            else
                ans = query(l+1,r+1);
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

