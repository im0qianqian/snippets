# Painter's Problem

## **Description**

> There is a square wall which is made of n×n small square bricks. Some bricks are white while some bricks are yellow. Bob is a painter and he wants to paint all the bricks yellow. But there is something wrong with Bob's brush. Once he uses this brush to paint brick (i, j), the bricks at (i, j), (i-1, j), (i+1, j), (i, j-1) and (i, j+1) all change their color. Your task is to find the minimum number of bricks Bob should paint in order to make all the bricks yellow. 
>
> ![img](http://poj.org/images/1681_1.jpg)



## **Input**

> The first line contains a single integer t (1 <= t <= 20) that indicates the number of test cases. Then follow the t cases. Each test case begins with a line contains an integer n (1 <= n <= 15), representing the size of wall. The next n lines represent the original wall. Each line contains n characters. The j-th character of the i-th line figures out the color of brick at position (i, j). We use a 'w' to express a white brick while a 'y' to express a yellow brick.



## **Output**

> For each case, output a line contains the minimum number of bricks Bob should paint. If Bob can't paint all the bricks yellow, print 'inf'.



## **Sample Input**

    2
    3
    yyy
    yyy
    yyy
    5
    wwwww
    wwwww
    wwwww
    wwwww
    wwwww



## **Sample Output**

    0
    15


## **题意**

给出一个 $n×n$ 小方砖组成的墙面，现在要为其统一涂成黄色，不过每粉刷一个小方砖都会让相邻的四个改变为相反的颜色，求最少需要多少次粉刷才可以成功。



## **思路**

考虑有 $n×n$ 个多项式，每一个多项式涉及到上下左右以及自身的五个变量，其结果为 `1` 。

然后代入高斯消元求出方程组的解，若唯一解，统计 `1` 的个数；若有无穷多个解，枚举所有的自由变元找出最优解；若无解输出 `inf` 。



## **AC 代码**

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;

typedef __int64 LL;

const int maxn = 300;

int equ,var;
int a[maxn][maxn];
int x[maxn];
int free_x[maxn];
int free_num;
int n;
int Gauss()
{
    int max_r,col,k;
    free_num=0;
    for(k=0,col=0; k<equ&&col<var; k++,col++)
    {
        max_r=k;
        for(int i=k+1; i<equ; i++)
            if(abs(a[i][col])>abs(a[max_r][col]))
                max_r=i;
        if(a[max_r][col]==0)
        {
            k--;
            free_x[free_num++]=col;
            continue;
        }
        if(max_r!=k)
            for(int j=col; j<var+1; j++)
                swap(a[k][j],a[max_r][j]);
        for(int i=k+1; i<equ; i++)
            if(a[i][col]!=0)
                for(int j=col; j<var+1; j++)
                    a[i][j]^=a[k][j];
    }
    for(int i=k; i<equ; i++)
        if(a[i][col]!=0)
            return -1;
    if(k<var)return var-k;
    for(int i=var-1; i>=0; i--)
    {
        x[i]=a[i][var];
        for(int j=i+1; j<var; j++)
            x[i]^=(a[i][j]&&x[j]);
    }
    return 0;
}

void init()
{
    memset(a,0,sizeof(a));
    memset(x,0,sizeof(x));
    equ=n*n;
    var=n*n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            int t=i*n+j;
            a[t][t]=1;
            if(i>0)a[(i-1)*n+j][t]=1;
            if(i<n-1)a[(i+1)*n+j][t]=1;
            if(j>0)a[i*n+j-1][t]=1;
            if(j<n-1)a[i*n+j+1][t]=1;
        }
}

void solve()
{
    int t=Gauss();
    if(t==-1)
        cout<<"inf"<<endl;
    else if(t==0)
    {
        int ans=0;
        for(int i=0; i<n*n; i++)
            ans+=x[i];
        cout<<ans<<endl;
    }
    else
    {
        int ans=0x3f3f3f3f;
        int tot=1<<t;
        for(int i=0; i<tot; i++)
        {
            int cnt=0;
            for(int j=0; j<t; j++)
            {
                if(i&(1<<j))
                {
                    x[free_x[j]]=1;
                    cnt++;
                }
                else x[free_x[j]]=0;
            }
            for(int j=var-t-1; j>=0; j--)
            {
                int idx;
                for(idx=j; idx<var; idx++)
                    if(a[j][idx])
                        break;
                x[idx]=a[j][var];
                for(int l=idx+1; l<var; l++)
                    if(a[j][l])
                        x[idx]^=x[l];
                cnt+=x[idx];
            }
            ans=min(ans,cnt);
        }
        cout<<ans<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        char str[30];
        cin>>n;
        init();
        for(int i=0; i<n; i++)
        {
            cin>>str;
            for(int j=0; j<n; j++)
                if(str[j]=='y')
                    a[i*n+j][n*n]=0;
                else a[i*n+j][n*n]=1;
        }
        solve();
    }
    return 0;
}
```

