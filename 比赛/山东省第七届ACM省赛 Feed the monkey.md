# Feed the monkey

## **Problem Description**

> Alice has a monkey, she must feed fruit to the monkey every day.She has three kinds of fruits, bananas, peaches and apples. Every day, she chooses one in three, and pick one of this to feed the monkey. 
>
> But the monkey is picky, it doesn’t want bananas for more than D1 consecutive days, peaches for more than D2 consecutive days, or apples for more than D3 consecutive days. Now Alice has N1 bananas, N2 peaches and N3 apples, please help her calculate the number of schemes to feed the monkey.



## **Input**

> Multiple test cases. The first line contains an integer T (T<=20), indicating the number of test case.
>
> Each test case is a line containing 6 integers N1, N2, N3, D1, D2, D3 (N1, N2, N3, D1, D2, D3<=50).



## **Output**

> One line per case. The number of schemes to feed the monkey during (N1+N2+N3) days.
>
> The answer is too large so you should mod 1000000007.



## **Example Input**

    1
    2 1 1 1 1 1



## **Example Output**

    6



## **题意**

给出三种水果以及每种水果不能连续的数量，求总共有多少种组合的方式。



## **思路**

`dp[a][b][c][k]` 代表当前剩余第一种水果 `a` 个，剩余第二种水果 `b` 个，剩余第三种水果 `c` 个，并且以 `k` 结尾所有的组合数。

枚举所有的 `a,b,c` ， `dp[s][b][c][0]` 可以由 `dp[a][b][c][1]` 与 `dp[a][b][c][2]` 转移而来，其中 `s` 为保证第一种水果最多连续不超过 `d[0]` 的水果数目。

因此 `s` 取值范围为： `[max(0,a-d[0]),a)` 。

第二种水果和第三种水果的转移也类似，输出 `mod 1e9+7` 之后的结果。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
typedef long long LL;
LL dp[51][51][51][3];
int n[3],d[3];

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        memset(dp,0,sizeof(dp));
        for(int i=0; i<3; i++)
            cin>>n[i];
        for(int i=0; i<3; i++)
            cin>>d[i];
        for(int a=n[0]; a>=0; a--)
        {
            for(int b=n[1]; b>=0; b--)
            {
                for(int c=n[2]; c>=0; c--)
                {
                    for(int s=max(0,a-d[0]); s<a; s++)
                    {
                        if(a==n[0]&&b==n[1]&&c==n[2])
                            dp[s][b][c][0]=(dp[s][b][c][0]+1)%mod;
                        else
                            dp[s][b][c][0]=(dp[s][b][c][0]+dp[a][b][c][1]+dp[a][b][c][2])%mod;
                    }
                    for(int s=max(0,b-d[1]); s<b; s++)
                    {
                        if(a==n[0]&&b==n[1]&&c==n[2])
                            dp[a][s][c][1]=(dp[a][s][c][1]+1)%mod;
                        else
                            dp[a][s][c][1]=(dp[a][s][c][1]+dp[a][b][c][0]+dp[a][b][c][2])%mod;
                    }
                    for(int s=max(0,c-d[2]); s<c; s++)
                    {
                        if(a==n[0]&&b==n[1]&&c==n[2])
                            dp[a][b][s][2]=(dp[a][b][s][2]+1)%mod;
                        else
                            dp[a][b][s][2]=(dp[a][b][s][2]+dp[a][b][c][0]+dp[a][b][c][1])%mod;
                    }
                }
            }
        }
        cout<<((dp[0][0][0][0]+dp[0][0][0][1])%mod+dp[0][0][0][2])%mod<<endl;
    }
    return 0;
}
```

