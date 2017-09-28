# B. Preparing for Merge Sort

## **Description**

> Ivan has an array consisting of n different integers. He decided to reorder all elements in increasing order. Ivan loves merge sort so he decided to represent his array with one or several increasing sequences which he then plans to merge into one sorted array.
>
> Ivan represent his array with increasing sequences with help of the following algorithm.
>
> While there is at least one unused number in array Ivan repeats the following procedure:
>
> iterate through array from the left to the right;
>
> Ivan only looks at unused numbers on current iteration;
>
> if current number is the first unused number on this iteration or this number is greater than previous unused number on current iteration, then Ivan marks the number as used and writes it down.
>
> For example, if Ivan's array looks like [1, 3, 2, 5, 4] then he will perform two iterations. On first iteration Ivan will use and write numbers [1, 3, 5], and on second one — [2, 4].
>
> Write a program which helps Ivan and finds representation of the given array with one or several increasing sequences in accordance with algorithm described above.



## **Input**

> The first line contains a single integer n (1 ≤ n ≤ 2·10^5) — the number of elements in Ivan's array.
>
> The second line contains a sequence consisting of distinct integers a1, a2, ..., an (1 ≤ ai ≤ 10^9) — Ivan's array.



## **Output**

> Print representation of the given array in the form of one or more increasing sequences in accordance with the algorithm described above. Each sequence must be printed on a new line.



## **Examples input**

    5
    1 3 2 5 4



## **Examples output**

    1 3 5 
    2 4 



## **题意**

找出所有不重叠不下降的子序列。



## **思路**

有一种暴力的想法：我们可以在 $O(n)$ 的时间复杂度找出当前数组中的一个不下降子序列，然后从数组中删掉这部分继续重复刚才的操作。

不过这佯的方法时间复杂度为 $O(n^2)$ ，显然会超时。

---

考虑用队列来存储所有不重叠不下降的子序列，对于已拓展出的 $len$ 个队列，显然其尾部数字的大小是按降序排列的。

比如我们有 $5,4,3,2,1,6,8,7,5$ 这些数字，其在队列中的存储如下：


    5,6,8
    4,7
    3,5
    2
    1


此时由所有队列尾部组成的序列为 $8,7,5,2,1$ ，对于即将加入的新数字 $x$ ，如果在已有队列尾部可以找到一个编号最小且尾部小于等于 $x$ 的索引，那么我们可以将 $x$ 加入到该队列尾部，否则用它来拓展一个新队列。

查找采用二分总时间复杂度为 $O(n \times \log n)$ 



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
typedef __int64 LL;

LL a[maxn];
int n;
deque<LL> top[maxn];

int lower_update(int len,LL x)      // 找一个编号最小且队列末尾元素小于 x 的索引
{
    int low = 0,high = len;
    while(low<high)
    {
        int mid = (low+high)>>1;
        if(*top[mid].rbegin()<=x)
            high = mid;
        else
            low = mid + 1;
    }
    if(high == len)return -1;
    return high;
}

void solve()
{
    int len = 0;
    for(int i=0; i<n; i++)
    {
        int res = lower_update(len,a[i]);   // 二分查找
        if(res == -1)                       // 没找到说明当前元素的值偏小
            top[len++].push_back(a[i]);
        else
            top[res].push_back(a[i]);
    }
    for(int i=0; i<len; i++)
    {
        cout<<top[i].front();
        top[i].pop_front();
        while(!top[i].empty())
        {
            cout<<" "<<top[i].front();
            top[i].pop_front();
        }
        cout<<endl;
    }
}

int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>a[i];
    solve();
    return 0;
}
```

