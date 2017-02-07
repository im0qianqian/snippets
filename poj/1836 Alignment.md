# Alignment

## **Description**

> In the army, a platoon is composed by n soldiers. During the morning inspection, the soldiers are aligned in a straight line in front of the captain. The captain is not satisfied with the way his soldiers are aligned; it is true that the soldiers are aligned in order by their code number: 1 , 2 , 3 , . . . , n , but they are not aligned by their height. The captain asks some soldiers to get out of the line, as the soldiers that remain in the line, without changing their places, but getting closer, to form a new line, where each soldier can see by looking lengthwise the line at least one of the line's extremity (left or right). A soldier see an extremity if there isn't any soldiers with a higher or equal height than his height between him and that extremity. 
>
> Write a program that, knowing the height of each soldier, determines the minimum number of soldiers which have to get out of line. 



## **Input**

> On the first line of the input is written the number of the soldiers n. On the second line is written a series of n floating numbers with at most 5 digits precision and separated by a space character. The k-th number from this line represents the height of the soldier who has the code k (1 <= k <= n). 
>
> There are some restrictions: 
>
> - 2 <= n <= 1000 
> - the height are floating numbers from the interval [0.5, 2.5] 



## **Output**

> The only line of output will contain the number of the soldiers who have to get out of the line.



## **Sample Input**

    8
    1.86 1.86 1.30621 2 1.4 1 1.97 2.2



## **Sample Output**

    4



## **题意**

求删除最少的数，使得序列中任取一个 a[i]，使得有 a[0]~a[i] 严格递增，a[i]~a[n-1]严格递减。



## **思路**

首先对于原序列正向、逆向求LIS，然后枚举左边递增序列右端点与右边递减序列左端点，求得该序列的最长递增递减子序列长度，需要删除的数的个数即是剩余的数的个数。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<vector>
#include<queue>

double a[1005];
int prev[1005],next[1005];

int lis(int n)
{
    int ans=0;
    prev[0]=next[n-1]=1;
    for(int i=1; i<n; i++)
    {
        prev[i]=1;
        for(int j=0; j<i; j++)
            if(a[i]>a[j])
                prev[i]=max(prev[i],prev[j]+1);
    }
    for(int i=n-2; i>=0; i--)
    {
        next[i]=1;
        for(int j=n-1; j>i; j--)
            if(a[j]<a[i])
                next[i]=max(next[i],next[j]+1);
    }
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            ans=max(ans,prev[i]+next[j]);
    return ans;
}

int main()
{
    int n;
    while(cin>>n)
    {
        for(int i=0; i<n; i++)
            cin>>a[i];
        cout<<n-lis(n)<<endl;
    }
    return 0;
}
```

