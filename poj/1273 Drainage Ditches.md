# **POJ 1273:Drainage Ditches (最大流)**

## **Description**

> Every time it rains on Farmer John's fields, a pond forms over Bessie's favorite clover patch. This means that the clover is covered by water for awhile and takes quite a long time to regrow. Thus, Farmer John has built a set of drainage ditches so that Bessie's clover patch is never covered in water. Instead, the water is drained to a nearby stream. Being an ace engineer, Farmer John has also installed regulators at the beginning of each ditch, so he can control at what rate water flows into that ditch. 
>
> Farmer John knows not only how many gallons of water each ditch can transport per minute but also the exact layout of the ditches, which feed out of the pond and into each other and stream in a potentially complex network. 
>
> Given all this information, determine the maximum rate at which water can be transported out of the pond and into the stream. For any given ditch, water flows in only one direction, but there might be a way that water can flow in a circle. 



## **Input**

> The input includes several cases. For each case, the first line contains two space-separated integers, N (0 <= N <= 200) and M (2 <= M <= 200). N is the number of ditches that Farmer John has dug. M is the number of intersections points for those ditches. Intersection 1 is the pond. Intersection point M is the stream. Each of the following N lines contains three integers, Si, Ei, and Ci. Si and Ei (1 <= Si, Ei <= M) designate the intersections between which this ditch flows. Water will flow through this ditch from Si to Ei. Ci (0 <= Ci <= 10,000,000) is the maximum rate at which water will flow through the ditch.



## **Output**

> For each case, output a single integer, the maximum rate at which water may emptied from the pond. 



## **Sample Input**

    5 4
    1 2 40
    1 4 20
    2 4 20
    2 3 30
    3 4 10



## **Sample Output**

    50


## **题意**

下雨的时候约翰的田里总是积水，积水淹没了他种的三叶草，于是他做了若干条排水沟，每条沟在起始处安置一个阀门来控制这条沟的最大排水量，现在给出沟的条数以及阀门的个数，并给出每条沟的最大排水量，求在处理积水时的最大排出量。



## **思路**

最大流模板题，源点为1，汇点为m，求从1到m的最大流即可。



## **AC 代码**

```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 210;
const int MAXM = 210*2;
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
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%d",&ai,&bi,&ci);
            addedge(ai,bi,ci);
        }
        printf("%d\n",dinic(1,m));
    }
    return 0;
}
```


