# Prime Path

## **Description**

> The ministers of the cabinet were quite upset by the message from the Chief of Security stating that they would all have to change the four-digit room numbers on their offices. 
>
> — It is a matter of security to change such things every now and then, to keep the enemy in the dark. 
>
> — But look, I have chosen my number 1033 for good reasons. I am the Prime minister, you know! 
>
> — I know, so therefore your new number 8179 is also a prime. You will just have to paste four new digits over the four old ones on your office door. 
>
> — No, it’s not that simple. Suppose that I change the first digit to an 8, then the number will read 8033 which is not a prime! 
>
> — I see, being the prime minister you cannot stand having a non-prime number on your door even for a few seconds. 
>
> — Correct! So I must invent a scheme for going from 1033 to 8179 by a path of prime numbers where only one digit is changed from one prime to the next prime. 
>
> Now, the minister of finance, who had been eavesdropping, intervened. 
>
> — No unnecessary expenditure, please! I happen to know that the price of a digit is one pound. 
>
> — Hmm, in that case I need a computer program to minimize the cost. You don't know some very cheap software gurus, do you? 
>
> — In fact, I do. You see, there is this programming contest going on... Help the prime minister to find the cheapest prime path between any two given four-digit primes! The first digit must be nonzero, of course. Here is a solution in the case above. 
>
> ```
> 1033
> 1733
> 3733
> 3739
> 3779
> 8779
> 8179
> ```
>
> The cost of this solution is 6 pounds. Note that the digit 1 which got pasted over in step 2 can not be reused in the last step – a new 1 must be purchased.



## **Input**

> One line with a positive number: the number of test cases (at most 100). Then for each test case, one line with two numbers separated by a blank. Both numbers are four-digit primes (without leading zeros).



## **Output**

> One line for each case, either with a number stating the minimal cost or containing the word Impossible.



## **Sample Input**

    3
    1033 8179
    1373 8017
    1033 1033



## **Sample Output**

    6
    7
    0


## **题意**

给你n,m分别是素数，求由n到m变化的步骤数，规定每一步只能改变个十百千一位的数（千位不能为零），且变化得到的每一个数也为素数。



## **思路**

首先进行素数打表，打出10000以内的所有素数（或者1000-10000），然后bfs。

对n变化个十百千的每一位，变化后检测是否为素数，若是，加入队列，同时标记已访问，然后对队列中的数进行同样的操作，直到某一次变化产生m，输出最少的变换次数。

若不可能达到m，则会在遍历完[1000-9999]之间所有素数后退出。



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

#define Max 10000
int prime[Max];
bool isvis[Max];    //已经访问过的数字不需要重新加入队列
void IsPrime()      //素数打表
{
    prime[0]=prime[1]=0;
    prime[2]=1;
    for(int i=3; i<Max; i++)
        prime[i]=i%2==0?0:1;
    int t=(int)sqrt(Max*1.0);
    for(int i=3; i<=t; i++)
        if(prime[i])
            for(int j=i*i; j<Max; j+=2*i) //优化
                prime[j]=0;
}
struct point
{
    int data;
    int time;   //当前进行到第几步
    point(int data,int time)
    {
        this->data=data;
        this->time=time;
    }
};
int solve(point a,int b)
{
    memset(isvis,false,sizeof(isvis));
    queue<point>sk;
    sk.push(a);
    while(!sk.empty())
    {
        point p=sk.front();
        sk.pop();
        if(p.data==b)return p.time;
        isvis[p.data]=true;
        for(int i=10; i<=10000; i*=10)  //从低到高枚举
        {
            for(int j=(i==10000)?1:0; j<=9; j++)    //最高位不能是0
            {
                int num=p.data/i*i+i/10*j+p.data%(i/10);    //计算当前的数字
                if(!isvis[num]&&prime[num])
                    sk.push(point(num,p.time+1));
            }
        }
    }
    return -1;
}

int main()
{
    IsPrime();
    int n;
    while(~scanf("%d",&n))
    {
        int a,b;
        for(int i=0; i<n; i++)
        {
            scanf("%d%d",&a,&b);
            int ans=solve(point(a,0),b);
            printf(ans==-1?"Impossible\n":"%d\n",ans);
        }
    }
    return 0;
}
```

