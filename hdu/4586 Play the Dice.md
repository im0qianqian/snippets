# **Play the Dice**

## **Problem Description**
>There is a dice with n sides, which are numbered from 1,2,...,n and have the equal possibility to show up when one rolls a dice. Each side has an integer ai on it. Now here is a game that you can roll this dice once, if the i-th side is up, you will get ai yuan. What's more, some sids of this dice are colored with a special different color. If you turn this side up, you will get once more chance to roll the dice. When you roll the dice for the second time, you still have the opportunity to win money and rolling chance. Now you need to calculate the expectations of money that we get after playing the game once.



## **Input**

>Input consists of multiple cases. Each case includes two lines.
>
>The first line is an integer n (2<=n<=200), following with n integers ai(0<=ai<200)
>
>The second line is an integer m (0<=m<=n), following with m integers bi(1<=bi<=n), which are the numbers of the special sides to get another more chance.



## **Output**

>Just a real number which is the expectations of the money one can get, rounded to exact two digits. If you can get unlimited money, print inf.



## **Sample Input**

    6 1 2 3 4 5 6
    0
    4 0 0 0 0
    1 3



## **Sample Output**

    3.50
    0.00



## **题意**

给你一个有n面的骰子，每一个面都有一个值（money），然后有一些特殊的面，当掷到这些特殊的面的时候你会获得一次新的机会再掷一次，问最终得到money的期望。



## **思路**

其实最终我们只是会获得再次投掷的机会，所以这部分和刚开始投掷是完全一样的。

$sum=a_1+a_2+…+a_n$ ，当前期望值为 $sum/n$

对于后面的m次，每一次都是在原来基础上乘以 $(m/n)$ ，也就是 $(sum/n)*(m/n)^k$

利用等比数列求和公式可得，最终结果 $ans=sum/(n-m)$



但是还有几点需要注意：

- 假如 $sum=0$ 的时候，每个面都不会对答案做出贡献，所以直接输出0.00 。
- 假如 $n=m$ 的时候，说明骰子的每一面都是特殊的面，这样我们永远也不会做完这场游戏，此时结果为 $inf$



## **AC代码**

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>
using namespace std;
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        int m,s,sum;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&s);
            sum+=s;
        }
        scanf("%d",&m);
        for(int i=0; i<m; i++)
            scanf("%d",&s);
        if(sum == 0)
            printf("0.00\n");
        else if(m==n)
            printf("inf\n");
        else
            printf("%.2lf\n",(double)sum/(n-m));
    }
    return 0;
}
```

