# **HDU 3549 Flow Problem**

## **Problem Description**

> Network flow is a well-known difficult problem for ACMers. Given a graph, your task is to find out the maximum flow for the weighted directed graph.



## **Input**

> The first line of input contains an integer T, denoting the number of test cases.
>
> For each test case, the first line contains two integers N and M, denoting the number of vertexes and edges in the graph. (2 <= N <= 15, 0 <= M <= 1000)
>
> Next M lines, each line contains three integers X, Y and C, there is an edge from X to Y and the capacity of it is C. (1 <= X, Y <= N, 1 <= C <= 1000)



## **Output**

> For each test cases, you should output the maximum flow from source 1 to sink N.



## **Sample Input**

    2
    3 2
    1 2 1
    2 3 1
    3 3
    1 2 1
    2 3 1
    1 3 1



## **Sample Output**

    Case 1: 1
    Case 2: 2



## **分析**

给出一张图，求从1到n的最大流。

本来很简单的最大流问题，结果刚好写了一道最小费用最大流的题目，所以直接拿来代码用啦！



## **AC代码：**

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

const int MAXX = 1005;
const int INF = 0x3f3f3f3f;

struct edge
{
    int to;     //边终点
    int next;   //下一个兄弟位置
    int cap;    //容量
    int flow;   //流量
    int cost;   //费用
} edge[MAXX<<1];

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
 * 返回最大流flow
 */
int minCostMaxFlow(int s,int t)
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
        }
        flow+=minn;
    }
    return flow;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1; ti<=T; ti++)
    {
        int n,m,s,t,cost;
        scanf("%d%d",&n,&m);
        init(n+1);
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d",&s,&t,&cost);
            addedge(s,t,cost,1);
        }
        printf("Case %d: %d\n",ti,minCostMaxFlow(1,n));
    }
    return 0;
}
```

