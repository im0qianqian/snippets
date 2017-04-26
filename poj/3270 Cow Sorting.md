# Cow Sorting

## **Description**

> Farmer John's N (1 ≤ N ≤ 10,000) cows are lined up to be milked in the evening. Each cow has a unique "grumpiness" level in the range 1...100,000. Since grumpy cows are more likely to damage FJ's milking equipment, FJ would like to reorder the cows in line so they are lined up in increasing order of grumpiness. During this process, the places of any two cows (not necessarily adjacent) can be interchanged. Since grumpy cows are harder to move, it takes FJ a total of X+Y units of time to exchange two cows whose grumpiness levels are X and Y.
>
> Please help FJ calculate the minimal time required to reorder the cows.



## **Input**

> Line 1: A single integer: N. 
>
> Lines 2..N+1: Each line contains a single integer: line i+1 describes the grumpiness of cow i. 



## **Output**

> Line 1: A single line with the minimal time required to reorder the cows in increasing order of grumpiness.



## **Sample Input**

    3
    2
    3
    1



## **Sample Output**

    7



## **题意**

有 n 头牛，每头牛都有一个独一无二的愤怒值，想要把这些牛根据愤怒值的大小进行排序（从小到大），交换任意两头牛位置所花费的时间是他们的愤怒值之和，求最小的交换时间。



## **思路**

**假设**

初始状态为： $1~3~4~5~2$

结束状态为： $1~2~3~4~5$

因为有 $1->1$ ，所以 $(1)$ 为一个轮换，另外还有 $3->2->5->4$ ，所以 $(3~4~5~2)$ 为另一个轮换。



对于每一个长度大于 $1$ 的轮换，其初始状态的元素一定不在结束状态的位置，也就是说，在这个轮换中所有的数字都需要移动，但是怎样才可以让交换所付出的代价最小呢？

首先，对于轮换中的元素，每一个数字都需要至少交换一次才可以到达目标位置，很明显，我们可以用轮换中最小的元素去交换其他元素这样付出的代价才是最小的，此时的代价为 $sum-min+(len-1)×min$ 

其中 $sum$ 为轮换中所有元素之和， $min$ 为轮换中最小元素， $len$ 为轮换的长度。



另外，还有一种情况，假如一个轮换中的最小元素也很大，反复交换所付出的代价也就会变得非常大了，但是我们可以把其他轮换中的元素（这里取全局最小值为最优）拿来与当前轮换的最小值进行交换，然后继续上面的步骤，计算结束后再交换回去，这样做的代价或许会比原来少一点，此时的代价为 $sum+min+(len+1)×ksmin$



**最终的答案为所有轮换所计算的最小代价之和。**



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define INF (1<<25)

int a[11000];
int b[11000];
bool vis[110000];
int main()
{
    int n;
    while(cin>>n)
    {
        memset(vis,false,sizeof(vis));
        map<int,int>mapp;           // n元置换群映射
        int ksmin=INF;
        for(int i=0; i<n; i++)
        {
            scanf("%d",a+i);
            ksmin=min(ksmin,a[i]);  // 找出所有牛的最小愤怒值
        }
        memcpy(b,a,sizeof(int)*n);
        sort(b,b+n);
        for(int i=0; i<n; i++)      // 建立映射关系
            mapp[a[i]]=b[i];
        int ans=0;
        for(int i=0; i<n; i++)
        {
            if(!vis[a[i]])          // 遍历每个轮换
            {
                int p=a[i],sum=0,minn=a[i],len=0;   // 记录和与长度以及轮换中最小值
                while(!vis[p])
                {
                    sum+=p;
                    ++len;
                    minn=min(minn,p);
                    vis[p]=true;
                    p=mapp[p];
                }
                ans+=min(sum-minn+(len-1)*minn,sum+minn+(len+1)*ksmin);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

