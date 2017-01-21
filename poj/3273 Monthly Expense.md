# Monthly Expense

## **Description**

> Farmer John is an astounding accounting wizard and has realized he might run out of money to run the farm. He has already calculated and recorded the exact amount of money (1 ≤ moneyi ≤ 10,000) that he will need to spend each day over the next N (1 ≤ N ≤ 100,000) days.
>
> FJ wants to create a budget for a sequential set of exactly M (1 ≤ M ≤ N) fiscal periods called "fajomonths". Each of these fajomonths contains a set of 1 or more consecutive days. Every day is contained in exactly one fajomonth.
>
> FJ's goal is to arrange the fajomonths so as to minimize the expenses of the fajomonth with the highest spending and thus determine his monthly spending limit.



## **Input**

> Line 1: Two space-separated integers: N and M
>
> Lines 2..N+1: Line i+1 contains the number of dollars Farmer John spends on the ith day



## **Output**

> Line 1: The smallest possible monthly limit Farmer John can afford to live with.



## **Sample Input**

    7 5
    100
    400
    300
    100
    500
    101
    400



## **Sample Output**

    500


## **题意**

有n个花费，现在要分成m段，使得每一段和的最大值是所有分法里面最小的。



## **思路**

对于这道题呢！我们可以换一种思路

- 我们所求出的最大段和一定大于等于当前所有的数，因为这个数一定存在于某个段中
- 如果只分一段，那么段和便是所有数的和，也同时是所有分法段和的最大值

于是，在这个区间，我们通过二分的方法判断mid作为最大段和时能否成功把所有数分区

现在要分为m区，并且m一定小于等于n

**假如在mid这个最大段和的前提下**，所有区充满都没有放置完所有的数，此时便说明mid太小，尝试增大；反之，如果在没有分足m区的时候便用完了所有的数，这属于正常情况，因为我们都保证了前面分的区处于充满状态，而可以把它们拆开凑足m区，此时，说明mid有点大，尝试缩小。

迭代完成之后的mid便是最终的答案，也就是所有分法段和最大的最小值。



## **AC代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

int data[110000];
int n,m;
bool judge(int mid) //判断当前最大段和范围内能否成功分区
{
    int now=0,count=1;
    for(int i=0; i<n; i++)
    {
        now+=data[i];
        if(now>mid) //当前段已充满，开启下一段
        {
            now=data[i];
            count++;
        }
    }
    return count<=m;    //充满的段小于m没有关系，因为我们可以把已有的段拆开
}
void binary(int low,int high)
{
    int ans=0;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(judge(mid))ans=mid,high=mid-1;
        else low=mid+1;
    }
    printf("%d\n",ans);
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        int maxx=0,sum=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d",data+i);
            maxx=max(data[i],maxx); //分别求得段和的最小值与最大值
            sum+=data[i];
        }
        binary(maxx,sum);   //在这个区间内二分
    }
    return 0;
}
```

