# A Simple Math Problem

## **Problem Description**

> Given two positive integers a and b,find suitable X and Y to meet the conditions:
>
> X+Y=a
>
> Least Common Multiple (X, Y) =b



## **Input**

> Input includes multiple sets of test data.Each test data occupies one line,including two positive integers a(1≤a≤2×10^4),b(1≤b≤10^9),and their meanings are shown in the description.Contains most of the 12W test cases.



## **Output**

> For each set of input data,output a line of two integers,representing X, Y.If you cannot find such X and Y,output one line of "No Solution"(without quotation).



## **Sample Input**

    6 8
    798 10780



## **Sample Output**

    No Solution
    308 490



## **题意**

给出 $X+Y=a$ 、 $lcm(X,Y)=b$ ，其中 `a、b` 是已知的，求 `X、Y` 。



## **思路**

无意间自己想出的一个定理（虽然不知道数论里面有没有它）， $\gcd(a,b)=\gcd(X,Y)$

关于证明在比赛的时候还没有，只是感觉它是对的，可能是数学方面的感性吧~



**证明过程：**

首先有 $\gcd(a,b)=\gcd(X+Y,lcm(X,Y))$

我们令 $k=\gcd(X,Y)$ ，显然 $k|X$ 、 $k|Y$ ，于是有 $X+Y=k×(\frac{X}{k}+\frac{Y}{k})$ ，并且 $\frac{X}{k}$、$\frac{Y}{k}$ 互质。

又因为 $lcm(X,Y)=\frac{X×Y}{k}$ ，它也就等价于 $k×(\frac{X}{k}×\frac{Y}{k})$ ，因为互质的关系，显然， $\gcd(X+Y,lcm(X,Y))=k=\gcd(X,Y)$

于是这样便证明成功啦~ （只是还不知道它在什么情况下才会成立）

---

有了 $\gcd(X,Y)$ ，我们便可以知道 $XY=lcm(X,Y)×\gcd(X,Y)$ 

然后因为 $(X+Y)^2-4XY=(X-Y)^2$ ，便可以计算出 $X-Y$ 咯~

与 $X+Y=a$ 联立方程组分别解出 `X、Y` 。

**解不存在的情况：** `X、Y` 计算其最小公倍数如果不等于 `b` ，则解不存在。



## **AC 代码**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include<iostream>
using namespace std;
#define MAXX 110000
typedef __int64 LL;

LL gcd(LL a,LL b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}

void solve(int a,int b)
{
    LL gc=gcd(a,b);
    LL xy=b*gc;
    LL x_y=sqrt(a*a-4.0*xy);
    LL x=(a+x_y)/2;
    LL y=a-x;
    if(x/gcd(x,y)*y!=b)
    {
        printf("No Solution\n");
        return;
    }
    if(x>y)swap(x,y);
    printf("%I64d %I64d\n",x,y);
}

int main()
{
    LL a,b;
    while(~scanf("%I64d%I64d",&a,&b))
        solve(a,b);
    return 0;
}
```

