# Chess

## **Description**

> 車是中国象棋中的一种棋子，它能攻击同一行或同一列中没有其他棋子阻隔的棋子。一天，小度在棋盘上摆起了许多車……他想知道，在一共N×M个点的矩形棋盘中摆最多个数的車使其互不攻击的方案数。他经过思考，得出了答案。但他仍不满足，想增加一个条件：对于任何一个車A，如果有其他一个車B在它的上方（車B行号小于車A），那么車A必须在車B的右边（車A列号大于車B）。
>
> 现在要问问你，满足要求的方案数是多少。



## **Input**

> 第一行一个正整数T，表示数据组数。
>
> 对于每组数据：一行，两个正整数N和M（N<=1000，M<=1000）。



## **Output**

> 对于每组数据输出一行，代表方案数模1000000007（1e9+7）。



## **Sample Input**

    1
    1 1



## **Sample Output**

    1



## **思路**

简单组合数，逆元打表计算输出一下就好。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod = 1e9+7;
const int maxn =1005;
LL mul[maxn];
LL inv[maxn];

void init()
{
    mul[0]=1;
    for(int i=1; i<maxn; i++)
        mul[i]=(mul[i-1]*i)%mod;
    inv[0]=inv[1]=1;
    for(int i=2; i<maxn; i++)
        inv[i]=(LL)(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1; i<maxn; i++)
        inv[i]=(inv[i-1]*inv[i])%mod;
}

LL C(int n,int m)
{
    return mul[n]*inv[m]%mod*inv[n-m]%mod;
}

int main()
{
    init();
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        int n,m;
        cin>>n>>m;
        if(n<m)
            swap(n,m);
        cout<<C(n,m)<<endl;
    }
    return 0;
}
```

