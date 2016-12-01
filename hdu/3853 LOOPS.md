# **HDU 3853 LOOPS**

## **Problem Description**

> Akemi Homura is a Mahou Shoujo (Puella Magi/Magical Girl).
>
> Homura wants to help her friend Madoka save the world. But because of the plot of the Boss Incubator, she is trapped in a labyrinth called LOOPS.

![img](http://acm.hdu.edu.cn/data/images/3853-1.jpg)

> The planform of the LOOPS is a rectangle of R*C grids. There is a portal in each grid except the exit grid. It costs Homura 2 magic power to use a portal once. The portal in a grid G(r, c) will send Homura to the grid below G (grid(r+1, c)), the grid on the right of G (grid(r, c+1)), or even G itself at respective probability (How evil the Boss Incubator is)!
>
> At the beginning Homura is in the top left corner of the LOOPS ((1, 1)), and the exit of the labyrinth is in the bottom right corner ((R, C)). Given the probability of transmissions of each portal, your task is help poor Homura calculate the EXPECT magic power she need to escape from the LOOPS.



## **Input**

> The first line contains two integers R and C (2 <= R, C <= 1000).
>
> The following R lines, each contains C*3 real numbers, at 2 decimal places. Every three numbers make a group. The first, second and third number of the cth group of line r represent the probability of transportation to grid (r, c), grid (r, c+1), grid (r+1, c) of the portal in grid (r, c) respectively. Two groups of numbers are separated by 4 spaces.
>
> It is ensured that the sum of three numbers in each group is 1, and the second numbers of the rightmost groups are 0 (as there are no grids on the right of them) while the third numbers of the downmost groups are 0 (as there are no grids below them).
>
> You may ignore the last three numbers of the input data. They are printed just for looking neat.
>
> The answer is ensured no greater than 1000000.
>
> Terminal at EOF



## **Output**

> A real number at 3 decimal places (round to), representing the expect magic power Homura need to escape from the LOOPS.



## **Sample Input**

    2 2
    0.00 0.50 0.50    0.50 0.00 0.50
    0.50 0.50 0.00    1.00 0.00 0.00



## **Sample Output**

    6.000


## **题意**

有一个迷宫r行c列，开始在 $[1,1]$ ，现在要走到 $[r,c]$ ，在点 $[x,y]$ 处我们有 $P_0$ 的概率保持原地不动，有 $P_1$ 的概率走到 $[x][y+1]$ ，有 $P_2$ 的概率走到 $[x+1][y]$ ，每次消耗2点魔力，求平均消耗多少魔力能走到 $[r,c]$ 。



## **分析**

我们假设 $dp[i][j]​$ 表示在点 $[i,j]​$ 到达 $[r,c]​$ 所需要消耗的平均魔力，也就是期望。

则从 $dp[i][j]$ 可以到达 $dp[i][j],dp[i][j+1],dp[i+1][j]$ ，对应概率分别为 $P_0,P_1,P_2$ .

于是有 $dp[i][j]=P_0*dp[i][j]+P_1*dp[i][j+1]+P_2*dp[i+1][j]$ ，移项化简可得 $dp[i][j]=P_1/(1-P_0)*dp[i][j+1]+P_2/(1-P_0)*dp[i+1][j]+2/(1-P_0)$ .

根据状态转移方程我们可以看出，计算dp的时候只需要倒着推就可以了。



## **AC代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
#define MAXX 1005
#define eps 1e-5

double a[MAXX][MAXX][3];
double dp[MAXX][MAXX];
int r,c;
void solve()
{
    dp[r][c]=0;
    for(int i=r; i>0; i--)
        for(int j=c; j>0; j--)
        {
            if(fabs(1-a[i][j][0])<eps)continue;
            dp[i][j]=a[i][j][1]/(1-a[i][j][0])*dp[i][j+1]+a[i][j][2]/(1-a[i][j][0])*dp[i+1][j]+2/(1-a[i][j][0]);
        }
    printf("%.3lf\n",dp[1][1]);
}

int main()
{
    while(~scanf("%d%d",&r,&c))
    {
        for(int i=1; i<=r; i++)
            for(int j=1; j<=c; j++)
                for(int k=0; k<3; k++)
                    scanf("%lf",&a[i][j][k]);
        solve();
    }
    return 0;
}
```

