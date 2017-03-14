# Kaka's Matrix Travels

## **Description**

> On an N × N chessboard with a non-negative number in each grid, Kaka starts his matrix travels with SUM = 0. For each travel, Kaka moves one rook from the left-upper grid to the right-bottom one, taking care that the rook moves only to the right or down. Kaka adds the number to SUM in each grid the rook visited, and replaces it with zero. It is not difficult to know the maximum SUM Kaka can obtain for his first travel. Now Kaka is wondering what is the maximum SUM he can obtain after his Kth travel. Note the SUM is accumulative during the K travels.



## **Input**

> The first line contains two integers N and K (1 ≤ N ≤ 50, 0 ≤ K ≤ 10) described above. The following N lines represents the matrix. You can assume the numbers in the matrix are no more than 1000.



## **Output**

> The maximum SUM Kaka can obtain after his Kth travel.



## **Sample Input**

    3 2
    1 2 3
    0 2 1
    1 4 2



## **Sample Output**

    15


## **题意**

给出一个 $N*N$ 的矩阵，找 k 条从左上角到右下角的路径，然后使得路径上的数字和最大。（寻找路径的时候只能向右或者向下走）



## **思路**

和 HDU 3376 一样的题型，只不过 HDU 3376 里面规定只有两条路径，而这里规定有 k 条，然后在建图策略中只需要修改原来矩阵中点到扩充点费用为0的边的容量为k-1即可。

具体请看：[HDU 3376 Matrix Again ](https://www.dreamwings.cn/hdu3376/4120.html)



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

const int MAXX = 5500;
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

int main()
{
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        int N=n*n,temp,cost=0;
        init(N+N+2);
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                scanf("%d",&temp);
                addedge(i*n+j,N+i*n+j,1,-temp); //因为该点只能累加一次，所以容量为1
                addedge(i*n+j,N+i*n+j,k-1,0);   //这里容量是k-1
                if(i!=n-1)
                    addedge(N+i*n+j,(i+1)*n+j,INF,0);
                if(j!=n-1)
                    addedge(N+i*n+j,i*n+j+1,INF,0);
            }
        addedge(N+N,0,k,0);
        addedge(N+N-1,N+N+1,k,0);
        minCostMaxFlow(N+N,N+N+1,cost);
        printf("%d\n",-cost);
    }
    return 0;
}
```

