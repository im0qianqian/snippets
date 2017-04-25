# Paratroopers

## **Description**

> It is year 2500 A.D. and there is a terrible war between the forces of the Earth and the Mars. Recently, the commanders of the Earth are informed by their spies that the invaders of Mars want to land some paratroopers in the m × n grid yard of one their main weapon factories in order to destroy it. In addition, the spies informed them the row and column of the places in the yard in which each paratrooper will land. Since the paratroopers are very strong and well-organized, even one of them, if survived, can complete the mission and destroy the whole factory. As a result, the defense force of the Earth must kill all of them simultaneously after their landing.
>
> In order to accomplish this task, the defense force wants to utilize some of their most hi-tech laser guns. They can install a gun on a row (resp. column) and by firing this gun all paratroopers landed in this row (resp. column) will die. The cost of installing a gun in the ith row (resp. column) of the grid yard is ri (resp. ci ) and the total cost of constructing a system firing all guns simultaneously is equal to the product of their costs. Now, your team as a high rank defense group must select the guns that can kill all paratroopers and yield minimum total cost of constructing the firing system.



## **Input**

> Input begins with a number T showing the number of test cases and then, T test cases follow. Each test case begins with a line containing three integers 1 ≤ m ≤ 50 , 1 ≤ n ≤ 50 and 1 ≤ l ≤ 500 showing the number of rows and columns of the yard and the number of paratroopers respectively. After that, a line with m positive real numbers greater or equal to 1.0 comes where the ith number is ri and then, a line with n positive real numbers greater or equal to 1.0 comes where the ith number is ci. Finally, l lines come each containing the row and column of a paratrooper.



## **Output**

> For each test case, your program must output the minimum total cost of constructing the firing system rounded to four digits after the fraction point.



## **Sample Input**

    1
    4 4 5
    2.0 7.0 5.0 2.0
    1.5 2.0 2.0 8.0
    1 1
    2 2
    3 3
    4 4
    1 4



## **Sample Output**

    16.0000



## **题意**

$n×m$ 的地图，给出 $L$ 个火星人登陆的坐标，要在火星人登陆地球的瞬间全部消灭他们，有一种激光枪，一次可以消灭一行（或一列），消灭一行（或一列）有不同的代价，总代价是所有激光枪的代价之积，求最小的总代价。



## **思路**

因为总代价是所有激光枪的代价之积，并不是之和，所以在这里我们要用点小技巧： $\log n×\log m=\log (n+m)$

**找一个源点，**它到所有 `x` 坐标的容量是相应行的代价。

**找一个汇点，**所有 `y` 坐标到它的容量是相应列的代价。

然后输入的点的坐标也就是 `x` 到 `y` 的一条边，容量为 `INF` ，此时这一条边就代表了这一个点。

想要消灭所有的点，也就是找一个最小的割边集合让源汇分离，根据最大流最小割定理，求出图的最大流即可。



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

const int MAXX = 500;
const int INF = 0x3f3f3f3f;

struct edge
{
    int to;     //边终点
    int next;   //下一个兄弟位置
    double cap;    //容量
    double flow;   //流量
    int cost;   //费用
} edge[MAXX<<2];

int head[MAXX],tol;
int pre[MAXX],dis[MAXX];
int N;  //节点总个数

double vx[55],vy[55];
double e=2.718281828459045;

void init(int n)
{
    N=n;
    tol=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,double cap,int cost)  //同时增加原边与反向边
{
    edge[tol].to=v;
    edge[tol].cap=cap;
    edge[tol].cost=cost;
    edge[tol].flow=0;
    edge[tol].next=head[u];
    head[u]=tol++;
    edge[tol].to=u;
    edge[tol].cap=0;
    edge[tol].cost=-cost;
    edge[tol].flow=0;
    edge[tol].next=head[v];
    head[v]=tol++;
}

/*
 * SPFA 算法判断是否存在s到t的通路
 */
bool spfa(int s,int t)
{
    queue<int>q;
    bool vis[MAXX];
    for(int i=0; i<N; i++)
    {
        dis[i]=INF;
        vis[i]=false;
        pre[i]=-1;
    }
    dis[s]=0;
    vis[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u]; i!=-1; i=edge[i].next)   //遍历所有与u临接的点
        {
            int v=edge[i].to;
            if(edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost)    //如果可以松弛该点
            {
                dis[v]=dis[u]+edge[i].cost;
                pre[v]=i;
                if(!vis[v]) //如果该点不在队列中，入队
                {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return (pre[t]!=-1);    //返回是否s到t是否有路径
}

/*
 * int s 起点
 * int t 终点
 */
double minCostMaxFlow(int s,int t,int &cost)
{
    double flow=0;
    while(spfa(s,t))
    {
        double minn=INF;   //当前路径可增广值
        for(int i=pre[t]; i!=-1; i=pre[edge[i^1].to])   //因为建图时每增加一条边会同时加入它的反向边，因此i^1为找出与i刚好相反的部分
        {
            if(minn>edge[i].cap-edge[i].flow)
                minn=edge[i].cap-edge[i].flow;
        }
        for(int i=pre[t]; i!=-1; i=pre[edge[i^1].to])   //修改图，计算花费
        {
            edge[i].flow+=minn;
            edge[i^1].flow-=minn;
            cost+=edge[i].cost*minn;
        }
        flow+=minn;
    }
    return flow;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m,l;
        scanf("%d%d%d",&n,&m,&l);
        init(n+m+2);
        for(int i=0; i<n; i++)
        {
            scanf("%lf",vx+i);
            addedge(n+m,i,log(vx[i]),0);
        }
        for(int i=0; i<m; i++)
        {
            scanf("%lf",vy+i);
            addedge(n+i,n+m+1,log(vy[i]),0);
        }
        for(int i=0; i<l; i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            addedge(x-1,y+n-1,INF,0);
        }
        int cost=0;
        printf("%.4f\n",pow(e,minCostMaxFlow(n+m,n+m+1,cost)));
    }
    return 0;
}
```

