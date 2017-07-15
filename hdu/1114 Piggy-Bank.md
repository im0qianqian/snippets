# Piggy-Bank

## **Problem Description**

> Before ACM can do anything, a budget must be prepared and the necessary financial support obtained. The main income for this action comes from Irreversibly Bound Money (IBM). The idea behind is simple. Whenever some ACM member has any small money, he takes all the coins and throws them into a piggy-bank. You know that this process is irreversible, the coins cannot be removed without breaking the pig. After a sufficiently long time, there should be enough cash in the piggy-bank to pay everything that needs to be paid.But there is a big problem with piggy-banks. It is not possible to determine how much money is inside. So we might break the pig into pieces only to find out that there is not enough money. Clearly, we want to avoid this unpleasant situation. The only possibility is to weigh the piggy-bank and try to guess how many coins are inside. Assume that we are able to determine the weight of the pig exactly and that we know the weights of all coins of a given currency. Then there is some minimum amount of money in the piggy-bank that we can guarantee. Your task is to find out this worst case and determine the minimum amount of cash inside the piggy-bank. We need your help. No more prematurely broken pigs!



## **Input**

> The input consists of T test cases. The number of them (T) is given on the first line of the input file. Each test case begins with a line containing two integers E and F. They indicate the weight of an empty pig and of the pig filled with coins. Both weights are given in grams. No pig will weigh more than 10 kg, that means 1 <= E <= F <= 10000. On the second line of each test case, there is an integer number N (1 <= N <= 500) that gives the number of various coins used in the given currency. Following this are exactly N lines, each specifying one coin type. These lines contain two integers each, Pand W (1 <= P <= 50000, 1 <= W <=10000). P is the value of the coin in monetary units, W is it's weight in grams.



## **Output**

> Print exactly one line of output for each test case. The line must contain the sentence "The minimum amount of money in the piggy-bank is X." where X is the minimum amount of money that can be achieved using coins with the given total weight. If the weight cannot be reached exactly, print a line "This is impossible.".



## **Sample Input**

    3
    10 110
    2
    1 1
    30 50
    10 110
    2
    1 1
    50 30
    1 6
    2
    10 3
    20 4



## **Sample Output**

    The minimum amount of money in the piggy-bank is 60.
    The minimum amount of money in the piggy-bank is 100.
    This is impossible.


## **思路**

　　一道完全背包的模版题，只不过题目中要求的是最小值，那么首先给 dp数组 设置一个很大的数，max函数改成min就可以了。

**状态转移方程：** `dp[j]=min(dp[j],dp[j-a[i].weight]+a[i].value);`



### **完全背包问题：**

　　有 `N` 种物品和一个容量为 `V` 的背包，每种物品都有无限件可用。第 `i` 种物品的费用是 `c[i]` ，价值是 `w[i]` 。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。 



#### **基本思路：**

　　这个问题非常类似于01背包问题，所不同的是每种物品有无限件。也就是从每种物品的角度考虑，与它相关的策略已并非取或不取两种，而是有取 `0` 件、取 `1` 件、取 `2` 件……等很多种。如果仍然按照解01背包时的思路，令 `f[i][v]` 表示前 `i` 种物品恰放入一个容量为 `v` 的背包的最大权值。仍然可以按照每种物品不同的策略写出状态转移方程，像这样： `f[i][v]=max{f[i-1][v-k*c[i]]+k*w[i]|0<=k*c[i]<=v}` 。这跟01背包问题一样有 `O(N*V)` 个状态需要求解，但求解每个状态的时间则不是常数了，求解状态 `f[i][v]` 的时间是 `O(v/c[i])` ，总的复杂度是超过 `O(VN)` 的。



#### **一个简单有效的优化：**

　　完全背包问题有一个很简单有效的优化，是这样的：若两件物品 `i、j` 满足 `c[i]<=c[j]` 且 `w[i]>=w[j]` ，则将物品 `j` 去掉，不用考虑。这个优化的正确性显然：任何情况下都可将价值小费用高的 `j` 换成物美价廉的 `i` ，得到至少不会更差的方案。

　　对于随机生成的数据，这个方法往往会大大减少物品的件数，从而加快速度。然而这并不能改善最坏情况的复杂度，因为有可能特别设计的数据可以一件物品也去不掉。



#### **转化为01背包问题求解：**

　　既然01背包问题是最基本的背包问题，那么我们可以考虑把完全背包问题转化为01背包问题来解。最简单的想法是，考虑到第 `i` 种物品最多选 `V/c[i]` 件，于是可以把第 `i` 种物品转化为 `V/c[i]` 件费用及价值均不变的物品，然后求解这个01背包问题。

　　这样完全没有改进基本思路的时间复杂度，但这毕竟给了我们将完全背包问题转化为01背包问题的思路：将一种物品拆成多件物品。



#### **更高效的转化方法是：**

　　把第 `i` 种物品拆成费用为 `c[i]*2^k` ，价值为 `w[i]*2^k` 的若干件物品，其中 `k` 满足 `c[i]*2^k<V` 。这是二进制的思想，因为不管最优策略选几件第 `i` 种物品，总可以表示成若干个 `2^k` 件物品的和。这样把每种物品拆成 `O(log(V/c[i]))` 件物品，是一个很大的改进。但我们有更优的 `O(VN)` 的算法。

`O(VN)` 的算法使用一维数组，伪代码如下：

```cpp
for i=1..N
 for v=0..V
   f[v]=max{f[v],f[v-c[i]]+w[i]};
```



## **AC 代码**

```cpp
#include <iostream>
#include <string.h>
#include<stdio.h>
using namespace std;
int dp[1000005];
struct po
{
    int value;
    int weight;
} a[1000005];
int solve(int ma,int n)
{
    fill(dp,dp+ma+105,10000000);
    dp[0]=0;
    for(int i=0; i<n; i++)
        for(int j=a[i].weight; j<=ma; j++)
            dp[j]=min(dp[j],dp[j-a[i].weight]+a[i].value);
    if(dp[ma]==10000000)return -1;
    return dp[ma];
}
int main()
{
    int N;
    cin>>N;
    while(N--)
    {
        int ko,ma,n;
        cin>>ko>>ma;
        ma-=ko;
        cin>>n;
        for(int i=0; i<n; i++)
            cin>>a[i].value>>a[i].weight;
        int so=solve(ma,n);
        printf(so!=-1?"The minimum amount of money in the piggy-bank is %d.\n":"This is impossible.\n",so);
    }
    return 0;
}
```

