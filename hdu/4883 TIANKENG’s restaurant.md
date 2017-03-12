# TIANKENG’s restaurant

## **Problem Description**

> TIANKENG manages a restaurant after graduating from ZCMU, and tens of thousands of customers come to have meal because of its delicious dishes. Today n groups of customers come to enjoy their meal, and there are Xi persons in the ith group in sum. Assuming that each customer can own only one chair. Now we know the arriving time STi and departure time EDi of each group. Could you help TIANKENG calculate the minimum chairs he needs to prepare so that every customer can take a seat when arriving the restaurant?



## **Input**

> The first line contains a positive integer T(T<=100), standing for T test cases in all. Each cases has a positive integer n(1<=n<=10000), which means n groups of customer. Then following n lines, each line there is a positive integer Xi(1<=Xi<=100), referring to the sum of the number of the ith group people, and the arriving time STi and departure time Edi(the time format is hh:mm, 0<=hh<24, 0<=mm<60), Given that the arriving time must be earlier than the departure time. Pay attention that when a group of people arrive at the restaurant as soon as a group of people leaves from the restaurant, then the arriving group can be arranged to take their seats if the seats are enough.



## **Output**

> For each test case, output the minimum number of chair that TIANKENG needs to prepare.



## **Sample Input**

    2
    2
    6 08:00 09:00
    5 08:59 09:59
    2
    6 08:00 09:00
    5 09:00 10:00



## **Sample Output**

    11
    6


## **题意**

给出一些时间段，以及在这段时间内会来进餐的人数，求至少需要安排多少个座位才可以满足所有的需求。



## **思路**

最大覆盖数，我们可以把时间的时和分通过某种运算合并成一个数字，比如 `h*60+m` ，然后在相应时间段内数组所有元素增加当前进餐的人数，最后只需要求得最大的那一点的人数即可。



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

int sum[1500];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,xi,h1,m1,h2,m2;
        scanf("%d",&n);
        memset(sum,0,sizeof(sum));
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%*c%d%d%*c%d",&xi,&h1,&m1,&h2,&m2);
            int st=h1*60+m1;
            int ed=h2*60+m2;
            for(int i=st; i<ed; i++)
                sum[i]+=xi;
        }
        int ans=0;
        for(int i=0; i<1500; i++)
            ans=max(sum[i],ans);
        printf("%d\n",ans);
    }
    return 0;
}
```

