# Squarefree number

## **Description**

> In mathematics, a squarefree number is one which is divisible by no perfect squares, except 1. For example, 10 is square-free but 18 is not, as it is divisible by 9 = 3^2. Now you need to determine whether an integer is squarefree or not.



## **Input**

> The first line contains an integer T indicating the number of test cases.
>
> For each test case, there is a single line contains an integer N.
>
> Technical Specification
>
> 1. 1 <= T <= 20
> 2. 2 <= N <= 10^18



## **Output**

> For each test case, output the case number first. Then output "Yes" if N is squarefree, "No" otherwise.



## **Sample Input**

    2
    30
    75



## **Sample Output**

    Case 1: Yes
    Case 2: No



## **题意**

判断一个数是否是“无平方数”（是这么翻译么？）



## **思路**

显然 $10^{18}$ 的数据范围不允许我们逐一尝试。

考虑对 $n$ 进行质因子分解，我们知道，如果某一个质数的次数大于 2 ，即说明它不是一个无平方数。

筛选完 $10^6$ 以下的所有质因子以后，如果 $n>10^6$ ，则说明它最多含有两个 $10^6$ 以上的质因子，根号然后平方判断一下这两个质因子是否一样即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 1e6+10;

bool visit[maxn];
int prime[maxn];
int tot;
LL n;
void getprime()
{
    tot=0;
    memset(visit,0,sizeof(visit));
    for(int i=2; i<maxn; i++)
    {
        if(!visit[i])
        {
            prime[tot++]=i;
            for(int j=i+i; j<maxn; j+=i)
                visit[j]=1;
        }
    }
}

bool solve()
{
    for(int i=0; i<tot; i++)
    {
        if(n%prime[i]==0)
        {
            n/=prime[i];
            if(n%prime[i]==0)
                return false;
        }
    }
    if(n>=1e6)
    {
        LL tmp = sqrt(n) + 0.5;
        if(tmp*tmp==n)
            return false;
    }
    return true;
}

int main()
{
    getprime();
    int T;
    cin>>T;
    for(int ti=1; ti<=T; ti++)
    {
        cin>>n;
        cout<<"Case "<<ti<<": ";
        cout<<(solve()?"Yes":"No")<<endl;
    }
    return 0;
}
```

