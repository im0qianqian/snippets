# River Hopscotch

## **Description**

> Every year the cows hold an event featuring a peculiar version of hopscotch that involves carefully jumping from rock to rock in a river. The excitement takes place on a long, straight river with a rock at the start and another rock at the end, L units away from the start (1 ≤ L ≤ 1,000,000,000). Along the river between the starting and ending rocks, N (0 ≤ N ≤ 50,000) more rocks appear, each at an integral distance Di from the start (0 < Di < L).
>
> To play the game, each cow in turn starts at the starting rock and tries to reach the finish at the ending rock, jumping only from rock to rock. Of course, less agile cows never make it to the final rock, ending up instead in the river.
>
> Farmer John is proud of his cows and watches this event each year. But as time goes by, he tires of watching the timid cows of the other farmers limp across the short distances between rocks placed too closely together. He plans to remove several rocks in order to increase the shortest distance a cow will have to jump to reach the end. He knows he cannot remove the starting and ending rocks, but he calculates that he has enough resources to remove up to M rocks (0 ≤ M ≤ N).
>
> FJ wants to know exactly how much he can increase the shortest distance *before* he starts removing the rocks. Help Farmer John determine the greatest possible shortest distance a cow has to jump after removing the optimal set of M rocks.



## **Input**

> Line 1: Three space-separated integers: L, N, and M 
>
> Lines 2..N+1: Each line contains a single integer indicating how far some rock is away from the starting rock. No two rocks share the same position.



## **Output**

> Line 1: A single integer that is the maximum of the shortest distance a cow has to jump after removing M rocks



## **Sample Input**

    25 5 2
    2
    14
    11
    21
    17



## **Sample Output**

    4



## **题意**

一条长l的河中，有n个垫脚石，现在给出它们距离起始点的距离，要求移除其中的m块，使得间距最小的两块石头之间的距离最大。



## **思路**

和 [POJ 3273](https://www.dreamwings.cn/poj3273/4425.html) 一样的题型，相应的，我们可以利用二分去判断路径中的每一个间距，判断mid区间下需要去掉多少个垫脚石，然后做出调整。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<queue>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;

int a[51000],n,l,m;

int solve(int high,int low)
{
    while(low<=high)
    {
        int mid=(low+high)/2;   //当前需要判断的间距
        int count=0;            //可以去掉的垫脚石数目
        int s=0,e=1;
        while(e<n)
        {
            if(a[e]-a[s]>=mid)  //一个包含mid的区间判断完毕
                s=e,e++;
            else e++,count++;   //继续扩充区间
        }
        if(count>m)             //区间过大
            high=mid-1;
        else low=mid+1;
    }
    return high;
}
int main()
{
    while(~scanf("%d%d%d",&l,&n,&m))
    {
        int high=l,low=(1<<25);
        a[0]=0,a[n+1]=l;
        n+=2;
        for(int i=1; i<n-1; i++)
            scanf("%d",a+i);
        sort(a,a+n);
        for(int i=1; i<n; i++)
            low=min(low,a[i]-a[i-1]);
        printf("%d\n",solve(high,low));
    }
}
```

