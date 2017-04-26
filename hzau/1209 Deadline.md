# Deadline

## **Description**

> There are N bugs to be repaired and some engineers whose abilities are roughly equal. And an engineer can repair a bug per day. Each bug has a deadline A[i].
>
> Question: How many engineers can repair all bugs before those deadlines at least?
>
> 1<=n<= 1e6. 1<=a[i] <=1e9



## **Input Description**

> There are multiply test cases.
>
> In each case, the first line is an integer N , indicates the number of bugs.
>
> The next line is n integers indicates the deadlines of those bugs.



## **Output Description**

> There are one number indicates the answer to the question in a line for each case.



## **Input**

    4
    1 2 3 4



## **Output**

    1



## **题意**

程序员一天可以修改一个 `bug` ，现在给你一些 `bug` 以及其修复期限，问最少需要多少个程序员才可以完成任务。



## **思路**

首先因为 $n$ 的范围是 $[1,10^6]$ ，也就是最多有 $10^6$ 个 `bug` 。

假如每一个 `bug` 找一个程序员来改，那么总共最多有 $10^6$ 个程序员使用一天的时间完成所有任务，所以修复期限在 $10^6$ 以上的 `bug` 我们不用考虑，因为它总能被修复。

对于前 $i$ 天需要修复的 `bug` ，我们把它在 $i$ 天内平均分配给的人数至少是 $(sum-1)/i+1$ ，也就是 $\lceil sum/i\rceil$ ，然后找最大的值即可。



## **AC 代码**

```cpp
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int a[1000009];
const int maxn = 1e6;
int main()
{
    int n,b;
    while(~scanf("%d",&n))
    {
        memset(a,0,sizeof(a));
        for(int i=1; i<=n; i++)
        {
            scanf("%d",&b);
            if(b<=maxn)a[b]++;
        }
        int sum=0,ans=1;
        for(int i=1; i<=maxn; i++)
        {
            sum+=a[i];
            int t=((sum-1)/i+1);
            ans=max(ans,t);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

