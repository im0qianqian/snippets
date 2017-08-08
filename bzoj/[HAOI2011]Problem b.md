# [HAOI2011]Problem b

## **Description**

> 对于给出的 $n$ 个询问，每次求有多少个数对 $(x,y)$ ，满足 $a≤x≤b,c≤y≤d$ ，且 $\gcd(x,y) = k$ ，$\gcd(x,y)$ 函数为 $x$ 和 $y$ 的最大公约数。 



## **Input**

> 第一行一个整数 $n$ ，接下来 $n$ 行每行五个整数，分别表示 $a、b、c、d、k$



## **Output**

> 共 $n$ 行，每行一个整数表示满足要求的数对 $(x,y)$ 的个数



## **Sample Input**

    2
    2 5 1 5 1
    1 5 1 5 2



## **Sample Output**


    14
    3



## **思路**

首先我们可以利用容斥原理将一个询问分解为四个，每次询问有多少个数对 $(x,y)$ 满足 $1<=x<=n,1<=y<=m$ 且 $\gcd(x,y)=k$ 。

然后问题便等价于询问有多少个数对 $(x,y)$ 满足 $1<=x<=\lfloor\frac{n}{k}\rfloor,1<=y<=\lfloor\frac{m}{k}\rfloor$ 且 $x$ 与 $y$ 互质。

**PS：这道题目的时间限制有 50s ，不过也千万别想枚举过掉它，因为 $O(n^3)$ 的复杂度在 $n=1e5$ 的情况下可能要跑好久好久。**

**我们考虑使用莫比乌斯反演**

因为之前的结论，我们可以令 $f(i)$ 为 $1<=x<=n,1<=y<=m$ 且 $\gcd(x,y)=i$ 的数对 $(x,y)$ 的个数， $F(i)$ 为 $1<=x<=n,1<=y<=m$ 且 $i|\gcd(x,y)$ 的数对 $(x,y)$ 的个数，满足 $F(i)=\sum_{i|d}f(d)$ 。

显然，我们有 $F(i)=\lfloor\frac{n}{i}\rfloor\lfloor\frac{m}{i}\rfloor$

反演之后即 $f(i)=\sum_{i|d}μ(\frac{d}{i})F(d)=\sum_{i|d}μ(\frac{d}{i})\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor$

枚举原题中 $k​$ 的倍数，我们就可以在 $O(n)​$ 的时间处理每一个询问了，不过 $O(n)​$ 还不能胜任本题的数据范围，于是我们考虑进一步优化。

我们发现，对于其中连续的 $s$ 项，有可能有 $\lfloor\frac{n}{d}\rfloor=\lfloor\frac{n}{d+s}\rfloor$ ，那么对于这 $s$ 项的贡献，我们可以直接得出，即 $(Sum_{d+s}-Sum_{d-1})×\frac{n}{d}×\frac{m}{d}$ ，其中 $Sum_i$ 代表莫比乌斯函数的前 $i$ 项和。

观察式子，我们发现 $\lfloor\frac{n}{d}\rfloor$ 最多有 $2\sqrt{n}$ 个取值，于是 $\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor$ 至多有 $2(\sqrt{n}+\sqrt{m})$ 个取值，所以我们只需要枚举这 $2(\sqrt{n}+\sqrt{m})$ 个取值就可以了。

**PS：关于如何求出二元组 $(\frac{n}{x},\frac{m}{x})$ 取值范围相同的一段：对于当前点 $x$ ，其向右延伸最远为 $\min(\frac{n}{\frac{n}{x}},\frac{m}{\frac{m}{x}})$ ，因为 $\frac{n}{x}$ 为下界，那么 $\frac{n}{\frac{n}{x}}$ 就是上界咯。**



## **AC 代码**

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 1e5+10;
typedef long long LL;
bool check[maxn];
int prime[maxn];
int mu[maxn];
LL sum[maxn];

void Moblus()
{
    memset(check,false,sizeof(check));
    mu[1]=1;
    int tot=0;
    for(int i=2; i<maxn; i++)
    {
        if(!check[i])
        {
            prime[tot++]=i;
            mu[i]=-1;
        }
        for(int j=0; j<tot && i*prime[j]<maxn; j++)
        {
            int num=i*prime[j];
            check[num]=true;
            if(i%prime[j]==0)
            {
                mu[num]=0;
                break;
            }
            else
            {
                mu[num]=-mu[i];
            }
        }
    }
}

LL solve(int n,int m)
{
    LL ans=0;
    if(n>m)swap(n,m);
    for(int i=1,la=0; i<=n; i=la+1)
    {
        la=min(n/(n/i),m/(m/i));
        ans+=(sum[la]-sum[i-1])*(m/i)*(n/i);
    }
    return ans;
}

int main()
{
    Moblus();
    for(int i=1; i<maxn; i++)
        sum[i]=sum[i-1]+mu[i];
    int a,b,c,d,k,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        LL ans=solve(b/k,d/k)-solve((a-1)/k,d/k)-solve(b/k,(c-1)/k)+solve((a-1)/k,(c-1)/k);
        printf("%lld\n",ans);
    }
    return 0;
}
```

