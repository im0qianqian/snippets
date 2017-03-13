# Going Home

## **Description**

> On a grid map there are n little men and n houses. In each unit time, every little man can move one unit step, either horizontally, or vertically, to an adjacent point. For each little man, you need to pay a $1 travel fee for every step he moves, until he enters a house. The task is complicated with the restriction that each house can accommodate only one little man. 
>
> Your task is to compute the minimum amount of money you need to pay in order to send these n little men into those n different houses. The input is a map of the scenario, a '.' means an empty space, an 'H' represents a house on that point, and am 'm' indicates there is a little man on that point. 
>
> ![img](http://poj.org/images/2195_1.jpg)
>
> You can think of each point on the grid map as a quite large square, so it can hold n little men at the same time; also, it is okay if a little man steps on a grid with a house without entering that house.



## **Input**

> There are one or more test cases in the input. Each case starts with a line giving two integers N and M, where N is the number of rows of the map, and M is the number of columns. The rest of the input will be N lines describing the map. You may assume both N and M are between 2 and 100, inclusive. There will be the same number of 'H's and 'm's on the map; and there will be at most 100 houses. Input will terminate with 0 0 for N and M.



## **Output**

> For each test case, output one line with the single integer, which is the minimum amount, in dollars, you need to pay.



## **Sample Input**

    2 2
    .m
    H.
    5 5
    HH..m
    .....
    .....
    .....
    mm..H
    7 8
    ...H....
    ...H....
    ...H....
    mmmHmmmm
    ...H....
    ...H....
    ...H....
    0 0


## **Sample Output**

    2
    10
    28


## **题意**

给出一张地图， `.` 是空地， `H` 是房子， `m` 是小人，并且地图上有相同数量的房子与小人，每个小人每次只能横向或者纵向移动一格，求最终所有人都找到一间独立的房子所走的步数。



## **思路**

幸好地图上没有**墙**（降低难度），人物也可以相遇在同一格，那么小人距离任意一个房间的步数便是它们两者横坐标差+纵坐标差。

找一个源点，它与所有小人之见都有一条容量为1费用为0的边，然后所有房子与汇点之间也有一条容量为1费用为0的边，小人与房子之间的边容量为1，费用为它们之间的距离（步数）。

当然反向建图也可以，因为这张图是对称的嘛！并且房子个数与小人个数也相等。

然后求从源点到汇点之间的最小费用即可。



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

const int MAXX = 10005;
const int INF = 0x3f3f3f3f;

struct edge
{
    int to;     //边终点
    int next;   //下一个兄弟位置
    int cap;    //容量
    int flow;   //流量
    int cost;   //费用
} edge[MAXX<<2];

int head[MAXX],tol;
int pre[MAXX],dis[MAXX];
int N;  //节点总个数

void init(int n)
{
    N=n;
    tol=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int cap,int cost)  //同时增加原边与反向边
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
int minCostMaxFlow(int s,int t,int &cost)
{
    int flow=0;
    while(spfa(s,t))
    {
        int minn=INF;   //当前路径可增广值
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

struct node
{
    int x;
    int y;
    node() {}
    node(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
};

inline int getlen(node a,node b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}

int main()
{
    int n,m;
    char str[105][105];
    while(~scanf("%d%d%*c",&n,&m)&&(n||m))
    {
        node H[5005],M[5005];   //模拟栈
        int th=0,tm=0;
        for(int i=0; i<n; i++)
        {
            gets(str[i]);
            for(int j=0; j<m; j++)
            {
                if(str[i][j]=='H')
                    H[th++]=node(i,j);  //房子
                else if(str[i][j]=='m')
                    M[tm++]=node(i,j);  //小人
            }
        }
        init(th+tm+2);
        for(int i=0; i<th; i++)
        {
            addedge(th+tm,i,1,0);       //源点到房子
            for(int j=0; j<tm; j++)
                addedge(i,th+j,1,getlen(H[i],M[j]));    //房子到小人
        }
        for(int i=0; i<tm; i++)
            addedge(th+i,th+tm+1,1,0);  //小人到汇点
        int cost=0;
        minCostMaxFlow(th+tm,th+tm+1,cost);
        printf("%d\n",cost);
    }
    return 0;
}
```

