# **POJ 3469：Dual Core CPU（最大流）**

## **Description**

> As more and more computers are equipped with dual core CPU, SetagLilb, the Chief Technology Officer of TinySoft Corporation, decided to update their famous product - SWODNIW.
>
> The routine consists of N modules, and each of them should run in a certain core. The costs for all the routines to execute on two cores has been estimated. Let's define them as Ai and Bi. Meanwhile, M pairs of modules need to do some data-exchange. If they are running on the same core, then the cost of this action can be ignored. Otherwise, some extra cost are needed. You should arrange wisely to minimize the total cost.



## **Input**

> There are two integers in the first line of input data, N and M (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000) .
>
> The next N lines, each contains two integer, Ai and Bi.
>
> In the following M lines, each contains three integers: a, b, w. The meaning is that if module a and module b don't execute on the same core, you should pay extra w dollars for the data-exchange between them.



## **Output**

> Output only one integer, the minimum total cost.



## **Sample Input**

    3 1
    1 10
    2 10
    10 3
    2 3 1000



## **Sample Output**

		13


## **题意**

有n个模块，每个模块在A上花费ai，在B上花费bi，然后有m个任务(ai,bi,wi)，如果ai,bi不在一起工作的话需要额外花费wi，求最小花费。



## **思路**

开始想了很久如何建图可以求得最小花费，最后发现它其实是一个最小割模型。

将网络里的模块划分成s-t两个点集，然后需要合适的方法去构建这个最小割模型。

对于每一个模块，考虑它在A集时，花费为ai，便从s出发连接一条ai的边，考虑它在B集时，花费为bi，便向t连接一条bi的边，而最终对于每一个任务，因为当ai与bi不同的时候会增加额外花费，所以在ai与bi之间连接一条wi的双向边。

题目中的最小花费，可以很轻松的发现它其实是我们构建出这个图的最小割，根据最大流最小割定理，我们只需要求出从源点s到汇点t的最大流便可。



## **AC代码**

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 200000;
const int MAXM = 100000000;
const int INF = 0x3f3f3f3f;

struct edge
{
    int v,f;    //边终点与当前流量
    int next;   //下一个兄弟位置
} edge[MAXM];

int n,m;
int index;
int head[MAXN];
int level[MAXN];

void init()
{
    index =0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int f) //同时往图中添加原边与反向边
{
    edge[index].v=v;
    edge[index].f=f;
    edge[index].next=head[u];
    head[u]=index++;
    edge[index].v=u;
    edge[index].f=0;
    edge[index].next=head[v];
    head[v]=index++;
}

int bfs(int s,int t)    //利用bfs搜索当前残量图中是否存在s到t的路径
{
    memset(level,0,sizeof(level));  //level为从源点到当前点的距离
    level[s]=1;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        if(x==t)return 1;
        for(int e=head[x]; e!=-1; e=edge[e].next)  //遍历所有与u临接的点
        {
            int v=edge[e].v,f=edge[e].f;
            if(!level[v]&&f)
            {
                level[v]=level[x]+1;    //广度优先搜索下一层距离源点比当前多1
                q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int s,int maxf,int t)
{
    if(s==t)return maxf;    //找到一条路径，返回当前路径中的最小流量
    int ret=0;
    for(int e=head[s]; e!=-1; e=edge[e].next)   //遍历s所有邻接的点
    {
        int v=edge[e].v,f=edge[e].f;
        if(level[s]+1==level[v]&&f) //如果新点可达并且标号为允许弧
        {
            int minn=min(maxf-ret,f);
            f=dfs(v,minn,t);
            edge[e].f-=f;
            edge[e^1].f+=f;
            ret+=f;
            if(ret==maxf)return ret;
        }
    }
    return ret;
}

int dinic(int s,int t)
{
    int ans=0;
    while(bfs(s,t)) //先确定是否存在路径从s到t
        ans+=dfs(s,INF,t);  //
    return ans;
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
        int ai,bi,ci;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d",&ai,&bi);
            addedge(0,i,ai);
            addedge(i,n+1,bi);
        }
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d",&ai,&bi,&ci);
            addedge(ai,bi,ci);
            addedge(bi,ai,ci);
        }
        printf("%d\n",dinic(0,n+1));
    }
    return 0;
}
```

