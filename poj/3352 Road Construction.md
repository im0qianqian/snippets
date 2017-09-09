# Road Construction

## **Description**

> It's almost summer time, and that means that it's almost summer construction time! This year, the good people who are in charge of the roads on the tropical island paradise of Remote Island would like to repair and upgrade the various roads that lead between the various tourist attractions on the island.
>
> The roads themselves are also rather interesting. Due to the strange customs of the island, the roads are arranged so that they never meet at intersections, but rather pass over or under each other using bridges and tunnels. In this way, each road runs between two specific tourist attractions, so that the tourists do not become irreparably lost.
>
> Unfortunately, given the nature of the repairs and upgrades needed on each road, when the construction company works on a particular road, it is unusable in either direction. This could cause a problem if it becomes impossible to travel between two tourist attractions, even if the construction company works on only one road at any particular time.
>
> So, the Road Department of Remote Island has decided to call upon your consulting services to help remedy this problem. It has been decided that new roads will have to be built between the various attractions in such a way that in the final configuration, if any one road is undergoing construction, it would still be possible to travel between any two tourist attractions using the remaining roads. Your task is to find the minimum number of new roads necessary.



## **Input**

> The first line of input will consist of positive integers n and r, separated by a space, where 3 ≤ n ≤ 1000 is the number of tourist attractions on the island, and 2 ≤ r ≤ 1000 is the number of roads. The tourist attractions are conveniently labelled from 1 to n. Each of the following r lines will consist of two integers, v and w, separated by a space, indicating that a road exists between the attractions labelled v and w. Note that you may travel in either direction down each road, and any pair of tourist attractions will have at most one road directly between them. Also, you are assured that in the current configuration, it is possible to travel between any two tourist attractions.



## **Output**

> One line, consisting of an integer, which gives the minimum number of roads that we need to add.



## **Sample Input**

    10 12
    1 2
    1 3
    1 4
    2 5
    2 6
    5 6
    3 7
    3 8
    7 8
    4 9
    4 10
    9 10



## **Sample Output**

    2



## **题意**

给出一张图，问至少增加多少条边才能使其成为强连通图。



## **思路**

首先我们可以利用 Tarjan 算法求出图中所有的强连通分量，然后根据每个点所在的强连通分量进行缩点。

缩点的结果是一棵树，于是问题便转化为了求在该缩点树上至少需要增加多少条边才能使其强连通。

**显然其结果是：(树中度为 1 的节点数目 + 1) / 2**



## **AC 代码**

```cpp
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<cstring>
using namespace std;

const int maxn = 2e3;
struct node
{
    int to;
    int next;
} e[maxn];

int head[maxn],tot;
int n,m;
int dfn[maxn],low[maxn],ind,ans;
bool instack[maxn];
int Stack[maxn],Stop,Bcnt;
int blong[maxn];
bool vis[maxn][maxn];
bool viss[maxn][maxn];

void init()
{
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vis,false,sizeof(vis));
    memset(instack,false,sizeof(instack));
    tot=ind=ans=Stop=Bcnt=0;
}

void addedge(int u,int v)
{
    e[tot].to=v;
    e[tot].next=head[u];
    head[u]=tot++;
}

void dfs(int x,int fa)
{
    dfn[x]=low[x]=++ind;
    instack[x]=true;
    Stack[++Stop]=x;
    for(int i=head[x]; i!=-1; i=e[i].next)
    {
        int to=e[i].to;
        if(to==fa)continue;
        if(!dfn[to])
        {
            dfs(to,x);
            if(low[to]<dfn[to])
                low[x]=low[to];
        }
        else if(instack[to]&&dfn[to]<low[x])
            low[x]=dfn[to];
    }
    if (dfn[x]==low[x]) //相等说明i为强连通子图搜索树的根节点
    {
        Bcnt++;
        int top;
        do  //退栈
        {
            top=Stack[Stop--];
            blong[top]=Bcnt;        //记录每一个点属于哪一个强连通分量
            instack[top]=false;
        }
        while (top!=x);
    }
}

void dfs2(int x,int fa)     //统计度为 1 地节点个数
{
    int num=0;
    dfn[x]=1;
    for(int i=head[x]; i!=-1; i=e[i].next)
    {
        num++;
        int to=e[i].to;
        if(to==x||dfn[to])continue;
        dfs2(to,x);
    }
    if(num==1)ans++;
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
        for(int i=0; i<m; i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            viss[u][v]=viss[v][u]=true;
            addedge(u,v);
            addedge(v,u);
        }
        memset(blong,0,sizeof(blong));
        dfs(1,-1);
        init();
        for(int i=1; i<=n; i++)
            for(int j=i+1; j<=n; j++)   //如果 i,j 有边，并且它们属于两个不同的强连通分量，说明 i<->j 为桥
            {
                if(viss[i][j]&&blong[i]!=blong[j]&&!vis[blong[i]][blong[j]])
                {
                    vis[blong[i]][blong[j]]=true;
                    addedge(blong[i],blong[j]);     //缩点重新建图
                    addedge(blong[j],blong[i]);
                }
            }
        dfs2(1,-1);
        printf("%d\n",(ans+1)/2);
    }
    return 0;
}
```

