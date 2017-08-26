# Killer Names

## **Description**

> Galen Marek, codenamed Starkiller, was a male Human apprentice of the Sith Lord Darth Vader. A powerful Force-user who lived during the era of the Galactic Empire, Marek originated from the Wookiee home planet of Kashyyyk as the sole offspring of two Jedi Knights—Mallie and Kento Marek—who deserted the Jedi Order during the Clone Wars. Following the death of his mother, the young Marek's father was killed in battle by Darth Vader. Though only a child, Marek possessed an exceptionally strong connection to the Force that the Dark Lord of the Sith sought to exploit.
>
> When Marek died in 2 BBY, shortly after the formation of the Alliance, Vader endeavored to recreate his disciple by utilizing the cloning technologies of the planet Kamino. The accelerated cloning process—an enhanced version of the Kaminoan method which allowed for a rapid growth rate within its subjects—was initially imperfect and many clones were too unstable to take Marek's place as the Dark Lord's new apprentice. After months of failure, one particular clone impressed Vader enough for him to hope that this version might become the first success. But as with the others, he inherited Marek's power and skills at the cost of receiving his emotions as well, a side effect of memory flashes used in the training process.
>
> — Wookieepedia
>
> Darth Vader is finally able to stably clone the most powerful soilder in the galaxy: the Starkiller. It is the time of the final strike to destroy the Jedi remnants hidden in every corner of the galaxy.
>
> However, as the clone army is growing, giving them names becomes a trouble. A clone of Starkiller will be given a two-word name, a first name and a last name. Both the first name and the last name have exactly n characters, while each character is chosen from an alphabet of size m. It appears that there are m2n possible names to be used.
>
> Though the clone process succeeded, the moods of Starkiller clones seem not quite stable. Once an unsatisfactory name is given, a clone will become unstable and will try to fight against his own master. A name is safe if and only if no character appears in both the first name and the last name.
>
> Since no two clones can share a name, Darth Vader would like to know the maximum number of clones he is able to create.



## **Input**

> The First line of the input contains an integer T (T≤10), denoting the number of test cases. 
>
> Each test case contains two integers n and m (1≤n,m≤2000).



## **Output**

> For each test case, output one line containing the maximum number of clones Vader can create.
>
> Output the answer  mod 10^9+7



## **Sample Input**

    2
    3 2
    2 3



## **Sample Output**

    2 
    18



## **题意**

$m$ 种颜色需要为两段长度为 $n$ 的格子染色，且这两段之间不能出现相同的颜色，问总共有多少种情况。



## **思路**

枚举要为这两段分配的颜色数目分别为 $i,j$ ，则在第一段总共有 $\binom{m}{i}$ 种选取方案，在第二段总共有 $\binom{m-i}{j}$ 种选取方案。

而在每段内部，我们设 $F(n,x)$ 为长度为 $n$ 的格子使用 $x$ 种颜色（等于 $x$ ）染色的方案数。

则根据容斥原理 $F(n,x)=x^n-\binom{x}{1}(x-1)^n+\binom{x}{2}(x-2)^n-\binom{x}{3}(x-3)^n+...$

于是最终的结果便是所有 $\binom{m}{i}F(n,i)×\binom{m-i}{j}F(n,j)$ 之和。

---

**补充 2017.08.18**

第二类 Stirling 数 $S(p,k)$ 的一个组合学解释是：将 $p$ 个物体划分成 $k$ 个非空的不可辨别的集合的方法数。

因此上面的 $F(n,x)=x!×S(n,x)$ ，其中乘以 $x!$ 是因为此时我们的颜色（盒子）是不同的，可以任意排列。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int maxn =2005;
const int mod = 1e9+7;

LL res[maxn];
LL C[maxn][maxn];
LL mul[maxn][maxn];

LL mult(LL a,LL b)
{
    if(mul[a][b])return mul[a][b];
    LL ans=1,aa=a,bb=b;
    a%=mod;
    while(b)
    {
        if(b&1)ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    mul[aa][bb]=ans;
    return ans;
}

void init()
{
    C[0][0]=1;
    for(int i=1; i<maxn; i++)
        for(int j=0; j<=i; j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
}

LL getget(LL n,LL m)
{
    LL cnt=0;
    for(int k=0; k<=m; k++)
    {
        if(k&1)cnt=(cnt-C[m][k]*mult(m-k,n)%mod)%mod;
        else cnt=(cnt+C[m][k]*mult(m-k,n)%mod+mod)%mod;
    }
    return cnt;
}

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9');
    while (c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0'), c = getchar();
}

void Out(LL a)
{
    if (a < 0)
    {
        putchar('-');
        a = -a;
    }
    if (a >= 10)
        Out(a / 10);
    putchar(a % 10 + '0');
}

int main()
{
    init();
    int T;
    scan_d(T);
    while(T--)
    {
        memset(res,0,sizeof(res));
        int n,m;
        LL ans=0;
        scan_d(n);
        scan_d(m);
        for(int i=1; i<m; i++)
            res[i]=getget(n,i);
        for(int i=1; i<m; i++)
            for(int j=i; j<=m-i; j++)
            {
                LL aa=C[m][i]*res[i]%mod;
                LL bb=C[m-i][j]*res[j]%mod;
                LL cnt = (aa*bb)%mod;
                if(i!=j) cnt = (cnt+cnt)%mod;
                ans=(cnt+ans)%mod;
            }
        Out(ans);
        putchar('\n');
    }
    return 0;
}
```

