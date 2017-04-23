# Little Red Riding Hood

## **Description**

> Once upon a time, there was a little girl. Her name was Little Red Riding Hood. One day, her grandma was ill. Little Red Riding Hood went to visit her. On the way, she met a big wolf. “That's a good idea.”，the big wolf thought. And he said to the Little Red Riding Hood, “Little Red Riding Hood, the flowers are so beautiful. Why not pick some to your grandma?” “Why didn't I think of that? Thank you.” Little Red Riding Hood said. Then Little Red Riding Hood went to the grove to pick flowers. There were n flowers, each flower had a beauty degree a[i]. These flowers arrayed one by one in a row. The magic was that after Little Red Riding Hood pick a flower, the flowers which were exactly or less than d distances to it are quickly wither and fall, in other words, the beauty degrees of those flowers changed to zero. Little Red Riding Hood was very smart, and soon she took the most beautiful flowers to her grandma’s house, although she didn’t know the big wolf was waiting for her.
>
> Do you know the sum of beauty degrees of those flowers which Little Red Riding Hood pick?



## **Input**

> The first line input a positive integer T (1≤T≤100), indicates the number of test cases.
>
> Next, each test case occupies two lines. The first line of them input two positive integer n and k (2 ≤ n ≤ 105,1 ≤ k < n), the second line of them input n positive integers a (1 ≤ a ≤ 105).



## **Output**

> Each group of outputs occupies one line and there are one number indicates the sum of the largest beauty degrees of flowers Little Red Riding Hood can pick.



## **Sample Input**

    1 
    3 1 
    2 1 3



## **Sample Output**

    5



## **题意**

小红帽去采花，每朵花都有它的 `degree` ，每采一朵其周边范围 `k` 以内的其他花都会枯萎，求最后能得到的最大 `degree` 和。



## **思路**

`dp[i][0]` 代表以 `i` 结尾但是不选择第 `i` 朵花所能得到的最大价值。

`dp[i][1]` 代表以 `i` 结尾并且选择第 `i` 朵花所能得到的最大价值。

**则有状态转移方程：**

`dp[i][0]=max(dp[i-1][0],dp[i-1][1])`

`dp[i][1]=max(dp[r][0],dp[r][1])+a[i]` 其中 `r` 为 `i` 枯萎半径以外的前一个状态。



## **AC 代码**

```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 1000007

typedef unsigned long long LL;
LL dp[110000][2];
int a[110000];
int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        int n,k;
        cin>>n>>k;
        for(int i=0; i<n; i++)
            cin>>a[i];
        memset(dp,0,sizeof(dp));
        dp[0][1]=a[0];
        dp[0][0]=0;
        for(int i=1; i<n; i++)
        {
            dp[i][0]=max(dp[i-1][1],dp[i-1][0]);
            int r=i-k-1;
            if(r<0)dp[i][1]=a[i];
            else dp[i][1]=max(dp[r][0],dp[r][1])+a[i];
        }
        cout<<max(dp[n-1][0],dp[n-1][1])<<endl;
    }
    return 0;
}
```

