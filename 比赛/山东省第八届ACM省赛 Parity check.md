# Parity check

## **Description**

> Fascinated with the computer games, Gabriel even forgets to study. Now she needs to finish her homework, and there is an easy problem:
> $$
> f(n)=\begin{cases}
> 0,n=0 \\
> 1,n=1 \\
> f(n-1)+f(n-2),n≥2
> \end{cases}
> $$
> She is required to calculate f(n) mod 2 for each given n. Can you help her?



## **Input**

> Multiple test cases. Each test case is an integer n(0≤n≤) in a single line.



## **Output**

> For each test case, output the answer of f(n)mod2.



## **Example Input**

    2



## **Example Output**

    1


## **题意**

给出 `f(n)` 的递推式以及 `n` 的值，求 `f(n)%2` 的结果。



## **思路**

模 2 当然是有规律的啦，果断打表看了一下 `110` ，然后输出。



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
#define eps (1e-8)
const int mod = 1e9+7;
typedef long long LL;

char str[1100];

int get()
{
    int no=0;
    int len=strlen(str);
    for(int i=0; i<len; i++)
        no=(no*10+str[i]-'0')%3;
    return no!=0;
}

int main()
{
    while(cin>>str)
        cout<<get()<<endl;
    return 0;
}
```

