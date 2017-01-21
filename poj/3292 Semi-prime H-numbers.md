# Semi-prime H-numbers

## **Description**

> This problem is based on an exercise of David Hilbert, who pedagogically suggested that one study the theory of *4n+1* numbers. Here, we do only a bit of that. 
>
> An **H**-number is a positive number which is one more than a multiple of four: 1, 5, 9, 13, 17, 21,... are the **H**-numbers. For this problem we pretend that these are the *only* numbers. The **H**-numbers are closed under multiplication. 
>
> As with regular integers, we partition the **H**-numbers into units, **H**-primes, and **H**-composites. 1 is the only unit. An **H**-number *h* is **H**-prime if it is not the unit, and is the product of two **H**-numbers in only one way: 1 × *h*. The rest of the numbers are **H**-composite. 
>
> For examples, the first few **H**-composites are: 5 × 5 = 25, 5 × 9 = 45, 5 × 13 = 65, 9 × 9 = 81, 5 × 17 = 85. 
>
> Your task is to count the number of **H**-semi-primes. An **H**-semi-prime is an **H**-number which is the product of exactly two **H**-primes. The two **H**-primes may be equal or different. In the example above, all five numbers are **H**-semi-primes. 125 = 5 × 5 × 5 is not an **H**-semi-prime, because it's the product of three **H**-primes. 



## **Input**

> Each line of input contains an **H**-number ≤ 1,000,001. The last line of input contains 0 and this line should not be processed. 



## **Output**

> For each inputted **H**-number *h*, print a line stating *h* and the number of **H**-semi-primes between 1 and *h* inclusive, separated by one space in the format shown in the sample. 



## **Sample Input**

    21 
    85
    789
    0



## **Sample Output**

    21 0
    85 5
    789 62



## **题意**

一个H-number是所有的模四余一的数。

如果一个H-number是H-primes当且仅当它的因数只有1和它本身（除1外）。

一个H-number是H-semi-prime当且仅当它只由两个H-primes的乘积表示，其余数均为H-composite。

H-number剩下其他的数均为H-composite。

给你一个数h,问1到h有多少个H-semi-prime数。



## **思路**

类似于素数筛法，把所有H-semi-prime打表筛出，然后统计区间个数之后直接输出。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define MAXX 1100000
int isprime[MAXX];
int num[MAXX];
void init() //筛法打表
{
    memset(isprime,0,sizeof(isprime));
    for(int i=5; i<MAXX; i+=4)  //遍历所有的H-number
        for(int j=5; j<MAXX; j+=4)
        {
            if(i*j>MAXX)break;  //超出最大范围
            if(isprime[i]==0&&isprime[j]==0)    //如果i,j都是H-prime
                isprime[i*j]=1;     //那么i*j是H-semi-primes
            else isprime[i*j]=-1;   //否则i*j是H-composite
        }
    int count=0;
    for(int i=1; i<MAXX; i++)
    {
        if(isprime[i]==1)count++;
        num[i]=count;
    }
}
int main()
{
    init();
    int a;
    while(~scanf("%d",&a)&&a)
        printf("%d %d\n",a,num[a]);
    return 0;
}
```

