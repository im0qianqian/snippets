# quadratic equation

## **Problem Description**

> With given integers a,b,c, you are asked to judge whether the following statement is true: "For any x, if $a⋅x^2+b⋅x^2+c=0$ , then x is an integer."



## **Input**

> The first line contains only one integer T(1≤T≤2000), which indicates the number of test cases.
>
> For each test case, there is only one line containing three integers a,b,c(−5≤a,b,c≤5).



## **Output**

> or each test case, output “YES” if the statement is true, or “NO” if not.



## **Example Input**

    3
    1 4 4
    0 0 1
    1 3 1



## **Example Output**

    YES
    YES
    NO



## **题意**

给出 `a,b,c` ，判断 $a⋅x^2+b⋅x^2+c=0$ 是否有非整数解，若有，输出 `NO` ，否则输出 `YES` 。



## **思路**

从测试数据可以看出如果原方程式无实数解时输出 `YES` 。

于是便是很多很多的 `if` 啦！

**注意：这题有坑、这题有坑、这题有坑，如果 a,b,c 都是 0 的情况 x 可以取任意实数，所以输出 NO**

如果没有这个坑，可能省赛的时候就是稳金了，忧伤~



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

bool jud(int a,int b,int c)
{
    if(a==0)
    {
        if(b==0)
        {
            if(c==0)return false;   // 已心痛的坑
            return true;
        }
        else if(c%b==0)return true;
        return false;
    }
    double der=b*b-4*a*c;
    int s=(int)sqrt(der);
    if(der<0)return true;
    if(fabs(s-sqrt(der))<eps)
        if((-b+s)%(2*a)==0&&(-b-s)%(2*a)==0)return true;
    return false;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int i=0; i<T; i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        printf(jud(a,b,c)?"YES\n":"NO\n");
    }
    return 0;
}
```

