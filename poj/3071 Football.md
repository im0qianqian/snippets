# Football

## **Description**

> Consider a single-elimination football tournament involving 2n teams, denoted 1, 2, …, 2n. In each round of the tournament, all teams still in the tournament are placed in a list in order of increasing index. Then, the first team in the list plays the second team, the third team plays the fourth team, etc. The winners of these matches advance to the next round, and the losers are eliminated. After n rounds, only one team remains undefeated; this team is declared the winner.
>
> Given a matrix P = [pij] such that pij is the probability that team i will beat team j in a match determine which team is most likely to win the tournament.



## **Input**

> The input test file will contain multiple test cases. Each test case will begin with a single line containing n (1 ≤ n ≤ 7). The next 2n lines each contain 2n values; here, the jth value on the ith line represents pij. The matrix P will satisfy the constraints that pij = 1.0 − pji for all i ≠ j, and pii = 0.0 for all i. The end-of-file is denoted by a single line containing the number −1. Note that each of the matrix entries in this problem is given as a floating-point value. To avoid precision problems, make sure that you use either the double data type instead of float.



## **Output**

> The output file should contain a single line for each test case indicating the number of the team most likely to win. To prevent floating-point precision issues, it is guaranteed that the difference in win probability for the top two teams will be at least 0.01.



## **Sample Input**

    2
    0.0 0.1 0.2 0.3
    0.9 0.0 0.4 0.5
    0.8 0.6 0.0 0.6
    0.7 0.5 0.4 0.0
    -1



## **Sample Output**

    2



## **题意**

有 $2^n$ 个队伍，相邻的两两打淘汰赛，求最后哪个队夺冠的概率最大。



## **思路**

**概率DP**

`dp[i][j]` 代表在第 `i` 轮中，队伍 `j` 赢的概率。

则 `dp[i][j]=sum(dp[i-1][j]*dp[i-1][k]*p[j][k])` 

表示在第 `i` 轮中 `j` 的获胜概率等于 `i-1` 轮中 `j` 取得了胜利并且打赢了 `k` （前提 `k` 也在第 `i-1` 轮中获胜）。



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

double a[205][205];
double dp[10][205];
int n,N;

inline bool jud(int k,int i,int j)  //判断两队是否相邻
{
    i>>=k-1;
    j>>=k-1;
    return (i^1)==j;
}

void solve()
{
    memset(dp,0,sizeof(dp));
    for(int i=0; i<N; i++)      //第0轮初始化概率都为1
        dp[0][i]=1;
    for(int k=1; k<=n; k++)
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                if(jud(k,i,j))
                    dp[k][i]+=dp[k-1][i]*dp[k-1][j]*a[i][j];
    int ans=0;
    for(int i=1; i<N; i++)
        if(dp[n][i]>dp[n][ans])
            ans=i;
    printf("%d\n",ans+1);
}

int main()
{
    while(~scanf("%d",&n)&&n!=-1)
    {
        N=1<<n;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                scanf("%lf",&a[i][j]);
        solve();
    }
    return 0;
}
```

