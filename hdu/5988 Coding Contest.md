# Coding Contest

## **Description**

> A coding contest will be held in this university, in a huge playground. The whole playground would be divided into N blocks, and there would be M directed paths linking these blocks. The i-th path goes from the ui-th block to the vi-th block. Your task is to solve the lunch issue. According to the arrangement, there are si competitors in the i-th block. Limited to the size of table, bi bags of lunch including breads, sausages and milk would be put in the i-th block. As a result, some competitors need to move to another block to access lunch. However, the playground is temporary, as a result there would be so many wires on the path.
>
> For the i-th path, the wires have been stabilized at first and the first competitor who walker through it would not break the wires. Since then, however, when a person go through the i - th path, there is a chance of pi to touch the wires and affect the whole networks. Moreover, to protect these wires, no more than ci competitors are allowed to walk through the i-th path.
>
> Now you need to find a way for all competitors to get their lunch, and minimize the possibility of network crashing.



## **Input**

> The first line of input contains an integer t which is the number of test cases. Then t test cases follow.
>
> For each test case, the first line consists of two integers N (N ≤ 100) and M (M ≤ 5000). Each of the next N lines contains two integers si and bi (si , bi ≤ 200).
>
> Each of the next M lines contains three integers ui , vi and ci(ci ≤ 100) and a float-point number pi(0 < pi < 1).
>
> It is guaranteed that there is at least one way to let every competitor has lunch.



## **Output**

> For each turn of each case, output the minimum possibility that the networks would break down. Round it to 2 digits.



## **Sample Input**

    1
    4 4
    2 0
    0 3
    3 0
    0 3
    1 2 5 0.5
    3 2 5 0.5
    1 4 5 0.5
    3 4 5 0.5



## **Sample Output**

    0.50



## **题意**

有 $n$ 个区域，每个区域都有一些人和食物，区域之间存在 $m$ 条有向路径，每条路都有一个人数上限。路径之间铺了电线，每当有人通过时都会有 $p_i$ 的概率碰到它，但是第一个通过的人一定不会碰到，求所有人都获取到食物而碰到电线的最小概率。



## **思路**

最小费用流的基础题。

首先我们可以让某个区域的人得到当前他所在区域的某个食物，然后原图转化为每一个点存在一些人或者存在一些食物，要求碰到电线的最小概率也就是不碰到电线的最大概率。

假设碰到某条电线的概率为 $p$ ，那不碰到它的概率即为 $1-p$ ，而我们在费用流中的费用是相加得到的，怎么才能转化为那种形式呢？

我们知道 $\log_2(ab)=\log_2a+\log_2b$ ，于是对 $1-p$ 取对数，边的费用就变成了 $-\log_2(1-p)$ （负边权求最大值相当于正边权求最小值），边容量为 $cap-1$ （因为有 $cap-1$ 个人通过这条路径有几率碰到电线），对于第一个人所对应的边，费用为 $0$ ，容量为 $1$ 。

随后从源点向每一个人所在的节点连有向边，每一个食物所在的节点向汇点连有向边，找最小费用即可。

---

PS: 这道题目卡常好严重，貌似 1000ms 的题目 998ms 过的。

So ，如果 TLE 可以考虑再提交一下。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 105;
const int maxm = 21000;
const int INF = 2e9;
const double eps = 1e-8;

struct edge
{
    int to;     //边终点
    int next;   //下一个兄弟位置
    int cap;    //容量
    int flow;   //流量
    double cost;   //费用
} edge[maxm];

int head[maxn],tol;
int pre[maxn];
double dis[maxn];
int N;  //节点总个数
bool vis[maxn];

int person[maxn],thing[maxn];

void init(int n)
{
    N=n;
    tol=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int cap,double cost)  //同时增加原边与反向边
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
            if(edge[i].cap>edge[i].flow&&dis[v]-dis[u]-edge[i].cost>eps)    //如果可以松弛该点
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
int minCostMaxFlow(int s,int t,double &cost)
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

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n=0,m=0;
        scanf("%d%d",&n,&m);
        init(n+2);
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d",person+i,thing+i);
            person[i]-=thing[i];
        }
        for(int i=0; i<m; i++)
        {
            int u=0,v=0,cap=0;
            double p;
            scanf("%d%d%d%lf",&u,&v,&cap,&p);
            p = -log2(1.0-p);
            if(cap>1)
                addedge(u,v,cap-1,p);
            if(cap>0)
                addedge(u,v,1,0);
        }
        for(int i=1; i<=n; i++)
        {
            if(person[i]>0)
                addedge(0,i,person[i],0);
            else
                addedge(i,n+1,-person[i],0);
        }
        double cost = 0;
        minCostMaxFlow(0,n+1,cost);
        printf("%.2f\n",1.0-pow(2,-cost));
    }
    return 0;
}
```

