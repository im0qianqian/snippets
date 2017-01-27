# C Looooops

## **Description**

> A Compiler Mystery: We are given a C-language style for loop of type 
>
>    for (variable = A; variable != B; variable += C)
>    	statement;
>
> I.e., a loop which starts by setting variable to value A and while variable is not equal to B, repeats statement followed by increasing the variable by C. We want to know how many times does the statement get executed for particular values of A, B and C, assuming that all arithmetics is calculated in a k-bit unsigned integer type (with values 0 <= x < 2^k) modulo 2^k. 



## **Input**

> The input consists of several instances. Each instance is described by a single line with four integers A, B, C, k separated by a single space. The integer k (1 <= k <= 32) is the number of bits of the control variable of the loop and A, B, C (0 <= A, B, C < 2^k) are the parameters of the loop. 
>
> The input is finished by a line containing four zeros. 



## **Output**

> The output consists of several lines corresponding to the instances on the input. The i-th line contains either the number of executions of the statement in the i-th instance (a single integer number) or the word FOREVER if the loop does not terminate. 



## **Sample Input**

    3 3 2 16
    3 7 2 16
    7 3 2 16
    3 4 2 16
    0 0 0 0



## **Sample Output**

    0
    2
    32766
    FOREVER



## **题意**

找一个最小的x，使得 $(A+C*x)\%2^k=B$



## **思路**

对于上面的式子，我们可以转化为 $(C*x)\%2^k=B-A$

于是，很典型的一个求解模线性方程的问题，因为要求最小的一组解，所以我们要保证计算的结果是正数。



对于 $ax≡b(mod~n)$ ， $d=gcd(a,n)$ 。

**推论1：**当且仅当 $d|b$ 时，方程对于未知量 $x$ 有解。

**推论2：**该方程或者对模 $n$ 有 $d$ 个不同的解，或者无解。

**定理1：**假设对某些整数 $x'$ 和 $y'$ ，有 $d=ax'+ny'$ ，如果 $d|b$ ，则该方程有一个解的值为 $x_0$ ，这里 $x_0=x'(b/d)~mod~n$



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
typedef __int64 LL;

int extgcd(LL a, LL b, LL &x, LL &y)
{
    LL d = a;
    if(b != 0)
    {
        d  = extgcd(b, a % b, y, x);
        y -= (a/b) * x;
    }
    else
    {
        x = 1, y = 0;
    }
    return d;
}

int main()
{
    LL a,b,c,k;
    while(~scanf("%I64d%I64d%I64d%I64d",&a,&b,&c,&k)&&(a||b||c||k))
    {
        LL x,y,mod=(1LL<<k),d=extgcd(c,mod,x,y);
        if((b-a)%d!=0)
            printf("FOREVER\n");
        else
        {
            x=(x*((b-a)/d))%mod;
            x=(x%(mod/d)+mod/d)%(mod/d);
            printf("%I64d\n",x);
        }
    }
}
```

