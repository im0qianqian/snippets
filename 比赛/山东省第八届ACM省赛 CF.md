# CF

## **Problem Description**

> LYD loves codeforces since there are many Russian contests. In an contest lasting for T minutes there are n problems, and for the ith problem you can get ai−di∗ti points, where ai indicates the initial points, di indicates the points decreased per minute (count from the beginning of the contest), and ti stands for the passed minutes when you solved the problem (count from the begining of the contest).
>
> Now you know LYD can solve the ith problem in ci minutes. He can't perform as a multi-core processor, so he can think of only one problem at a moment. Can you help him get as many points as he can?



## **Input**

> The first line contains two integers n,T(0≤n≤2000,0≤T≤5000).
>
> The second line contains n integers a1,a2,..,an(0<ai≤6000).
>
> The third line contains n integers d1,d2,..,dn(0<di≤50).
>
> The forth line contains n integers c1,c2,..,cn(0<ci≤400).



## **Output**

> Output an integer in a single line, indicating the maximum points LYD can get.



## **Example Input**

    3 10
    100 200 250
    5 6 7
    2 4 10



## **Example Output**

    254



## **题意**

有 $n$ 道题目，每一道题都有一个初始分值 $a_i$ ，每个单位时间这道题的分数便会减少 $d_i$ ，而我们可以在 $c_i$ 时间内做出这道题而得到分数，求在时间 $T$ 内最多可以获得的分数。



## **思路**

假设每道题做出所需要的时间都为 $t$ ，那么我们一定会选择单位时间内消耗最快的题目开始做，因为这样才能保证总的分数不会减少太快。

假设每道题目不自动消耗分数，那么我们一定会选择题目越快做出越好。

于是，综合以上两种因素得出的公式便是 $f_i=\frac{d_i}{c_i}$ ，根据它排序以后便是裸的01背包啦~



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

struct node
{
    int a;
    int d;
    int c;
    double f;
} a[5100];

bool cmp(const node &a,const node &b)
{
    return a.f>b.f;
}
int dp[5100];
int main()
{
    int n,T;
    while(~scanf("%d%d",&n,&T))
    {
        memset(dp,0,sizeof(dp));
        for(int i=0; i<n; i++)
            scanf("%d",&a[i].a);
        for(int i=0; i<n; i++)
            scanf("%d",&a[i].d);
        for(int i=0; i<n; i++)
        {
            scanf("%d",&a[i].c);
            a[i].f=(double)a[i].d/a[i].c;
        }
        sort(a,a+n,cmp);
        int maxx=0;
        for(int i=0; i<n; i++)
            for(int j=T; j>=a[i].c; j--)
            {
                dp[j]=max(dp[j],dp[j-a[i].c]+a[i].a-a[i].d*j);
                maxx=max(dp[j],maxx);
            }
        printf("%d\n",maxx);
    }
    return 0;
}
```

