## A. A Twisty Movement

## **Description**

> A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.
>
> A performer holding the rod low is represented by a 1, while one holding it high is represented by a 2. Thus, the line of performers can be represented by a sequence $a_1, a_2, ..., a_n$ .
>
> Little Tommy is among them. He would like to choose an interval $[l, r]~(1 ≤ l ≤ r ≤ n)$, then reverse $a_l, a_{l + 1}, ..., a_r$ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.
>
> A non-decreasing subsequence is a sequence of indices $p_1, p_2, ..., p_k$ , such that $p_1 < p_2 < ... < p_k$ and $a_{p_1} ≤ a_{p_2} ≤ ... ≤ a_{p_k}$ . The length of the subsequence is $k$ .



## **Input**

> The first line contains an integer $n~(1 ≤ n ≤ 2000)$ , denoting the length of the original sequence.
>
> The second line contains $n$ space-separated integers, describing the original sequence $a1, a2, ..., an~(1 ≤ ai ≤ 2, i = 1, 2, ..., n)$ .



## **Output**

> Print a single integer, which means the maximum possible length of the longest non-decreasing subsequence of the new sequence.



## **Examples input**

    4
    1 2 1 2



## **Examples output**

    4



## **题意**

在一个只包含 $1,2$ 的序列中，翻转其中任意一个区间，求此时最大的 LIS 。



## **思路**

正着倒着预处理出每一段的 LIS，分别记为 $L[i][j],R[i][j]$

然后开始枚举，翻转一个区间相当于减去这段区间的贡献，然后加上其翻转以后的

此时 LIS 为 $L[0][n-1] - L[i][j] + R[i][j]$



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 2e3+10;

int n;
int a[maxn];
int L[maxn][maxn],R[maxn][maxn];

int main()
{
    IO;
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i];
    for(int i=0; i<n; i++)
    {
        int dp1 = 0, dp2 = 0;
        for(int j=i; j<n; j++)
        {
            if(a[j]==1)
                ++dp1;
            else
                dp2 = max(dp1,dp2) + 1;
            L[i][j] = max(dp1,dp2);
        }
        dp1 = dp2 = 0;
        for(int j=i; j<n; j++)
        {
            if(a[j]==2)
                ++dp1;
            else
                dp2 = max(dp1,dp2) + 1;
            R[i][j] = max(dp1,dp2);
        }
    }
    int ans = 0;
    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++)
            ans = max(ans,L[0][n-1] - L[i][j] + R[i][j]);
    cout<<ans<<endl;
    return 0;
}
```

