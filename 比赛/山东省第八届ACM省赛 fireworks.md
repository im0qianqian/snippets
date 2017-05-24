# fireworks

## **Description**

> Hmz likes to play fireworks, especially when they are put regularly.
>
> Now he puts some fireworks in a line. This time he put a trigger on each firework. With that trigger, each firework will explode and split into two parts per second, which means if a firework is currently in position x, then in next second one part will be in position x−1 and one in x+1. They can continue spliting without limits, as Hmz likes.
>
> Now there are n fireworks on the number axis. Hmz wants to know after T seconds, how many fireworks are there in position w?
>
> ![img](http://acm.sdut.edu.cn/image/3895.png)



## **Input**

> Input contains multiple test cases.
>
> For each test case:
>
> The first line contains 3 integers n,T,w(n,T,|w|≤10^5)
>
> In next n lines, each line contains two integers xi and ci, indicating there are ci fireworks in position xi at the beginning(ci,|xi|≤10^5).



## **Output**

> For each test case, you should output the answer MOD 1000000007.



## **Example Input**

    1 2 0
    2 2
    2 2 2
    0 3
    1 2



## **Example Output**

    2
    3



## **题意**

烟花在每秒都会分裂一次，并且分裂成的两半刚好落在相邻的两点，然后它们也可以继续分裂。

给出 `n` 个点烟花的初始数量，问经过 `T` 秒后在点 `w` 有多少数量的烟花。



## **思路**

考虑所有的烟花分裂都是一样的，并且其分裂之后所形成的局势仅和时间有关。

**所以我们只需要关心一个烟花是如何分裂的：**

    0 0 0 0 0 1 0 0 0 0 0
    0 0 0 0 1 0 1 0 0 0 0
    0 0 0 1 0 2 0 1 0 0 0
    0 0 1 0 3 0 3 0 1 0 0
    0 1 0 4 0 6 0 4 0 1 0

第几行代表第几秒，行中的每个数字代表当前时间该点烟花的数量，于是我们发现了一个中间插入了 `0` 的杨辉三角，计算方法也就是组合数咯~

从上面的矩阵我们可以发现，当时间与距离同奇偶的时候才处于杨辉三角中，其余情况都为 `0` 。

---

因为题目中数据比较大，所以计算组合数需要用到乘法逆元，先打表求出 `n!` ，然后根据组合数公式计算即可。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define eps (1e-8)
const int mod = 1e9+7;
typedef long long LL;
LL jie[110000];

void init()
{
    jie[0]=jie[1]=1;
    for(int i=2; i<=100000; i++)
        jie[i]=(jie[i-1]*i)%mod;
}

LL mult(LL a,LL n)
{
    LL ans=1;
    while(n)
    {
        if(n&1)ans=(ans*a)%mod;
        a=(a*a)%mod;
        n>>=1;
    }
    return ans;
}

LL C(LL n,LL m)
{
    return ((jie[n]*mult(jie[n-m],mod-2))%mod*mult(jie[m],mod-2))%mod;
}

int main()
{
    init();
    int n,t,w;
    while(cin>>n>>t>>w)
    {
        LL ans=0;
        for(int i=0; i<n; i++)
        {
            LL x,c;
            cin>>x>>c;
            LL k=abs(w-x);
            if((k&1)==(t&1)&&k<=t)
                ans=(ans+(c*C(t,(k+t)/2))%mod)%mod;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

