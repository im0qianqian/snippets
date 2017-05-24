# Quadrat

## **Description**

> It is well-known that for any n there are exactly four n-digit numbers (including ones with leading zeros) that are self-squares: the last n digits of the square of such number are equal to the number itself. These four numbers are always suffixes of these four infinite sequences: 
>
> ...0000000000 
>
> ...0000000001 
>
> ...8212890625 
>
> ...1787109376 
>
> For example, =87909376, which ends with 09376.
>
> You are required to count the numbers that are almost self-squares: such that each of the last n digits of their square is at most d away from the corresponding digit of the number itself. Note that we consider digits 0 and 9 to be adjacent, so for example digits that are at most 3 away from digit 8 are 5, 6, 7, 8, 9, 0 and 1. 



## **Input**

> The first line contains the number of test cases t,1≤t≤72. Each of the next t lines contains one test case: two numbers n(1≤n≤ 18) and d(0≤ d≤3). 



## **Output**

> For each test case, output the number of almost self-squares with length n and the (circular) distance in each digit from the square at most d in a line by itself.



## **Example Input**

    2
    5 0
    2 1



## **Example Output**

    4
    12



## **Hint**

> In the second case, number 12's almost self-squares are: 00, 01, 10, 11, 15, 25, 35, 66, 76, 86, 90, 91



## **题意**

找出有多少个数，它的长度为 `n` ，且平方后模 `10^n` 与原来数之间的差距不大于 `d` （每一位字符差距和）。



## **思路**

对于 `10` 以内的数，假如 `d=0` 时，只有四个数满足要求，分别为 `0、1、5、6` 。

假如 `d=2` 时，有八个数满足要求： `0、1、2、4、5、6、7、9` 。

写一个暴力的程序当然很简单咯~

所以嘛！先用它来打表看看，找出 `1<=n<=4` 范围内所有 `0<=d<=3` 的答案。

    1:      4 4 8 8
    2:      4 12 40 56
    3:      4 36 200 392
    4:      4 108 1000 2744

于是发现了 `dp[i][j]=dp[i-1][j]*(2*j+1)` 的规律，其中 `i` 为数的长度， `j` 为最大距离。



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
#include<map>
const int mod = 1e9+7;
typedef long long LL;

LL dp[20][4];
void init()
{
    dp[1][0]=dp[1][1]=4;
    dp[1][2]=dp[1][3]=8;
    for(int i=2; i<=18; i++)
        for(int j=0; j<4; j++)
            dp[i][j]=dp[i-1][j]*(2*j+1);
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,k;
        cin>>n>>k;
        cout<<dp[n][k]<<endl;
    }
    return 0;
}
```

