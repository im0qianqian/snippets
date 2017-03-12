# Task schedule

## **Problem Description**

> 有一台机器，并且给你这台机器的工作表，工作表上有n个任务，机器在ti时间执行第i个任务，1秒即可完成1个任务。
>
> 有m个询问，每个询问有一个数字q，表示如果在q时间有一个工作表之外的任务请求，请计算何时这个任务才能被执行。
>
> 机器总是按照工作表执行，当机器空闲时立即执行工作表之外的任务请求。



## **Input**

> 输入的第一行包含一个整数T， 表示一共有T组测试数据。
>
> 对于每组测试数据：
>
> 第一行是两个数字n, m，表示工作表里面有n个任务, 有m个询问；
>
> 第二行是n个不同的数字t1, t2, t3....tn，表示机器在ti时间执行第i个任务。
>
> 接下来m行，每一行有一个数字q，表示在q时间有一个工作表之外的任务请求。
>
> 特别提醒：m个询问之间是无关的。
>
> [Technical Specification]
>
> 1. T <= 50
> 2. 1 <= n, m <= 10^5
> 3. 1 <= ti <= 2*10^5, 1 <= i <= n*
> 4. *1 <= q <= 2*10^5



## **Output**

> 对于每一个询问，请计算并输出该任务何时才能被执行，每个询问输出一行。



## **Sample Input**

    1
    5 5
    1 2 3 5 6
    1
    2
    3
    4
    5



## **Sample Output**

    4
    4
    4
    4
    7


## **题意**

需要输出的是大于等于给定数且没有出现过的最小的数。

因此这一个数字一定是小于等于给定数列最大值+1的，我们可以从最大位置开始枚举，用一个 now 变量来表示大于等于当前位置且为空的坐标，然后 i-- ，假如当前位置的数字没有出现过，则更新 now ，否则数组赋值为 now 。

最后便是输入输出的环节啦！



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

bool ni[220000];
int ha[220000];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m,temp;
        scanf("%d%d",&n,&m);
        memset(ni,false,sizeof(ni));
        for(int i=0; i<n; i++)
        {
            scanf("%d",&temp);
            ni[temp]=true;
        }
        int now=210000;
        for(int i=210000; i>0; i--)
        {
            if(!ni[i])now=i;
            ha[i]=now;
        }
        for(int i=0; i<m; i++)
        {
            scanf("%d",&temp);
            printf("%d\n",ha[temp]);
        }
    }
    return 0;
}
```

