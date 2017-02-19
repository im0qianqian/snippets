# Ultra-QuickSort

## **Description**

> In this problem, you have to analyze a particular sorting algorithm. The algorithm processes a sequence of n distinct integers by swapping two adjacent sequence elements until the sequence is sorted in ascending order. For the input sequence 
>
> 9 1 0 5 4 ,
>
> Ultra-QuickSort produces the output 
>
> 0 1 4 5 9 .
>
> Your task is to determine how many swap operations Ultra-QuickSort needs to perform in order to sort a given input sequence.



## **Input**

> The input contains several test cases. Every test case begins with a line that contains a single integer n < 500,000 -- the length of the input sequence. Each of the the following n lines contains a single integer 0 ≤ a[i] ≤ 999,999,999, the i-th input sequence element. Input is terminated by a sequence of length n = 0. This sequence must not be processed.



## **Output**

> For every input sequence, your program prints a single line containing an integer number op, the minimum number of swap operations necessary to sort the given input sequence.



## **Sample Input**

    5
    9
    1
    0
    5
    4
    3
    1
    2
    3
    0



## **Sample Output**

    6
    0


## **题意**

求把一个序列排序所需要的最小相邻交换次数。



## **思路**

题目可以转化为**求数组所有数字的逆序数之和**，因为n比较大的关系，所以舍弃 $O(n^2)$ 的算法，改用归并排序。

一般这样的题目都可以用归并排序来解决，或者树状数组也可以。



**假设当前归并排序的两个序列为**

1 3 4 9

2 5 7 8

分别取数3、2，3>2，说明3后面所有的数都比2大(m-p)，因为序列1一定在序列2前面，那这一个解释便是逆序数咯！

另外，当序列2全部排序完之后序列1还剩9，此时可以得到，9以及后面的所有的数都比序列2大(y-m)。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
__int64 total,n;
int A[500005],T[500005];
void merge_sort(int x,int y)
{
    if(y-x>1)
    {
        int m=x+(y-x)/2;
        int p=x,q=m,i=x;
        merge_sort(x,m);
        merge_sort(m,y);
        while(p<m&&q<y)
        {
            if(A[p]>A[q])   //说明A[p]后面的数都比A[q]大
            {
                total+=m-p;
                T[i++]=A[q++];
            }
            else
            {
                total+=q-m; //A[q]前面的都比A[p]小
                T[i++]=A[p++];
            }
        }
        while(q<y)
        {
            T[i++]=A[q++];
        }
        while(p<m)
        {
            total+=y-m;     //如果A[p]还有剩余，即剩下的都比A[q]大
            T[i++]=A[p++];
        }
        for(int j=x; j<y; j++)
            A[j]=T[j];
    }
}
int main(int argc, char *argv[])
{
    while(~scanf("%I64d",&n)&&n)
    {
        memset(A,0,sizeof(A));
        memset(T,0,sizeof(T));
        total=0;
        for(int i=0; i<n; i++)
            scanf("%d",&A[i]);
        merge_sort(0,n);
        printf("%I64d\n",total/2);  //除以2是因为计算了前面比i大，后面比i小的，也就是逆序数的二倍
    }
    return 0;
}
```

