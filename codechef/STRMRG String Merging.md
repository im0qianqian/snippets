# STRMRG String Merging

## **Description**

> All submissions for this problem are available.
>
> Read problems statements in Mandarin chinese, Russian and Vietnamese as well.
>
> For a string S, let's define a function F(S) as the minimum number of blocks consisting of consecutive identical characters in S. In other words, F(S) is equal to 1 plus the number of valid indices i such that Si ≠ Si+1.
>
> You are given two strings A and B with lengths N and M respectively. You should merge these two strings into one string C with length N+M. Specifically, each character of C should come either from A or B; all characters from A should be in the same relative order in C as in A and all characters from B should be in the same relative order in C as in B.
>
> Compute the minimum possible value of F(C).



## **Input**

> The first line of the input contains a single integer T denoting the number of test cases. The description of T test cases follows.
>
> The first line of each test case contains two space-separated integers N and M.
>
> The second line contains a single string A with length N.
>
> The third line contains a single string B with length M.



## **Output**

> For each test case, print a single line containing one integer — the minimum possible value of F(C).



## **Constraints**

> 1 ≤ T ≤ 100
>
> 1 ≤ N, M ≤ 5,000
>
> 1 ≤ sum of N in all test cases ≤ 5,000
>
> 1 ≤ sum of M in all test cases ≤ 5,000
>
> strings A, B consist only of lowercase English letters



## **Example Input**

    1
    4 4
    abab
    baba



## **Example Output**

    5



## **题意**

> 对于字符串 S，定义函数 F(S) 为：最少可以将 S 划分为几个连续的子串，使得每个子串仅包含相同的字符。换句话说，F(S) 等于 1 加上满足 Si ≠ Si+1 的合法下标 i 的数量。
>
> 给定两个字符串 A 和 B，长度分别为 N 和 M。你需要将这两个字符串合并成一个长度为 N + M 的字符串 C。C 的每个字符要么来源于 A，要么来源于 B，且来源于 A 的字符的相对顺序应当与在 A 中一致，来源于 B 的字符亦然。
>
> 请求出 F(C) 最小可能的值。



## **思路**

unique 以后直接做 LCS 即可。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e4+10;
const int mod = 1e9+7;
typedef long long LL;
 
int n,m;
char s1[maxn],s2[maxn];
int dp[maxn][maxn];
 
int unique_str(char *s,int len)
{
    int tot = 0;
    for(int i=1; i<len; i++)
        if(s[i]!=s[tot])
            s[++tot] = s[i];
    return tot+1;
}
 
int main()
{
    IO;
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        cin>>(s1+1);
        cin>>(s2+1);
        n = unique_str(s1+1,n);
        m = unique_str(s2+1,m);
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=m; j++)
            {
                if(s1[i]==s2[j])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        cout<<n+m-dp[n][m]<<endl;
    }
    return 0;
}
```

