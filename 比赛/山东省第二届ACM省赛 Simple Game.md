# Simple Game

## **Problem Description**

> Here is a simple game. In this game, there are several piles of stones and two players. The two players play in turn. In each turn, one can choose at least one pile and at most three piles to take away arbitrary number of stones from the pile (Of course the number of stones, which is taken away, cannot be zero and cannot be larger than the number of stones in the chosen pile). If after a player ′ s turn, there is no stone left, the player is the loser.
>
> Suppose that the two players are all very smart. Your job is to tell whether the player who plays first can win the game or not.



## **Input**

> The input has multiple test cases. The first line of the input contains one integer C, which is the number of test cases. Each test case begins with a line contains one integer N(1 <= N <=10000),which is the number of piles. Then comes N positive integers, which are not larger than 10000000. These N integers represent the number of stones in each pile.



## **Output**

> For each test case, output "Yes" in a single line, if the player who play first will win, otherwise output "No".



## **Example Input**

    2
    2
    1
    1
    4
    2
    2
    2
    2



## **Example Output**

    Yes
    No



## **题意**

一共有 `n` 堆石子，每一堆中的石子个数均不相同，两人从这 `n` 堆中取石子，每次最少取一个，最多取三堆石子（可以从三堆石子中取任意个），取走最后一枚石子的人获胜，求先手是否必胜。



## **思路**

**`Nim+Bash`**

`Nim` 博弈说的是有三堆石子，两人轮流从某一堆中取任意多的石子，规定每次至少取一个，取走最后一枚石子的人获胜。

经典的 `Nim` 博弈中，只要所有堆的石子个数异或等于 `1` 便是必胜态，因为先手总能在石子最多的一堆中拿走一些使得所有堆的石子个数异或等于 `0` ，也就是先手总能将对手转移到必败态，而后手不论如何选取，异或的结果都是 `1` ，也就是说后手不论如何选取都不会改变先手的必胜态。

**举例：**

三堆石子分别是： `1、2、4` ，此时异或结果非零。

先手在第三堆中选取 `1` 个，石子个数变为 `1、2、3` ，此时异或结果为零，转移到后手的必败态。

后手不论如何选取，石子个数的异或值都非零，转移到先手的必胜态。

...

先手拿走了最后一枚石子，获胜！

---

`Bash` 博弈说只有一堆石子，两人轮流取，最少取一个，最多取 `m` 个，取走最后一枚石子的人获胜。

这种情况下当 `n` 为 `m+1` 的整数倍时为先手必败态，因为后手总能选取 `m+1-先手拿的个数` 个石子使得后手最终拿走最后一枚石子。

**举例：**

石子个数 `n=30` ， `m=5`

先手 `2` ，后手 `5+1-2` ，此时剩余 `24`

先手 `5` ，后手 `5+1-5` ，此时剩余 `18`

先手 `1` ，后手 `5+1-1` ，此时剩余 `12`

先手 `3` ，后手 `5+1-3` ，此时剩余 `6`

先手 `4` ，后手 `5+1-4` ，此时剩余 `0`

**后手获胜**

而当 `n=r×(m+1)+s` 中 `s!=0` 时，先手必胜，因为先手可以先选取 `s` 个石子转移到后手必败态，于是...

---

对于这道题目来说呢，如果所有数的二进制每一位的数量和都为 `4` 的整数倍时为必败态。

**假如有五堆石子：** `7、11、13、14、15`

|      | 1/1  | 2/2  | 3/4  | 4/8  |
| :--: | :--: | :--: | :--: | :--: |
|  7   |  1   |  1   |  1   |  0   |
|  11  |  1   |  1   |  0   |  1   |
|  13  |  1   |  0   |  1   |  1   |
|  14  |  0   |  1   |  1   |  1   |
|  15  |  1   |  1   |  1   |  1   |

这一组数据为先手必败态。

**我们先来看纵向的状态**，先手无论从哪几行选取，我都可以在其他 `4-先手选取的行数` 行选取，最终最后一行也一定是后手取走。

比如先手可以取走最低位的三个 `1` ，然后我可以拿走剩余的那一个。

**然后再看横向的状态**，先手无论选取最多三堆的某些石子，我都可以选取相应石子使得当前这四行的石子数量保持一致，即仍然保证了当前所有位一的个数都是 `4` 的整数倍，于是转移到先手必败态。

结合起来看的话也就是一个纵向 `Bash` ，横向 `Nim` 的博弈问题。



## **AC 代码**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

int bin[25];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(bin,0,sizeof(bin));
        int n;
        scanf("%d",&n);
        while(n--)
        {
            int k;
            scanf("%d",&k);
            for(int i=0; k; i++)
            {
                bin[i]+=k%2;
                k>>=1;
            }
        }
        bool flag=true;
        for(int i=0; i<25; i++)
            if(bin[i]%4!=0)
            {
                flag=false;
                break;
            }
        printf(!flag?"Yes\n":"No\n");
    }
    return 0;
}
```

