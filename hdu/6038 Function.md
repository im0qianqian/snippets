# Function

## **Description**

> You are given a permutation a from 0 to n−1 and a permutation b from 0 to m−1.
>
> Define that the domain of function f is the set of integers from 0 to n−1, and the range of it is the set of integers from 0 to m−1.
>
> Please calculate the quantity of different functions f satisfying that f(i)=bf(ai) for each i from 0 to n−1.
>
> Two functions are different if and only if there exists at least one integer from 0 to n−1 mapped into different integers in these two functions.
>
> The answer may be too large, so please output it in modulo 10^9+7.



## **Input**

> The input contains multiple test cases.
>
> For each case:
>
> The first line contains two numbers n, m. (1≤n≤100000,1≤m≤100000)
>
> The second line contains n numbers, ranged from 0 to n−1, the i-th number of which represents ai−1.
>
> The third line contains m numbers, ranged from 0 to m−1, the i-th number of which represents bi−1.
>
> It is guaranteed that ∑n≤106, ∑m≤106.



## **Output**

> For each test case, output "Case #x: y" in one line (without quotes), where x indicates the case number starting from 1 and y denotes the answer of corresponding case.



## **Sample Input**

    3 2
    1 0 2
    0 1
    3 4
    2 0 1
    0 2 3 1



## **Sample Output**

    Case #1: 4
    Case #2: 4


## **题意**

给出两个序列 a 和 b ，求满足 $f(i)=b_{f(a_i)}$ 的函数个数。



## **思路**

根据样例 1 我们可以得到：

$f(0)=b_{f(1)}$

$f(1)=b_{f(0)}$

$f(2)=b_{f(2)}$

代换以后有 $f(0)=b_{f(1)}=b_{b_{f(0)}}$ ， $f(1)=b_{f(0)}=b_{b_{f(1)}}$ ，也就是说，在这一个循环节中，我们只要确定其中一个数，其余的数都可以通过它来表示出来。

考虑置换 $a$ 的一个循环节，长度为 $l$ ，那么有 $f(i) = b_{f(a_i)} = b_{b_{f(a_{a_i})}} = \underbrace{b_{\cdots b_{f(i)}}}_{l\text{ times }b}$ 。

于是 $f(i)$ 的值在置换 $b$ 中所在的循环节的长度必须为 $l$ 的因数。

而如果 $f(i)$ 的值确定下来了，这个循环节的另外 $l - 1$ 个数的函数值也都确定下来了（刚刚所讨论的问题）。

因此满足条件的函数个数就是 $\sum_{i = 1}^{k} \sum_{j | l_i} {j \cdot cal_j}$ ，其中 $k$ 是置换 $a$ 中循环节的个数， $l_i$ 表示置换 $a$ 中第 $i$ 个循环节的长度， $cal_j$ 表示置换 $b$ 中长度为 $j$ 的循环节的个数。



## **AC 代码**

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;

typedef __int64 LL;
const int maxn=110000;
const int mod = 1e9+7;

int a[maxn],b[maxn];
vector<int> na,nb;
bool vis[maxn];

void findnum(int *a,int n,vector<int> &res)     //寻找 res 中的循环节个数以及长度
{
    memset(vis,false,sizeof(vis));
    for(int i=0; i<n; i++)
    {
        if(!vis[i])
        {
            int now=a[i],len=0;
            while(!vis[now])
            {
                ++len;
                vis[now]=true;
                now=a[now];
            }
            res.push_back(len);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int n,m,ti=0;
    while(cin>>n>>m)
    {
        na.clear();
        nb.clear();
        for(int i=0; i<n; i++)
            cin>>a[i];
        for(int i=0; i<m; i++)
            cin>>b[i];
        findnum(a,n,na);
        findnum(b,m,nb);
        LL ans=1;
        int lena=na.size();
        int lenb=nb.size();
        for(int i=0; i<lena; i++)
        {
            LL res=0;
            for(int j=0; j<lenb; j++)
            {
                if(na[i]%nb[j]==0)
                    res=(res+nb[j])%mod;
            }
            ans=(ans*res)%mod;
        }
        cout<<"Case #"<<++ti<<": "<<ans<<endl;
    }
    return 0;
}
```

