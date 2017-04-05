# Team Formation

## **Description**

> For an upcoming programming contest, Edward, the headmaster of Marjar University, is forming a two-man team from N students of his university.
>
> Edward knows the skill level of each student. He has found that if two students with skill level A and B form a team, the skill level of the team will be A ⊕ B, where ⊕ means bitwise exclusive or. A team will play well if and only if the skill level of the team is greater than the skill level of each team member (i.e. A ⊕ B > max{A, B}).
>
> Edward wants to form a team that will play well in the contest. Please tell him the possible number of such teams. Two teams are considered different if there is at least one different team member.



## **Input**

> There are multiple test cases. The first line of input contains an integer T indicating the number of test cases. For each test case:
>
> The first line contains an integer N (2 <= N <= 100000), which indicates the number of student. The next line contains N positive integers separated by spaces. The ith integer denotes the skill level of ith student. Every integer will not exceed 109.



## **Output**

> For each case, print the answer in one line.



## **Sample Input**

    2
    3
    1 2 3
    5
    1 2 3 4 5



## **Sample Output**

    1
    6



## **题意**

找出一些数中可以找多少组两个数，满足这两个数异或的结果大于其中任意一个数。



## **思路**

一个数A，想要异或之后比原数大，我们可以找一个比它小的数B，并且B的二进制最高位所对应A的相应位为0。

对于输入的所有数，我们可以统计其二进制最高位在第k位的出现次数。

然后枚举所有的数字，对每一个数字二进制中有效的零，看是否有统计中存在最高位为当前位的数，若有， `sum+=b[t]` 



## **AC 代码**

```cpp
#include <iostream>
#include <cstdio>
#include<cmath>
#include <algorithm>
#include<cstring>
using namespace std;
int a[100100],b[40];

int maxbit(int n)
{
    int t = 0;
    while(n)
    {
        t++;
        n>>=1;
    }
    return t;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int sum = 0,n;
        scanf("%d",&n);
        memset(b,0,sizeof(b));
        for(int i=0; i<n; i++)
        {
            scanf("%d",a+i);
            b[maxbit(a[i])]++;
        }
        for(int i=0; i<n; i++)
        {
            int t = 1;
            while(a[i])
            {
                if(a[i]%2==0) sum += b[t];
                a[i] >>= 1;
                t++;
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
```

