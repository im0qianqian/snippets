# Balance

## **Description**

> Gigel has a strange "balance" and he wants to poise it. Actually, the device is different from any other ordinary balance. 
>
> It orders two arms of negligible weight and each arm's length is 15. Some hooks are attached to these arms and Gigel wants to hang up some weights from his collection of G weights (1 <= G <= 20) knowing that these weights have distinct values in the range 1..25. Gigel may droop any weight of any hook but he is forced to use all the weights. 
>
> Finally, Gigel managed to balance the device using the experience he gained at the National Olympiad in Informatics. Now he would like to know in how many ways the device can be balanced. 
>
> Knowing the repartition of the hooks and the set of the weights write a program that calculates the number of possibilities to balance the device. 
>
> It is guaranteed that will exist at least one solution for each test case at the evaluation. 



## **Input**

> The input has the following structure: 
>
> - the first line contains the number C (2 <= C <= 20) and the number G (2 <= G <= 20); 
> - the next line contains C integer numbers (these numbers are also distinct and sorted in ascending order) in the range -15..15 representing the repartition of the hooks; each number represents the position relative to the center of the balance on the X axis (when no weights are attached the device is balanced and lined up to the X axis; the absolute value of the distances represents the distance between the hook and the balance center and the sign of the numbers determines the arm of the balance to which the hook is attached: '-' for the left arm and '+' for the right arm); 
> - on the next line there are G natural, distinct and sorted in ascending order numbers in the range 1..25 representing the weights' values. 



## **Output**

The output contains the number M representing the number of possibilities to poise the balance.



## **Sample Input**

    2 4	
    -2 3 
    3 4 5 8



## **Sample Output**

    2



## **题意**

有一个天平，左臂右臂各长15，然后给出c，g。

c代表有几个挂钩，挂钩给出负数代表在左臂的距离，正数则在右臂；

g代表有几个砝码，要你求出使得这个天平保持平衡有几种方法，要求所有砝码全部使用完。



## **思路**

$dp[i][j]$ ， $i$ 为放置的砝码数量， $j$ 为平衡状态，当 $j=0$ 时平衡。

但是这样定义的话 $j$ 有可能为负数，在当作数组下标的时候是不允许的，于是我们计算出天枰左倾或者右倾的最大限度是7500。

则 $dp[i][7500]$ 代表 $i$ 个砝码平衡的方法数目。

**转换为了一个01背包的问题**

状态转移方程： $dp[i][j+w[i]*c[k]]+=dp[i-1][j]$

对于第 $i$ 个砝码，它可以被在放置在任何地方，于是对每一个挂钩处 $j+w[i]*c[k]$ 都有贡献。

最终答案： $dp[g][7500]$ 



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
int dp[25][16000];
int a[25],b[25];
int main()
{
    int c,g;
    while(~scanf("%d%d",&c,&g))
    {
        memset(dp,0,sizeof(dp));
        for(int i=1; i<=c; i++)
            scanf("%d",a+i);
        for(int i=1; i<=g; i++)
            scanf("%d",b+i);
        dp[0][7500]=1;
        for(int i=1; i<=g; i++)
            for(int j=0; j<15000; j++)
                if(dp[i-1][j])      //一个小小的优化
                    for(int k=1; k<=c; k++)
                        dp[i][j+b[i]*a[k]]+=dp[i-1][j];
        printf("%d\n",dp[g][7500]);
    }
    return 0;
}
```

