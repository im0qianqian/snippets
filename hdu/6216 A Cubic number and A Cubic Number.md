# A Cubic number and A Cubic Number

## **Description**

> A cubic number is the result of using a whole number in a multiplication three times. For example, 3×3×3=27 so 27 is a cubic number. The first few cubic numbers are 1,8,27,64 and 125. Given an prime number p. Check that if p is a difference of two cubic numbers.



## **Input**

> The first of input contains an integer T (1≤T≤100) which is the total number of test cases.
>
> For each test case, a line contains a prime number p (2≤p≤10^12).



## **Output**

> For each test case, output 'YES' if given p is a difference of two cubic numbers, or 'NO' if not.



## **Sample Input**

    10
    2
    3
    5
    7
    11
    13
    17
    19
    23
    29



## **Sample Output**

    NO
    NO
    NO
    YES
    NO
    NO
    NO
    YES
    NO
    NO



## **题意**

判断一个质数是否可以表示为两个正整数立方的差。



## **思路**

设这两个正整数分别为 $a,b$ ，其中 $a>b$ ，则问题可以表示为 $a^3-b^3=p$ 是否成立。

$a^3-b^3=(a-b)(a^2+ab+b^2)$

因为 $p$ 是质数的关系，则 $a-b=1$ ， $a^2+ab+b^2=p$ 。

然后 $a,b$ 作为两个未知量， $b=a-1$ ，然后剩下的就是一个一元二次方程啦~

如果能够找到整数解即说明原问题成立~



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;
#define eps 1e-7

bool solve(double x)
{
    double sq = sqrt(9.0-12.0*(1.0-x));
    double ans = (3.0+sq)/6.0;
    if(fabs(ans-LL(ans))<eps)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        double x;
        cin>>x;
        if(solve(x))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}
```

