# BestCoder Sequence

## **Problem Description**

> Mr Potato is a coder.
>
> Mr Potato is the BestCoder.
>
> One night, an amazing sequence appeared in his dream. Length of this sequence is odd, the median number is M, and he named this sequence as Bestcoder Sequence.
>
> As the best coder, Mr potato has strong curiosity, he wonder the number of consecutive sub-sequences which are bestcoder sequences in a given permutation of 1 ~ N.



## **Input**

> Input contains multiple test cases. 
>
> For each test case, there is a pair of integers N and M in the first line, and an permutation of 1 ~ N in the second line.
>
> [Technical Specification]
>
> 1. 1 <= N <= 40000
> 2. 1 <= M <= N



## **Output**

> For each case, you should output the number of consecutive sub-sequences which are the Bestcoder Sequences. 



## **Sample Input**

    1 1
    1
    5 3
    4 5 3 2 1



## **Sample Output**

    1
    3



## **题意**

给出一个数列，中位数为m，问在这个数列中能找到多少个子连续数列满足中位数为m，且长度为奇数。



## **思路**

我们可以先找到m这个位置，然后向右扩展，如果遇到的数大于m，`l++`，否则`l--`，用`hashh`数组来存储出现 `l` 这种情况的次数。

然后从m向左扩展，同样的`l++ l--`，如果 `hashh[MAXX-l]` 有值，也就是匹配到了之前向右扩展的情况，于是 `ans+=hashh[MAXX-l]` ，因为m一定在这个数列里面，所以初始时 `hashh[MAXX]=1` 。

给数组下标 `+MAXX` 是因为l的值可能为负数。



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

#define MAXX 41000
int a[MAXX],hashh[MAXX<<1];
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int k=0,ans=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d",a+i);
            if(a[i]==m)k=i;
        }
        memset(hashh,0,sizeof(hashh));
        hashh[MAXX]=1;
        for(int i=k+1,l=0; i<n; i++)
        {
            if(a[i]<m)l--;
            else l++;
            hashh[MAXX+l]++;
        }
        ans+=hashh[MAXX];
        for(int i=k-1,l=0; i>=0; i--)
        {
            if(a[i]<m)l--;
            else l++;
            if(hashh[MAXX-l])
                ans+=hashh[MAXX-l];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

