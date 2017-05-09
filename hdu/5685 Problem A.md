# Problem A

## **Problem Description**

> 度熊手上有一本字典存储了大量的单词，有一次，他把所有单词组成了一个很长很长的字符串。现在麻烦来了，他忘记了原来的字符串都是什么，神奇的是他竟然记得原来那些字符串的哈希值。一个字符串的哈希值，由以下公式计算得到：
>
> $H(s)=∏_{i=1}^{i≤len(s)}(S_i−28) (mod~9973)$
>
> $S_i$ 代表 `S[i]` 字符的 `ASCII` 码。
>
> 请帮助度熊计算大字符串中任意一段的哈希值是多少。



## **Input**

> 多组测试数据，每组测试数据第一行是一个正整数N，代表询问的次数，第二行一个字符串，代表题目中的大字符串，接下来N行，每行包含两个正整数a和b，代表询问的起始位置以及终止位置。
>
> $1≤N≤1000$
>
> $1≤len(string)≤100000$
>
> $1≤a,b≤len(string)$

 

## **Output**

> 对于每一个询问，输出一个整数值，代表大字符串从 a 位到 b 位的子串的哈希值。



## **Sample Input**

    2
    ACMlove2015
    1 11
    8 10
    1
    testMessage
    1 1



## **Sample Output**

    6891
    9240
    88



## **思路**

这是一道可以用线段树也可以用逆元做的题目，我们可以先找到逆元的递推模版打表，然后嘛！区间哈希值打表之后就可以随便输出咯！

伤心的是比赛的时候后台一定改过数据，不然当时用高速幂就不会超时啦~



## **AC 代码**

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef __int64 ll;
const ll maxn=100005;
const ll mod=9973;
ll sum[maxn],inv[maxn],re[maxn];
char s[maxn];
int main()
{
    inv[1]=1;
    for(int i=2;i<maxn;++i)
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    int n;
    while(~scanf("%d",&n))
    {
        scanf("%s",s+1);
        sum[0]=re[0]=1;
        for(int i=1;s[i]!=0;++i)
        {
            sum[i]=(sum[i-1]*(s[i]-28))%mod;
            re[i]=inv[sum[i]];
        }
        for(int i=0;i<n;++i)
        {
            ll a,b;
            scanf("%I64d%I64d",&a,&b);
            ll tp=re[a-1];
            printf("%I64d\n",(sum[b]*tp)%mod);
        }
    }
    return 0;
}
```

