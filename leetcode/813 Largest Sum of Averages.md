# 813 Largest Sum of Averages

## **Description**

> We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. What is the largest score we can achieve?
>
> Note that our partition must use every number in A, and that scores are not necessarily integers.



## **Input**

    A = [9,1,2,3,9]
    K = 3



## **Output**

    20



## **题意**

长度为 $n$ 的数组最多可分为 $k$ 段，求分完以后每一段平均值和的最大值。



## **思路**

因为数据很水的原因，就用最普通的做法咯~ ( $1<=n<=100$ )

设 $dp[i][j][k]$ 为区间 $[i,j]$ 分为 $k$ 段所能得到的结果，则显然：

$$
dp[i][j][k]=\max(dp[i][j][k],dp[i][s][k-1] + \frac{Sum(s+1,j)}{j-s})
$$

其中 $s$ 为区间 $[i,j]$ 之间的一个分割点，最终的结果：$dp[0][len-1][K]$



## **AC 代码**

```cpp
const int maxn = 1e2+10;
double dp[maxn][maxn][maxn];
int sum[maxn];
class Solution
{
public:
    int getSum(int x,int y)
    {
        return sum[y] - (x==0?0 : sum[x-1]);
    }
    double largestSumOfAverages(vector<int>& A, int K)
    {
        memset(sum,0,sizeof(sum));
        memset(dp,0,sizeof dp);
        int len = A.size();
        sum[0] = A[0];
        for(int i=1; i<len; i++)
            sum[i] = sum[i-1] + A[i];
        for(int i=0; i<len; i++)
            for(int j=i; j<len; j++)
            {
                dp[i][j][j-i+1] = getSum(i,j) * 1.0;
                dp[i][j][1] = getSum(i,j) * 1.0 / (j-i+1);
            }
        for(int k=2; k<=K; k++)
            for(int i=0; i<len; i++)
                for(int j=i + k - 1; j<len; j++)
                    for(int s = i; s < j; s++)
                        dp[i][j][k] = max(dp[i][j][k],dp[i][s][k-1]+getSum(s+1,j) * 1.0 / (j-s));
        return dp[0][len-1][K];
    }
};
```

