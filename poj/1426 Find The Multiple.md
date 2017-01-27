# Find The Multiple

## **Description**

> Given a positive integer n, write a program to find out a nonzero multiple m of n whose decimal representation contains only the digits 0 and 1. You may assume that n is not greater than 200 and there is a corresponding m containing no more than 100 decimal digits.



## **Input**

> The input file may contain multiple test cases. Each line contains a value of n (1 <= n <= 200). A line containing a zero terminates the input.



## **Output**

> For each value of n in the input print a line containing the corresponding value of m. The decimal representation of m must not contain more than 100 digits. If there are multiple solutions for a given value of n, any one of them is acceptable.



## **Sample Input**

    2
    6
    19
    0



## **Sample Output**

    10
    100100100100100100
    111111111111111111


## **题意**

求任意一个数是n的倍数，且该数的每一位只能是0或1。



## **思路**

利用bfs，从最低的1开始枚举，对于每一位的两种情况进行判断，合理即输出。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<queue>
#include<math.h>
using namespace std;
typedef __int64 LL;

LL bfs(LL n)
{
    queue<LL>sk;
    sk.push(1);
    while(!sk.empty())
    {
        LL s=sk.front();
        sk.pop();
        if(s%n==0)return s;
        sk.push(s*10);
        sk.push(s*10+1);
    }
    return 0;
}
int main()
{
    LL n;
    while(~scanf("%I64d",&n)&&n)
        printf("%I64d\n",bfs(n));
}
```

