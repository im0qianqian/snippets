# **HDU 4336 Card Collector**

## **Problem Description**

> In your childhood, do you crazy for collecting the beautiful cards in the snacks? They said that, for example, if you collect all the 108 people in the famous novel Water Margin, you will win an amazing award.
>
> As a smart boy, you notice that to win the award, you must buy much more snacks than it seems to be. To convince your friends not to waste money any more, you should find the expected number of snacks one should buy to collect a full suit of cards.



## **Input**

> The first line of each test case contains one integer $N (1 <= N <= 20)$, indicating the number of different cards you need thecollect. The second line contains $N$ numbers $p1, p2, ..., pN, (p1 + p2 + ... + pN <= 1)$, indicating the possibility of each card to appear in a bag of snacks. 
>
> Note there is at most one card in a bag of snacks. And it is possible that there is nothing in the bag.



## **Output**

> Output one number for each test case, indicating the expected number of bags to buy to collect all the N different cards.
>
> You will get accepted if the difference between your answer and the standard answer is no more that $10^{-4}$.



## **Sample Input**

    1
    0.1
    2
    0.1 0.4



## **Sample Output**

    10.000
    10.500



## **题意**

在你的童年有过收集零食里面的卡片的经历吧！当你集得所有卡片的时候你会获得很多奖励。

输入的第一行代表需要集得卡片的数量$N$，接下来的一行有N个实数，代表每张卡片出现的概率，问最少需要买多少零食才可以集全所有卡片。



## **思路**

### **容斥原理** ###

假设第一张卡片出现概率为 $P_1$ ，我们要获得它需要花费 $1.0/P_1$ ，同理，其他卡片的花费也是如此 $1.0/P_n$ ，但是我们在 $P_1$ 中花费时也有可能出现 $P_2$ 、 $P_3$ 。

于是很容易想到容斥原理，求得所有卡片花费集合的并便是答案。



### **概率dp**

用 $dp[i]$ 表示 $i$ 用二进制表示状态的期望值，然后二进制每一位代表卡片的状态，1为已得到，0为没有得到。

假设总共有五张卡片，那么 $i$ 最大为 $2^5-1$ ，此时是全1状态，它是由前面很多状态转移得到的。

比如：我们要计算 $dp[(10101)_2]$ ，它可以由 $(00101)_2~(10001)_2~(10100)_2$ 分别改变对应位状态得到，代表当前位的卡片我已经得到了，概率为 $P_i$ 。

而当前要计算的状态我们认为一定会得到，因为这是必须的，默认置 $dp[i]=1$ ，于是很容易便可以求出当前的期望值。

- 每一个状态都是由比它小的其他状态通过改变一位二进制数转移得到的
- 从 $dp[0]$ 一直计算到 $dp[2^n-1]$ 。
- 最后一个全 $1$ 状态的值即获得所有卡片的期望数量。





## **容斥原理**

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double a[25];
void solve(int N)
{
    double ans=0.0;
    for(int msk=1; msk<(1<<N); msk++)
    {
        double sum=0;
        int flag=0;
        for(int i=0; i<N; i++)
        {
            if(msk&(1<<i))  //选中一个二进制位
            {
                ++flag;
                sum+=a[i];
            }
        }
        if(flag&1)ans+=1.0/sum; //奇加偶减
        else ans-=1.0/sum;
    }
    printf("%lf\n",ans);
}

int main()
{
    int N;
    while(~scanf("%d",&N))
    {
        for(int i=0; i<N; i++)
            scanf("%lf",a+i);
        solve(N);
    }
    return 0;
}
```



## **概率dp** ##

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
using namespace std;
double a[25],dp[1<<25];
void solve(int T)
{
    int maxx=(1<<T)-1;
    dp[0]=0;
    for(int i=1; i<=maxx; i++)
    {
        double tmp=0;
        dp[i]=1;    //当前状态一定会成功1*P/P
        for(int j=0; j<T; j++)
        {
            if((1<<j)&i)    //找到1位
            {
                dp[i]+=dp[i-(1<<j)]*a[j];   //计算前项期望*转移概率
                tmp+=a[j];  //计算概率和
            }
        }
        dp[i]/=tmp;
    }
    printf("%lf\n",dp[maxx]);
}
int main()
{
    int T;
    while(~scanf("%d",&T))
    {
        for(int i=0; i<T; i++)
            scanf("%lf",a+i);
        solve(T);
    }
    return 0;
}
```

