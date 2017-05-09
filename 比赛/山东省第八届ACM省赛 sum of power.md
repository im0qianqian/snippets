# sum of power

## **Problem Description**

> Calculate $\sum_{i=1}^ni^m~mod~(1000000000+7)$ for given n，m.



## **Input**

> Input contains two integers n,m(1≤n≤1000,0≤m≤10).



## **Output**

> Output the answer in a single line.



## **Example Input**

    10 0



## **Example Output**

    10



## **思路**

绝不应该错的一道题，比赛时第一道敲的题目，居然 `1WA` 了，原因时题面上写的 `mod=100000000+7` ，当时已经写出 `1e9+7` ，然后检查的时候发现差点交错，改成 `1e8+7` 之后就错了。

还好之后这道题重判了，减少了20分钟的罚时。

**会不会 100000000+7=1e9+7 呢？** 



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define eps (1e-8)
const int mod = 1e9+7;
typedef long long LL;

LL mult(LL a,LL n)
{
    LL ans=1;
    while(n)
    {
        if(n&1)ans=(ans*a)%mod;
        a=(a*a)%mod;
        n>>=1;
    }
    return ans;
}

int main()
{
    LL n,m;
    while(cin>>n>>m)
    {
        LL ans=0;
        for(LL i=1; i<=n; i++)
            ans=(ans+mult(i,m))%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```

