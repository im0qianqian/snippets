# Fence Repair

## **Description**

> Farmer John wants to repair a small length of the fence around the pasture. He measures the fence and finds that he needs N (1 ≤ N ≤ 20,000) planks of wood, each having some integer length Li (1 ≤ Li ≤ 50,000) units. He then purchases a single long board just long enough to saw into the N planks (i.e., whose length is the sum of the lengths Li). FJ is ignoring the "kerf", the extra length lost to sawdust when a sawcut is made; you should ignore it, too.
>
> FJ sadly realizes that he doesn't own a saw with which to cut the wood, so he mosies over to Farmer Don's Farm with this long board and politely asks if he may borrow a saw.
>
> Farmer Don, a closet capitalist, doesn't lend FJ a saw but instead offers to charge Farmer John for each of the N-1 cuts in the plank. The charge to cut a piece of wood is exactly equal to its length. Cutting a plank of length 21 costs 21 cents.
>
> Farmer Don then lets Farmer John decide the order and locations to cut the plank. Help Farmer John determine the minimum amount of money he can spend to create the N planks. FJ knows that he can cut the board in various different orders which will result in different charges since the resulting intermediate planks are of different lengths.



## **Input**

> Line 1: One integer N, the number of planks 
>
> Lines 2..N+1: Each line contains a single integer describing the length of a needed plank



## **Output**

> Line 1: One integer: the minimum amount of money he must spend to make N-1 cuts



## **Sample Input**

    3
    8
    5
    8



## **Sample Output**

    34



## **题意**

FJ需要修补牧场的围栏，他需要 $N$ 块长度为 $L_i$ 的木头（N planks of woods）。

开始时，FJ只有一块无限长的木板，因此他需要把无限长的木板锯成 $N$ 块长度为 $L_i$ 的木板，Farmer Don提供FJ锯子，但必须要收费的，收费的标准是对应每次据出木块的长度，求最小的花费。

比如说测试数据 5 8 8，一开始，FJ需要在无限长的木板上锯下长度 21 的木板（5+8+8=21），第二次锯下长度为 5 的木板，第三次锯下长度为 8 的木板，至此就可以将长度分别为 5 8 8 的木板找出。



## **思路**

既然最终要找的是长度为 $L_i$ 的 $N$ 块木板，那么我们可以用从下向上组合的方式选择（类似于数塔问题）

首先假设我们有长度为5 8的两根木头，那它是由长度为13的木头得来的，于是，此时便有了长13 8的两根木头，同样，它是由长21的木头得来的，于是最终的最小花费为 $13+21=34$ 。

哈夫曼问题，总是选取最小的两个，然后组合之后加入队列，当到达树的顶端时，组合完毕，输出路径中各组合节点的和。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
typedef __int64 LL;

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        priority_queue<int,vector<int>,greater<int> >sk;    //优先队列 小顶堆
        int num;
        LL ans=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&num);
            sk.push(num);
        }
        if(sk.size()==1)    //如果只有1根木头
            ans=sk.top();
        while(sk.size()>1)
        {
            int a=sk.top();
            sk.pop();
            a+=sk.top();    //选取最小的两个求和
            ans+=a;
            sk.pop();
            sk.push(a); //加入队列
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
```

