# Limited Permutation

## **Description**

> As to a permutation p1,p2,⋯,pn from 1 to n, it is uncomplicated for each 1≤i≤n to calculate (li,ri) meeting the condition that min(pL,pL+1,⋯,pR)=pi if and only if li≤L≤i≤R≤ri for each 1≤L≤R≤n.
>
> Given the positive integers n, (li,ri) (1≤i≤n), you are asked to calculate the number of possible permutations p1,p2,⋯,pn from 1 to n, meeting the above condition.
>
> The answer may be very large, so you only need to give the value of answer modulo 10^9+7.



## **Input**

> The input contains multiple test cases.
>
> For each test case:
>
> The first line contains one positive integer n, satisfying 1≤n≤106.
>
> The second line contains n positive integers l1,l2,⋯,ln, satisfying 1≤li≤i for each 1≤i≤n.
>
> The third line contains n positive integers r1,r2,⋯,rn, satisfying i≤ri≤n for each 1≤i≤n.
>
> It's guaranteed that the sum of n in all test cases is not larger than 3⋅10^6.
>
> Warm Tips for C/C++: input data is so large (about 38 MiB) that we recommend to use fread() for buffering friendly.
>
> size_t fread(void *buffer, size_t size, size_t count, FILE *stream); // reads an array of count elements, each one with a size of size bytes, from the stream and stores them in the block of memory specified by buffer; the total number of elements successfully read is returned.



## **Output**

> For each test case, output "Case #x: y" in one line (without quotes), where x indicates the case number starting from 1 and y denotes the answer of corresponding case.



## **Sample Input**

    3
    1 1 3
    1 3 3
    5
    1 2 2 4 5
    5 2 5 5 5



## **Sample Output**

    Case #1: 2
    Case #2: 3



## **题意**

给出 $n$ 组 $[l_i,r_i]$ 代表 $p_i$ 在这个区间内最小，求满足该要求的排列总共有多少种情况。



## **思路**

对于区间 $[l_i,r_i]$ ，我们可以将其分为 $[l_i,i-1]$ 和 $[i+1,r_i]$ 。

于是对整个区间 $[1,n]$ 进行递归分治搜索，每一个区间可贡献的值为其两个子区间贡献之积乘以 $C_{R-L}^{i-L}$ 。

PS：因为我们要在区间 $[L,R]$ 中选取 $i-L$ 个数放置在 $i$ 的左边，其中区间 $[L,R]$ 除去 $i$ 后剩 $R-L$ 个数，所以为 $C_{R-L}^{i-L}$ 。



## **AC 代码**

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<map>
using namespace std;
typedef pair<int,int> P;
typedef __int64 LL;
map<P,int> mapp;

const int maxn = 1e6+10;
const int mod = 1e9+7;
int l[maxn],r[maxn];
LL ans;
LL mul[maxn];
LL inv[maxn];

inline char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}

template <class T>
inline bool scan_d(T & x)
{
    char c=nc();
    x=0;
    if(c==EOF)return false;
    for(; c>'9'||c<'0'; c=nc());
    for(; c>='0'&&c<='9'; x=x*10+c-'0',c=nc());
    return true;
}

void init()
{
    mul[0]=1;
    for(int i=1; i<maxn; i++)
        mul[i]=(mul[i-1]*i)%mod;

    inv[0]=inv[1]=1;
    for(int i=2; i<maxn; i++)
        inv[i]=(LL)(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1; i<maxn; i++)
        inv[i]=(inv[i-1]*inv[i])%mod;
}

LL C(int n,int m)
{
    return mul[n]*inv[m]%mod*inv[n-m]%mod;
}

void dfs(int ll,int rr)
{
    if(ans==0||rr<ll)return;
    int i=mapp[P(ll,rr)];
    if(i==0)
    {
        ans=0;
        return;
    }
    if(ll==rr)return;
    int len=rr-ll;
    ans=(ans*C(len,i-ll))%mod;
    dfs(ll,i-1);
    dfs(i+1,rr);
}

int main()
{
    int n;
    init();
    for(int ti=1; scan_d(n); ti++)
    {
        mapp.clear();
        ans=1;
        for(int i=1; i<=n; i++)
            scan_d(l[i]);
        for(int i=1; i<=n; i++)
        {
            scan_d(r[i]);
            mapp[P(l[i],r[i])]=i;
        }
        dfs(1,n);
        printf("Case #%d: %I64d\n",ti,ans);
    }
    return 0;
}
```

