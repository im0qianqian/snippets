# Sequence

## **Description**

> Given m sequences, each contains n non-negative integer. Now we may select one number from each sequence to form a sequence with m integers. It's clear that we may get n ^ m this kind of sequences. Then we can calculate the sum of numbers in each sequence, and get n ^ m values. What we need is the smallest n sums. Could you help us?



## **Input**

> The first line is an integer T, which shows the number of test cases, and then T test cases follow. The first line of each case contains two integers m, n (0 < m <= 100, 0 < n <= 2000). The following m lines indicate the m sequence respectively. No integer in the sequence is greater than 10000.



## **Output**

> For each test case, print a line with the smallest n sums in increasing order, which is separated by a space.



## **Sample Input**

    1
    2 3
    1 2 3
    2 2 3



## **Sample Output**

    3 3 4



## **题意**

给出m组数，每组n个，求从每一组挑选出一个数相加产生前n小的和。



## **思路**

假设只有一组数，那么前n小的和便是这组的所有元素，如果增加一组数之后，只有原来组的前n小的和才会对新组产生贡献（因为其他数相加产生的和一定不会是结果所说的前n个里面的），于是用一个二重循环来枚举计算添加完这一组之后的前n小的和。



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
#include<map>

typedef __int64 LL;

int num[2001];
priority_queue<int,vector<int>,greater<int> >d; //小顶堆
priority_queue<int>q;       //大顶堆

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int m,n,x;
        scanf("%d%d",&m,&n);
        for(int i=0; i<n; i++)
        {
            scanf("%d",&x);
            d.push(x);      //首先当只有一组的时候
        }
        for(int i=1; i<m; i++)  //添加剩下的组
        {
            for(int j=0; j<n; j++)
                scanf("%d",num+j);
            while(!d.empty())
            {
                x=d.top();
                d.pop();
                for(int j=0; j<n; j++)  //二重循环计算
                {
                    if((int)q.size()<n)
                        q.push(x+num[j]);
                    else if(x+num[j]<q.top())
                    {
                        q.pop();
                        q.push(x+num[j]);
                    }
                }
            }
            while(!q.empty())
            {
                d.push(q.top());
                q.pop();
            }
        }
        printf("%d",d.top());
        d.pop();
        while(!d.empty())
        {
            printf(" %d",d.top());
            d.pop();
        }
        printf("\n");
    }
    return 0;
}
```

