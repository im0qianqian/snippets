# **POJ 2135 Farm Tour**

## **Description**

> When FJ's friends visit him on the farm, he likes to show them around. His farm comprises N (1 <= N <= 1000) fields numbered 1..N, the first of which contains his house and the Nth of which contains the big barn.  A total M (1 <= M <= 10000) paths that connect the fields in various ways. Each path connects two different fields and has a nonzero length smaller than 35,000. 
>
> To show off his farm in the best way, he walks a tour that starts at his house, potentially travels through some fields, and ends at the barn.  Later, he returns (potentially through some fields) back to his house again. 
>
> He wants his tour to be as short as possible, however he doesn't want to walk on any given path more than once. Calculate the shortest tour possible.  FJ is sure that some tour exists for any given farm.



## **Input**

> Line 1: Two space-separated integers: N and M. 
>
> Lines 2..M+1: Three space-separated integers that define a path: The starting field, the end field, and the path's length. 


## **Output**

> A single line containing the length of the shortest tour. 



## **Sample Input**

    4 5
    1 2 1
    2 3 1
    3 4 1
    1 3 2
    2 4 2



## **Sample Output**

	6


## **题意**

FJ有N个农场，M条路，FJ要领朋友游玩，从1走到N，再回到1，不走重复路，每条路长度不一样，问最短路长为多少。



## **思路**

最小费用最大流，题目等同于从1到N这些点建立的图，然后我们找两条不相交从1到N的路径，并且路径长度的和最短。

可以转化为网络流的问题，我们假设每条边的费用为原来路径的长度，边的容量为1，然后给图中增加一个源点与一个汇点，源点连接图中第1个点，边费用为0，容量为2，汇点与第N个点相连，边费用为0，容量为2。

仔细想想我们可以知道，源点和汇点的加入并不影响总路径长度，因为与他们相接的边的长度都为0，但是容量为2代表可以同时从该点出发或汇入的流量增加到原来两倍，等同于两条路径同时有效。

因为原图边容量都为1，所以不存在使用网络流计算时会出现重边情况。



## **AC代码**

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

const int MAXX = 40010;
const int INF = 0x3f3f3f3f;

struct edge
{
    int to;
    int next;
    int cap;
    int flow;
    int cost;
} edge[MAXX];

int head[MAXX],tol;
int pre[MAXX],dis[MAXX];
bool vis[MAXX];
int N;  //节点总个数

void init(int n)
{
    N=n;
    tol=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int cap,int cost)
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

bool spfa(int s,int t)
{
    queue<int>q;
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
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            int v=edge[i].to;
            if(edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost)
            {
                dis[v]=dis[u]+edge[i].cost;
                pre[v]=i;
                if(!vis[v])
                {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t]==-1)return false;
    else return true;
}

/*
 * int s 起点
 * int t 终点
 * 返回最大流
 */
int minCostMaxFlow(int s,int t)
{
    int cost=0;
    while(spfa(s,t))
    {
        int minn=INF;
        for(int i=pre[t]; i!=-1; i=pre[edge[i^1].to])
        {
            if(minn>edge[i].cap-edge[i].flow)
                minn=edge[i].cap-edge[i].flow;
        }
        for(int i=pre[t]; i!=-1; i=pre[edge[i^1].to])
        {
            edge[i].flow+=minn;
            edge[i^1].flow-=minn;
            cost+=edge[i].cost*minn;
        }
    }
    return cost;
}

int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        init(n+2);  //因为有增加的两个点
        int st,ed,cost;
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d",&st,&ed,&cost);
            addedge(st,ed,1,cost);
            addedge(ed,st,1,cost);
        }
        addedge(0,1,2,0);   //增加的源点与汇点
        addedge(n,n+1,2,0);
        printf("%d\n",minCostMaxFlow(0,n+1));
    }
    return 0;
}
```

