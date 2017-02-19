# Asteroids

## **Description**

> Bessie wants to navigate her spaceship through a dangerous asteroid field in the shape of an N x N grid (1 <= N <= 500). The grid contains K asteroids (1 <= K <= 10,000), which are conveniently located at the lattice points of the grid. 
>
> Fortunately, Bessie has a powerful weapon that can vaporize all the asteroids in any given row or column of the grid with a single shot.This weapon is quite expensive, so she wishes to use it sparingly.Given the location of all the asteroids in the field, find the minimum number of shots Bessie needs to fire to eliminate all of the asteroids.



## **Input**

> - Line 1: Two integers N and K, separated by a single space. 
> - Lines 2..K+1: Each line contains two space-separated integers R and C (1 <= R, C <= N) denoting the row and column coordinates of an asteroid, respectively.
>   Output
> - Line 1: The integer representing the minimum number of times Bessie must shoot.



## **Sample Input**

    3 4
    1 1
    1 3
    2 2
    3 2



## **Sample Output**

    2



## **题意**

给出所有障碍物的坐标，每一次可以消灭一行或者一列，问最少需要几次才可以消灭完所有的障碍物。



## **思路**

看过别人的博客才知道这种建图的方法，要是我会想到么？

把行 $x$ 看成二分图的一个集合，列 $y$ 看作二分图的另一个集合，然后某一点 $(x,y)$ ，便是从图的左边连向右边的一条边。

于是二分图的每一条边便是一个障碍物，而我们现在要做的是找到需要安置炸弹的行与列，在二分图中便是两个集合的相应点。

呐，最小点覆盖问题。

因为二分图的最大匹配数等于最小点覆盖数目，于是便可以用匈牙利算法解决咯！



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stack>
#define inf (1<<25)
using namespace std;

const int MAXN=510;
int uN,vN;//u,v数目
int g[MAXN][MAXN];
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)//从左边开始找增广路径
{
    int v;
    for(v=0; v<vN; v++) //这个顶点编号从0开始，若要从1开始需要修改
        if(g[u][v]&&!used[v])
        {
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v]))
            {
                //找增广路，反向
                linker[v]=u;
                return true;
            }
        }
    return false;//这个不要忘了，经常忘记这句
}
int hungary()
{
    int res=0;
    int u;
    memset(linker,-1,sizeof(linker));
    for(u=0; u<uN; u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}
int main()
{
    int k;
    while(~scanf("%d%d",&uN,&k))
    {
        int r,c;
        memset(g,0,sizeof(g));
        vN=uN;
        for(int i=0; i<k; i++)
        {
            scanf("%d%d",&r,&c);
            g[r-1][c-1]=1;
        }
        printf("%d\n",hungary());
    }
    return 0;
}
```

