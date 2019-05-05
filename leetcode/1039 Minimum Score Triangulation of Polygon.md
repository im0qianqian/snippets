# 1039 Minimum Score Triangulation of Polygon

## **Description**

> 给定 `N`，想象一个凸 `N` 边多边形，其顶点按顺时针顺序依次标记为 `A[0], A[i], ..., A[N-1]`。
>
> 假设您将多边形剖分为 `N-2` 个三角形。对于每个三角形，该三角形的值是顶点标记的**乘积**，三角剖分的分数是进行三角剖分后所有 `N-2` 个三角形的值之和。
>
> 返回多边形进行三角剖分后可以得到的最低分。




## **Input**

    [3,7,4,5]



## **Output**

    144



## **思路**

设 $dp[i][j]$ 代表 $A$ 中从第 $i$ 到第 $j$ 个点围成凸多边形所得的最优解。

枚举在 $i,j$ 之间的一点 $k$，考虑是否将该凸多边形剖分出 `i, j, k` 三点所围成的三角形。

则有：$dp[i][j] = \min(dp[i][j], dp[i][k] + dp[k][j] + A[i] \times A[j] \times A[k])$



## **AC 代码**

```cpp
class Solution {
public:
    int minScoreTriangulation(vector<int> &A) {
        int n = A.size();
        int dp[n + 1][n + 1];
        for (int d = 2; d < n; d++) {
            for (int i = 0; i + d < n; i++) {
                int j = i + d;
                dp[i][j] = INT_MAX;
                for (int k = i + 1; k < j; k++) {
                    cout << i << " " << j << " " << k << endl;
                    dp[i][j] =
                        min(dp[i][j], dp[i][k] + dp[k][j] + A[i] * A[j] * A[k]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
```
