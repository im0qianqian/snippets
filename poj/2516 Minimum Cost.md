# Minimum Cost

## **Description**

> Dearboy, a goods victualer, now comes to a big problem, and he needs your help. In his sale area there are N shopkeepers (marked from 1 to N) which stocks goods from him.Dearboy has M supply places (marked from 1 to M), each provides K different kinds of goods (marked from 1 to K). Once shopkeepers order goods, Dearboy should arrange which supply place provide how much amount of goods to shopkeepers to cut down the total cost of transport. 
>
> It's known that the cost to transport one unit goods for different kinds from different supply places to different shopkeepers may be different. Given each supply places' storage of K kinds of goods, N shopkeepers' order of K kinds of goods and the cost to transport goods for different kinds from different supply places to different shopkeepers, you should tell how to arrange the goods supply to minimize the total cost of transport.



## **Input**

> The input consists of multiple test cases. The first line of each test case contains three integers N, M, K (0 < N, M, K < 50), which are described above. The next N lines give the shopkeepers' orders, with each line containing K integers (there integers are belong to [0, 3]), which represents the amount of goods each shopkeeper needs. The next M lines give the supply places' storage, with each line containing K integers (there integers are also belong to [0, 3]), which represents the amount of goods stored in that supply place. 
>
> Then come K integer matrices (each with the size N * M), the integer (this integer is belong to (0, 100)) at the i-th row, j-th column in the k-th matrix represents the cost to transport one unit of k-th goods from the j-th supply place to the i-th shopkeeper. 
>
> The input is terminated with three "0"s. This test case should not be processed.



## **Output**

> For each test case, if Dearboy can satisfy all the needs of all the shopkeepers, print in one line an integer, which is the minimum cost; otherwise just output "-1".



## **Sample Input**

    1 3 3   
    1 1 1
    0 1 1
    1 2 2
    1 0 1
    1 2 3
    1 1 1
    2 1 1
    
    1 1 1
    3
    2
    20
    
    0 0 0



## **Sample Output**

    4
    -1


## **题意**

有n个店主，k个物品，m个供应商，求满足店主需求所需要的最小花费。



## **思路**

分析题目可以得出，k个物品之间是没有关系的，因为它们之间的独立，所以我们可以将这k个物品单独计算。

创建源点与汇点，从源点到供应商之间的一条容量为供应量费用为0的边可以看作是供应商的供应情况，然后从店主到汇点之间一条容量为需求量费用为0的边可以看作是店主的需求情况，至于供应商与店主之间也有相应的边，它的容量可以是无限大，然后需要的花费为实际花费，此时从源点到汇点之间的最小费用即为供应这一种物品所需要花费的最小费用。

当供应量不足需求的时候，输出 `-1` 。



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

const int MAXX = 100005;
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
 * 返回费用cost
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

int dn[105][105],dm[105][105];
int ctos[105][105];

int main()
{
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k)&&(n||m||k))
    {
        bool flag=true;
        int ans=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<k; j++)
                scanf("%d",&dn[i][j]);
        for(int i=0; i<m; i++)
            for(int j=0; j<k; j++)
                scanf("%d",&dm[i][j]);
        for(int ki=0; ki<k; ki++)   //第ki种物品
        {
            init(n+m+2);    //初始化 共n+m+2个点
            int cost,temp=0,f1=0,f2=0;
            for(int j=0; j<n; j++)
            {
                f1+=dn[j][ki];  //总需求
                addedge(m+j,n+m+1,dn[j][ki],0); //从店主到汇点之间的边，容量为需求量，费用为0
            }
            for(int j=0; j<m; j++)
            {
                f2+=dm[j][ki];  //总供应
                addedge(n+m,j,dm[j][ki],0);     //从源点到供应商之间的边，容量为供应量，费用为0
            }

            for(int i=0; i<n; i++)
                for(int j=0; j<m; j++)
                {
                    scanf("%d",&cost);          //供应第ki个商品时从供应商到店主之间所需要的花费
                    addedge(j,m+i,INF,cost);
                }
            if(flag)
            {
                minCostMaxFlow(n+m,n+m+1,temp); //求源点到汇点的最小费用
                if(f1>f2)flag=false;            //如果供应不满足需求
                ans+=temp;
            }
        }
        printf(flag?"%d\n":"-1\n",ans);
    }
    return 0;
}
```

