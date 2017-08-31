# Corn Fields

## **Description**

> Farmer John has purchased a lush new rectangular pasture composed of M by N (1 ≤ M ≤ 12; 1 ≤ N ≤ 12) square parcels. He wants to grow some yummy corn for the cows on a number of squares. Regrettably, some of the squares are infertile and can't be planted. Canny FJ knows that the cows dislike eating close to each other, so when choosing which squares to plant, he avoids choosing squares that are adjacent; no two chosen squares share an edge. He has not yet made the final choice as to which squares to plant.
>
> Being a very open-minded man, Farmer John wants to consider all possible options for how to choose the squares for planting. He is so open-minded that he considers choosing no squares as a valid option! Please help Farmer John determine the number of ways he can choose the squares to plant.



## **Input**

> Line 1: Two space-separated integers: M and N 
>
> Lines 2..M+1: Line i+1 describes row i of the pasture with N space-separated integers indicating whether a square is fertile (1 for fertile, 0 for infertile)



## **Output**

> Line 1: One integer: the number of ways that FJ can choose the squares modulo 100,000,000.



## **Sample Input**

    2 3
    1 1 1
    0 1 0



## **Sample Output**

    9



## **题意**

在一个 0,1 组成的数字矩阵中选取 0,1,2..k 个 1 ，且所有的 1 都不相邻的方案总数。



## **思路**

`dp[i][j][k]` 代表第 `i` 行的状态为 `j` （二进制形式），且总共挑选了 `k` 个 `1` 满足题意的前 `i` 行选择方案数

我们确定一个 `judge` 方法，其目的是判断一个整数 `x` 的二进制中是否含有相邻的 `1` ，若有，返回结果 `-1` ，否则返回该二进制数中 `1` 的个数

于是，对于第一行，所有的合法状态的 `dp` 取值都为 `1`

对于第 `i` 行的某个状态 `j` ，显然它可以由上一行与当前行所有不相交的方案转移而来

已知第 `i-1` 行的最大可行方案为 `~j&((1<<m)-1)` ，则我们只需要枚举其二进制的子集即可



**状态转移方程：**

`dp[i][j][num+k]+=dp[i-1][s][k]`

其中， `num` 为当前行合法状态中 `1` 的个数， `k` 为前 `i-1` 行挑选的数目， `s` 为第 `i-1` 行一个合法的不相交子集。



## **AC 代码**

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 15;
const int maxm = 5000+10;
const int maxk = 75;
const int mod = 100000000;
typedef unsigned __int64 LL;

LL dp[maxn][maxm][maxk];    //第 i 行状态为 j 且总共挑选 k 个数满足题意的前 i 行选择方案
int a[maxn],n,m;

int judge(int x)
{
    int ans=0;
    for(int i=1; i<=x; i<<=1)
        if(i&x)
        {
            ans++;
            if(i>>1&x)return -1;
        }
    return ans;
}

void solve()
{
    for(int i=1; i<=n; i++)     //枚举行
        for(int j=0; j<1<<m; j++)   //枚举第 i 行状态
            if((j&a[i])==j)     //j 是 a[i] 的子集
            {
                unsigned int fa=~j&((1<<m)-1);  //第 i-1 行最大可行方案
                int num = judge(j);             //判断 j 是否含有两个相邻 1
                if(num==-1)continue;
                if(i==1)dp[i][j][num]=1;
                else
                {
                    for(unsigned int s=0; s<1u<<m; s++) //枚举第 i-1 行状态
                        if((s&fa)==s)           //属于 i-1 行最大可行方案的子集
                            for(int k=0; k<maxk; k++)   //枚举挑选数目
                                dp[i][j][num+k]=(dp[i][j][num+k]+dp[i-1][s][k])%mod;
                }
            }
}

int main()
{
    ios::sync_with_stdio(false);
    while(cin>>n>>m)
    {
        memset(dp,0,sizeof(dp));
        for(int i=1; i<=n; i++)
        {
            int x=0;
            for(int j=0,temp; j<m; j++)
            {
                cin>>temp;
                x=(x<<1)+temp;  //每行保存为一个二进制数
            }
            a[i]=x;
        }
        solve();
        LL ans=0;
        for(int i=0; i<1<<m; i++)   //第 n 行所有状态之和
            for(int j=1; j<maxk; j++)
                ans=(ans+dp[n][i][j])%mod;
        cout<<(ans+1)%mod<<endl;    //+1 是挑选 0 个的方案
    }
    return 0;
}
```

