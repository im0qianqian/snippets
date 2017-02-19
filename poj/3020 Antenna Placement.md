# Antenna Placement

## **Description**

> The Global Aerial Research Centre has been allotted the task of building the fifth generation of mobile phone nets in Sweden. The most striking reason why they got the job, is their discovery of a new, highly noise resistant, antenna. It is called 4DAir, and comes in four types. Each type can only transmit and receive signals in a direction aligned with a (slightly skewed) latitudinal and longitudinal grid, because of the interacting electromagnetic field of the earth. The four types correspond to antennas operating in the directions north, west, south, and east, respectively. Below is an example picture of places of interest, depicted by twelve small rings, and nine 4DAir antennas depicted by ellipses covering them.
>
> Obviously, it is desirable to use as few antennas as possible, but still provide coverage for each place of interest. We model the problem as follows: Let A be a rectangular matrix describing the surface of Sweden, where an entry of A either is a point of interest, which must be covered by at least one antenna, or empty space. Antennas can only be positioned at an entry in A. When an antenna is placed at row r and column c, this entry is considered covered, but also one of the neighbouring entries (c+1,r),(c,r+1),(c-1,r), or (c,r-1), is covered depending on the type chosen for this particular antenna. What is the least number of antennas for which there exists a placement in A such that all points of interest are covered?



## **Input**

> On the first row of input is a single positive integer n, specifying the number of scenarios that follow. Each scenario begins with a row containing two positive integers h and w, with 1 <= h <= 40 and 0 < w <= 10. Thereafter is a matrix presented, describing the points of interest in Sweden in the form of h lines, each containing w characters from the set ['*','o']. A '*'-character symbolises a point of interest, whereas a 'o'-character represents open space.



## **Output**

> For each scenario, output the minimum number of antennas necessary to cover all '*'-entries in the scenario's matrix, on a row of its own.



## **Sample Input**

    2
    7 9
    ooo**oooo
    **oo*ooo*
    o*oo**o**
    ooooooooo
    *******oo
    o*o*oo*oo
    *******oo
    10 1
    *
    *
    *
    o
    *
    *
    *
    *
    *
    *



## **Sample Output**

    17
    5


## **题意**

一个矩形中，有N个城市（*），现在这n个城市都要覆盖无线，若放置一个基站，那么它至多可以覆盖相邻的两个城市。

问至少需要放置多少个基站才能使得所有的城市都覆盖无线？



## **思路**

二分图的最小路径覆盖问题，即使用最少的路径覆盖二分图中的所有顶点。

地图中的城市和相邻的城市可以同时被一个基站覆盖，那么这两个城市我们可以理解为有一条无向边，或者两条有向边。

为了构造二分图，我们不可以直接使用x和y作为两个集合来构造它，因为这样构造的结果使得每一条边作为一个城市，然后相邻城市便无法表达。

把城市作为二分图的顶点可以成功构造，用两个集合之间的边来表达它们之间的相邻关系，于是需要引入一个拆点的概念，即把一个点拆成两个分别位于不同的集合。



假设城市A与B相邻，在二分图中便有A->B'，与B->A'这两条边，因为每一个集合都必须包含所有的城市。



可以想到，这个二分图一定是对称的（无向二分图），当二分图的两个顶点子集基数相等时，该二分图所有顶点的匹配数**等于**任意一个顶点子集匹配数的2倍。

**无向二分图的最小路径覆盖 = 顶点数 – 最大二分匹配数/2**

关于最大二分匹配数还是用匈牙利算法求解。



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
int mapp[MAXN][MAXN];
int mv[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};
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
int hungary()   //匈牙利算法求二分图最大匹配
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
    int T;
    char str[55];
    scanf("%d",&T);
    while(T--)
    {
        memset(mapp,-1,sizeof(mapp));
        memset(g,0,sizeof(g));
        int h,w;
        scanf("%d%d%*c",&h,&w);
        uN=0;
        for(int i=0; i<h; i++)
        {
            gets(str);
            for(int j=0; j<w; j++)
                if(str[j]=='*')mapp[i][j]=uN++;     //先给城市标号
        }
        vN=uN;
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
            {
                if(mapp[i][j]>=0)   //如果当前点是城市
                {
                    for(int k=0; k<4; k++)      //找它相邻的点
                    {
                        int x=i+mv[k][0],y=j+mv[k][1];
                        if(x<0||x>=h||j<0||j>=w||mapp[x][y]<0)continue;
                        g[mapp[i][j]][mapp[x][y]]=true;
                    }
                }
            }
        printf("%d\n",uN-hungary()/2);          //因为有了拆点所以匹配数增加了1倍
    }
    return 0;
}
```

