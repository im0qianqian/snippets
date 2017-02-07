# Cash Machine

## **Description**

> A Bank plans to install a machine for cash withdrawal. The machine is able to deliver appropriate @ bills for a requested cash amount. The machine uses exactly N distinct bill denominations, say Dk, k=1,N, and for each denomination Dk the machine has a supply of nk bills. For example, 
>
> N=3, n1=10, D1=100, n2=4, D2=50, n3=5, D3=10 
>
> means the machine has a supply of 10 bills of @100 each, 4 bills of @50 each, and 5 bills of @10 each. 
>
> Call cash the requested amount of cash the machine should deliver and write a program that computes the maximum amount of cash less than or equal to cash that can be effectively delivered according to the available bill supply of the machine. 
>
> Notes: 
>
> @ is the symbol of the currency delivered by the machine. For instance, @ may stand for dollar, euro, pound etc. 



## **Input**

> The program input is from standard input. Each data set in the input stands for a particular transaction and has the format: 
>
> cash N n1 D1 n2 D2 ... nN DN 
>
> where 0 <= cash <= 100000 is the amount of cash requested, 0 <=N <= 10 is the number of bill denominations and 0 <= nk <= 1000 is the number of available bills for the Dk denomination, 1 <= Dk <= 1000, k=1,N. White spaces can occur freely between the numbers in the input. The input data are correct. 



## **Output**

> For each set of data the program prints the result to the standard output on a separate line as shown in the examples below. 



## **Sample Input**

    735 3  4 125  6 5  3 350
    633 4  500 30  6 100  1 5  0 1
    735 0
    0 3  10 100  10 50  10 10



## **Sample Output**

    735
    630
    0
    0


## **题意**

一个取款机有`N`种钞票，每种钞票有`nk`张，面额为`Dk`，给定一个取款金额`cash`，可行的、不超过该金额的吐钞方案最大是多少钱？



## **思路**

多重背包模版题目，具体查看 [背包九讲](http://love-oriented.com/pack/Index.html) 。

代码中加入了二进制优化。



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
#define MAXX 110000
int p[MAXX],h[MAXX],c[MAXX];
int dp[MAXX];
void solve(int pi,int hi,int n)
{
    for(int i=n; i>=pi; i--)
        dp[i]=max(dp[i],dp[i-pi]+hi);
}
void mult(int pi,int hi,int ci,int n)
{
    int k=1;
    while(k<=ci)
    {
        solve(k*pi,k*hi,n);
        ci-=k;
        k<<=1;
    }
    solve(ci*pi,ci*hi,n);
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0; i<m; i++)
            scanf("%d%d",c+i,p+i);
        memset(dp,0,sizeof(dp));
        for(int i=0; i<m; i++)
            mult(p[i],p[i],c[i],n);
        printf("%d\n",dp[n]);
    }
    return 0;
}
```

