/*

HDU 1114：Piggy-Bank


　　一道完全背包的模版题，只不过题目中要求的是最小值，那么首先给dp数组设置一个很大的数，max函数改成min就可以了。
　　状态转移方程：dp[j]=min(dp[j],dp[j-a[i].weight]+a[i].value);

完全背包问题 ：
　　有N种物品和一个容量为V的背包，每种物品都有无限件可用。第i种物品的费用是c[i]，价值是w[i]。求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。 


基本思路 ：
　　这个问题非常类似于01背包问题，所不同的是每种物品有无限件。也就是从每种物品的角度考虑，与它相关的策略已并非取或不取两种，而是有取0件、取1件、取2件……等很多种。如果仍然按照解01背包时的思路，令f[i][v]表示前i种物品恰放入一个容量为v的背包的最大权值。仍然可以按照每种物品不同的策略写出状态转移方程，像这样：f[i][v]=max{f[i-1][v-k*c[i]]+k*w[i]|0<=k*c[i]<= v}。这跟01背包问题一样有O(N*V)个状态需要求解，但求解每个状态的时间则不是常数了，求解状态f[i][v]的时间是O(v/c[i])，总的复杂度是超过O(VN)的。 


一个简单有效的优化 ：
　　完全背包问题有一个很简单有效的优化，是这样的：若两件物品i、j满足c[i]<=c[j]且w[i]>=w[j]，则将物品j去掉，不用考虑。这个优化的正确性显然：任何情况下都可将价值小费用高得j换成物美价廉的i，得到至少不会更差的方案。对于随机生成的数据，这个方法往往会大大减少物品的件数，从而加快速度。然而这个并不能改善最坏情况的复杂度，因为有可能特别设计的数据可以一件物品也去不掉。 


转化为01背包问题求解 ：
　　既然01背包问题是最基本的背包问题，那么我们可以考虑把完全背包问题转化为01背包问题来解。最简单的想法是，考虑到第i种物品最多选V/c [i]件，于是可以把第i种物品转化为V/c[i]件费用及价值均不变的物品，然后求解这个01背包问题。这样完全没有改进基本思路的时间复杂度，但这毕竟给了我们将完全背包问题转化为01背包问题的思路：将一种物品拆成多件物品。 


更高效的转化方法是：
　　把第i种物品拆成费用为c[i]*2^k、价值为w[i]*2^k的若干件物品，其中k满足c[i]*2^k<V。这是二进制的思想，因为不管最优策略选几件第i种物品，总可以表示成若干个2^k件物品的和。这样把每种物品拆成O(log(V/c[i]))件物品，是一个很大的改进。但我们有更优的O(VN)的算法。 * O(VN)的算法这个算法使用一维数组，伪代码： 

for i=1..N  
 for v=0..V  
   f[v]=max{f[v],f[v-c[i]]+w[i]};   

*/

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


