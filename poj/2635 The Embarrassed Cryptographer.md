# The Embarrassed Cryptographer

## Description

> The young and very promising cryptographer Odd Even has implemented the security module of a large system with thousands of users, which is now in use in his company. The cryptographic keys are created from the product of two primes, and are believed to be secure because there is no known method for factoring such a product effectively. 
>
> What Odd Even did not think of, was that both factors in a key should be large, not just their product. It is now possible that some of the users of the system have weak keys. In a desperate attempt not to be fired, Odd Even secretly goes through all the users keys, to check if they are strong enough. He uses his very poweful Atari, and is especially careful when checking his boss' key.



## Input

> The input consists of no more than 20 test cases. Each test case is a line with the integers 4 <= K <= 10100 and 2 <= L <= 106. K is the key itself, a product of two primes. L is the wanted minimum size of the factors in the key. The input set is terminated by a case where K = 0 and L = 0.



## Output

> For each number K, if one of its factors are strictly less than the required L, your program should output "BAD p", where p is the smallest factor in K. Otherwise, it should output "GOOD". Cases should be separated by a line-break.



## Sample Input

    143 10
    143 20
    667 20
    667 30
    2573 30
    2573 40
    0 0



## Sample Output

    GOOD
    BAD 11
    GOOD
    BAD 23
    GOOD
    BAD 31



## 题意

已知K是两个素数的乘积，判断这两个素数中最小的一个是否小于L，若小于，输出`BAD + MIN_PRIME`，否则输出`GOOD`。



## 思路

同余定理中有这么几条定律

$(a+b)\%c=(a\%c+b\%c)\%c$

$(a*b)\%c=(a\%c*b\%c)\%c$

例如要验证123是否被3整除，只需求 $123\%3$ ，判断是否等于0。

但是，当123是一个大数时，我们不能直接对它进行模运算，只能通过同余定理对大数进行分块，然后间接运算。

**具体的做法：**

**先求** $1\%3=1$

**再求** $(1*10+2)\%3=0$

**再求** $(0*10+3)\%3=0$

于是便间接得到了 $123\%3=0$ ，每一次运算中乘号的前面都是上一次运算的结果。



题目中有说明K的范围是 $[4,10^{100}]$ ，打表出的素数个数大概有8w，本来分析的用十进制应该不会超时，但是提交之后发现果然超时了。无奈只能百度看到别人用的千进制存储，于是我也试了一下，AC~

用千进制存储主要是为了减少循环的次数，可以把原数长度缩短3倍，毕竟 $1000=10^3$ 



## AC代码

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;

const int Range = 1e6+100;
int prime[Range+1];
int kt[110];  //千进制存储的k
int l;
void init() //素数打表
{
    int pNum=0;
    prime[pNum++]=2;

    for(int i=3; i<=Range; i+=2) //奇偶法
    {
        bool flag=true;
        for(int j=0; prime[j]*prime[j]<=i; j++) //根号法+递归法
            if(!(i%prime[j]))
            {
                flag=false;
                break;
            }
        if(flag)prime[pNum++]=i;
    }
    return;
}

bool mod(int *k,int p,int len)  //判断高精度k是否可以整除p
{
    int s=0;
    for(int i=len-1; i>=0; i--) //同余模定理
        s=(s*1000+k[i])%p;
    return s==0;
}

int main()
{
    init();
    char k[110];
    while(~scanf("%s%d",k,&l)&&l)
    {
        memset(kt,0,sizeof(kt));
        int len=strlen(k);
        for(int i=0; i<len; i++)    //十进制与千进制差1e3，因此在转换的时候直接每三位作为千进制的一位
        {
            int pkt=(len+2-i)/3-1;  //+2是为了在/3的时候保证上取整
            kt[pkt]=kt[pkt]*10+(k[i]-'0');
        }
        int lent=(len+2)/3; //千进制数的位数
        bool flag=true;
        int pmin=0;
        while(prime[pmin]<l)
        {
            if(mod(kt,prime[pmin],lent))
            {
                flag=false;
                printf("BAD %d\n",prime[pmin]);
                break;
            }
            pmin++;
        }
        if(flag)printf("GOOD\n");
    }
    return 0;
}
```

