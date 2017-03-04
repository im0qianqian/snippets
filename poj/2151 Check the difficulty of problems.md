# Check the difficulty of problems

## **Description**

> Organizing a programming contest is not an easy job. To avoid making the problems too difficult, the organizer usually expect the contest result satisfy the following two terms: 
>
> 1. All of the teams solve at least one problem. 
>
> 2. The champion (One of those teams that solve the most problems) solves at least a certain number of problems. 
>
>
> Now the organizer has studied out the contest problems, and through the result of preliminary contest, the organizer can estimate the probability that a certain team can successfully solve a certain problem. 
>
> Given the number of contest problems M, the number of teams T, and the number of problems N that the organizer expect the champion solve at least. We also assume that team i solves problem j with the probability Pij (1 <= i <= T, 1<= j <= M). Well, can you calculate the probability that all of the teams solve at least one problem, and at the same time the champion team solves at least N problems? 



## **Input**

> The input consists of several test cases. The first line of each test case contains three integers M (0 < M <= 30), T (1 < T <= 1000) and N (0 < N <= M). Each of the following T lines contains M floating-point numbers in the range of [0,1]. In these T lines, the j-th number in the i-th line is just Pij. A test case of M = T = N = 0 indicates the end of input, and should not be processed.



## **Output**

> For each test case, please output the answer in a separate line. The result should be rounded to three digits after the decimal point.



## **Sample Input**

    2 2 2
    0.9 0.9
    1 0.9
    0 0 0



## **Sample Output**

    0.972



## **题意**

ACM比赛中，共 $M$ 道题，$T$ 个队， $p[i][j]$ 表示第 $i$ 队解出第 $j$ 题的概率，问每队至少解出一题且冠军队至少解出N道题的概率。 



## **思路**

首先，每队至少解出一题中一定包含所有队解题数目至少为1并且都是少于 $n$ 的，如果减去这一部分便是至少有一个队伍的解题数目大于 $n$ 了，至于冠军队嘛！我们不用关心，因为我们只需要让它大于 $n$ 就行了。

- ans: 所有队至少解出一题的概率
- as  : 所有队至少解出一题但是不超过 $n-1$ 题的概率

**最终答案**： $ans-as$



一个队伍解出不超过 $n-1$ 道题目的概率是解出 $1、2、...、n-1$ 道题的概率之和。

$pd[j][k]$ 表示在前 $j$ 道题中做对 $k$ 道的概率，于是有

$pd[j][k]=pd[j-1][k]*(1.0-p[i][j])+pd[j-1][k-1]*p[i][j]$

其中考虑 $j$ 题，要么做对，要么做错，只有这两种情况，其概率相加。



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
#include<stack>

double pd[35][35],p[1005][35]; //pd[i][j]表示在前i道题中做对j道的概率
int main()
{
    int m,t,n;
    while(~scanf("%d%d%d",&m,&t,&n)&&(m||t||n))
    {
        double ans=1.0,as=1.0;  //ans 为所有队至少A一道题的概率 as为所有队A的题目数量都不超过n的概率
        memset(pd,0,sizeof(pd));
        for(int i=0; i<t; i++)
        {
            double temp=1.0;
            for(int j=1; j<=m; j++)
            {
                scanf("%lf",&p[i][j]);
                temp*=1.0-p[i][j];  //逆命题就是该队伍一道题也没有做对
            }
            ans*=1.0-temp;      //因为要保证所有队伍都满足，所以用乘法定理
        }
        for(int i=0; i<t; i++)
        {
            memset(pd,0,sizeof(pd));
            pd[0][0]=1.0;         //在前0道题目中A0道永真
            for(int j=1; j<=m; j++)
            {
                pd[j][0]=pd[j-1][0]*(1-p[i][j]);
                for(int k=1; k<=j; k++)
                    pd[j][k]=pd[j-1][k]*(1.0-p[i][j])+pd[j-1][k-1]*p[i][j]; //第j题要么做对，要么做错
            }
            double temp=0.0;
            for(int j=1; j<n; j++)
                temp+=pd[m][j];     //前m道题中做对数目少于n的子命题（做对1、2...n-1道）之间用加法定理
            as*=temp;           //各组之间乘法定理
        }
        printf("%.3f\n",ans-as);
    }
    return 0;
}
```

