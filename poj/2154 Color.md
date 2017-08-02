# Color

## **Description**

> Beads of N colors are connected together into a circular necklace of N beads (N<=1000000000). Your job is to calculate how many different kinds of the necklace can be produced. You should know that the necklace might not use up all the N colors, and the repetitions that are produced by rotation around the center of the circular necklace are all neglected. 
>
> You only need to output the answer module a given number P. 



## **Input**

> The first line of the input is an integer X (X <= 3500) representing the number of test cases. The following X lines each contains two numbers N and P (1 <= N <= 1000000000, 1 <= P <= 30000), representing a test case.



## **Output**

> For each test case, output one line containing the answer.



## **Sample Input**

    5
    1 30000
    2 30000
    3 30000
    4 30000
    5 30000



## **Sample Output**

    1
    3
    11
    70
    629



## **题意**

有 `N` 种颜色的珠子要组成长度为 `N` 的项链，考虑旋转相同的情况算一种，求总共有多少种情况 mod P 。



## **思路**

从题意来看是一道 `Polya` 计数问题，于是我们想到公式 $L=\frac{1}{|G|}×\sum k^{C(f)},f\in G$ ，其中 $C(f)$ 为置换 $f$ 的循环节个数， $|G|$ 表示置换方法数。

因为只需要考虑旋转置换，于是 $C(f_i)=\gcd(n,i)$ ， $i$ 表示一次转过 $i$ 颗珠子，当 $i=0$ 时， $C(f_0)=N$ 。

---

再看 $N$ 的范围： $[1,1000000000]$ ，显然我们不能一一枚举每一个 $i$ 。

于是分析 $C(f_i)=x$ 在所有的 $\gcd(n,i)$ 中出现了多少次。

显然 $\gcd(n,i)=x$ 等同于 $\gcd(\frac{n}{x},\frac{i}{x})=1$ ，然后我们可以知道其出现次数便是 $\frac{n}{x}$ 的欧拉函数（其中 $x$ 为 $n$ 的因子）

**然后公式便被我们转化为了：** $L=\frac{1}{|G|}×\sum_{i|N}(k^i×phi[N/i])$ 。

---

素数表的辅助可以更快的求解欧拉函数的值，然后我们在枚举 $N$ 的因子时遍历长度只需要小于等于 $\sqrt N$ 即可，因为另一个因子可以通过计算直接得到。



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

typedef __int64 LL;

const int maxn = 40000;
int N,P;

int pr[maxn];
bool prime[maxn];

void getprime()         //筛法素数表
{
    int i,j,k=0;
    memset(prime,true,sizeof(prime));
    for(i=2; i<maxn; i++)
    {
        if(prime[i])
        {
            pr[k++]=i;
            for(j=i+i; j<maxn; j+=i)
                prime[j]=false;
        }
    }
}

int phi(int n)      //求欧拉函数
{
    int rea=n;
    for(int i=0; pr[i]*pr[i]<=n; i++)
    {
        if(n%pr[i]==0)
        {
            rea=rea-rea/pr[i];
            while(n%pr[i]==0)
                n/=pr[i];
        }
    }
    if(n>1)
        rea=rea-rea/n;
    return rea;
}

int mult(int a,int n)   //快速幂取模
{
    if(n<0)return 0;
    int ans=1;
    while(n)
    {
        if(n&1)ans=(ans*a)%P;
        a=(a*a)%P;
        n>>=1;
    }
    return ans;
}


int main()
{
    ios::sync_with_stdio(false);
    int T;
    getprime();
    cin>>T;
    while(T--)
    {
        cin>>N>>P;
        int ans=0;
        for(int i=1; i*i<=N; i++)
        {
            if(N%i==0)
            {
                int no=N/i;
                int oula=phi(no)%P;
                int foula=0;
                if(i*i!=N)
                    foula=phi(i)%P;
                ans=(ans+mult(N%P,i-1)*oula%P+mult(N%P,no-1)*foula%P)%P;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

