# Palindrome Function

## **Description**

> As we all know,a palindrome number is the number which reads the same backward as forward,such as 666 or 747.Some numbers are not the palindrome numbers in decimal form,but in other base,they may become the palindrome number.Like 288,it’s not a palindrome number under 10-base.But if we convert it to 17-base number,it’s GG,which becomes a palindrome number.So we define an interesting function f(n,k) as follow:
>
> f(n,k)=k if n is a palindrome number under k-base.
>
> Otherwise f(n,k)=1.
>
> Now given you 4 integers L,R,l,r,you need to caluclate the mathematics expression $\sum_{i=L}^{R}\sum_{j=l}^{r}f(i,j)$ .
>
> When representing the k-base(k>10) number,we need to use A to represent 10,B to represent 11,C to repesent 12 and so on.The biggest number is Z(35),so we only discuss about the situation at most 36-base number.



## **Input**

> The first line consists of an integer T,which denotes the number of test cases.
>
> In the following T lines,each line consists of 4 integers L,R,l,r.
>
> $(1≤T≤10^5,1≤L≤R≤10^9,2≤l≤r≤36)$



## **Output**

> For each test case, output the answer in the form of “Case #i: ans” in a seperate line.



## **Sample Input**

    3
    1 1 2 36
    1 982180 10 10
    496690841 524639270 5 20



## **Sample Output**

    Case #1: 665
    Case #2: 1000000
    Case #3: 447525746



## **题意**

求 L 到 R 之间所有数在 l 到 r 进制中是否是回文数的贡献和。



## **思路**

**回文数的个数其实是有规律的，假设在 $k$ 进制下：**

$1$ 位回文数： $k^1-k^0$ 个

$2$ 位回文数： $k^1-k^0$ 个

$3$ 位回文数： $k^2-k^1$ 个

$4$ 位回文数： $k^2-k^1$ 个

$5$ 位回文数： $k^3-k^2$ 个

...

于是我们可以考虑枚举进制 $[l,r]$ ，计算 $[1,R]$ 与 $[1,L-1]$ 之间有多少个回文数。

对于每一个进制 $k$ ，我们设 $tot$ 为数 $x$ 在 $k$ 进制下的位数。

首先可以根据上面的规律求得 $tot-1$ 位以下的 $k$ 进制回文数有多少个。

假设 $x=12345$ ，显然，对于长度为 $tot$ 位的回文数，受到约束的范围是在回文对称轴的左边，即 $123$ ，也就是说它的大小约束了当前长度下回文数的个数，其结果与之前的计算方法类似，即 $123-100$ ，代表对称轴左边可以是 $[100,122]$ 总共 $23$ 种情况，那什么时候在左边可以出现 $123$ 呢？

可以看出，如果 $12321<12345$ 成立即可。

综上，分别求得区间 $[1,R]$ 的回文个数与 $[1,L-1]$ 的回文个数，然后根据函数 $f$ 计算做差即可。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int64 LL;
const int maxn = 40;
int num[maxn];

LL solve(LL x,int k)
{
    if(x==0)return 0;
    LL i=x,tot=0;
    while(i)
    {
        num[tot++]=i%k;
        i/=k;
    }
    LL p=0,sum=1,cnt=0,base=k,left;
    for(int i=1; i<tot; i++)
    {
        cnt+=base-sum;
        if(i%2==0)
        {
            sum=base;
            base*=k;
        }
    }
    for(int i=tot-1; i>=tot/2; i--)
        p = p * k + num[i];
    left = p;
    for(int i=tot/2+(tot&1); i<tot; i++)
        p = p * k + num[i];
    cnt+=left-sum + (p<=x);
    return cnt*(k-1)+x;
}

int main()
{
    int T;
    cin>>T;
    for(int ti=1; ti<=T; ti++)
    {
        LL L,R,ans=0;
        int l,r;
        cin>>L>>R>>l>>r;
        for(int i=l; i<=r; i++)
            ans+=solve(R,i)-solve(L-1,i);
        cout<<"Case #"<<ti<<": "<<ans<<endl;
    }
    return 0;
}
```

