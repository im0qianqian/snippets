# Expedition

## **Description**

> A group of cows grabbed a truck and ventured on an expedition deep into the jungle. Being rather poor drivers, the cows unfortunately managed to run over a rock and puncture the truck's fuel tank. The truck now leaks one unit of fuel every unit of distance it travels. 
>
> To repair the truck, the cows need to drive to the nearest town (no more than 1,000,000 units distant) down a long, winding road. On this road, between the town and the current location of the truck, there are N (1 <= N <= 10,000) fuel stops where the cows can stop to acquire additional fuel (1..100 units at each stop). 
>
> The jungle is a dangerous place for humans and is especially dangerous for cows. Therefore, the cows want to make the minimum possible number of stops for fuel on the way to the town. Fortunately, the capacity of the fuel tank on their truck is so large that there is effectively no limit to the amount of fuel it can hold. The truck is currently L units away from the town and has P units of fuel (1 <= P <= 1,000,000). 
>
> Determine the minimum number of stops needed to reach the town, or if the cows cannot reach the town at all. 



## **Input**

> Line 1: A single integer, N 
>
> Lines 2..N+1: Each line contains two space-separated integers describing a fuel stop: The first integer is the distance from the town to the stop; the second is the amount of fuel available at that stop. 
>
> Line N+2: Two space-separated integers, L and P



## **Output**

> Line 1: A single integer giving the minimum number of fuel stops necessary to reach the town. If it is not possible to reach the town, output -1.



## **Sample Input**

    4
    4 4
    5 2
    11 5
    15 10
    25 10



## **Sample Output**

    2


## **题意**

一辆卡车要行驶 `L` 单位距离。最开始时，卡车上有 `P` 单位汽油，每向前行驶 `1` 单位距离消耗 `1` 单位汽油。如果在途中车上的汽油耗尽，卡车就无法继续前行，即无法到达终点。途中共有 `N` 个加油站，加油站提供的油量有限，卡车的油箱无限大，无论加多少油都没问题。给出每个加油站距离终点的距离和能够提供的油量，问卡车从起点到终点至少要加几次油？如果不能到达终点，输出 `-1` 。



## **思路**

我们可以变换一下思考方式，在卡车开往终点的途中，只有在加油站才可以加油，我们可以认为，如果经过加油站 `i` 后，不论任何时候都可以加油 `Bi` ，那么，因为希望到达终点时加油次数尽可能少，我们可以当燃料为 `0` 之后再进行加油！至于选择加多少呢？当然是已经过加油站所能加油的最大值啦~ 使用从大到小依次取出数值的优先队列可解决。



## **AC 代码**

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
struct po
{
    int later;
    int wi;
} sit[10005];
bool cmp(po a,po b)
{
    return a.later<b.later;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0; i<n; i++)
            scanf("%d%d",&sit[i].later,&sit[i].wi);
        int L,P;
        scanf("%d%d",&L,&P);
        for(int i=0; i<n; i++)
            sit[i].later=L-sit[i].later;
        sit[n].later=L;
        sit[n].wi=0;
        sort(sit,sit+n,cmp);
        priority_queue<int>wi;
        int ans=0,pos=0,tank=P;
        for(int i=0; i<=n; i++)
        {
            int d=sit[i].later-pos;
            while(tank<d)
            {
                if(wi.empty())
                {
                    puts("-1");
                    goto end1;
                }
                tank+=wi.top();
                wi.pop();
                ans++;
            }
            tank-=d;
            pos=sit[i].later;
            wi.push(sit[i].wi);
        }
        printf("%d\n",ans);
end1:
        ;
    }
    return 0;
}
```

