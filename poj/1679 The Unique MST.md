# The Unique MST

## **Description**

> Given a connected undirected graph, tell if its minimum spanning tree is unique. 
>
> Definition 1 (Spanning Tree): Consider a connected, undirected graph G = (V, E). A spanning tree of G is a subgraph of G, say T = (V', E'), with the following properties: 
>
> 1. V' = V. 
>
> 2. T is connected and acyclic. 
>
> Definition 2 (Minimum Spanning Tree): Consider an edge-weighted, connected, undirected graph G = (V, E). The minimum spanning tree T = (V, E') of G is the spanning tree that has the smallest total cost. The total cost of T means the sum of the weights on all the edges in E'. 



## **Input**

> The first line contains a single integer t (1 <= t <= 20), the number of test cases. Each case represents a graph. It begins with a line containing two integers n and m (1 <= n <= 100), the number of nodes and edges. Each of the following m lines contains a triple (xi, yi, wi), indicating that xi and yi are connected by an edge with weight = wi. For any two nodes, there is at most one edge connecting them.



## **Output**

> For each input, if the MST is unique, print the total cost of it, or otherwise print the string 'Not Unique!'.



## **Sample Input**

    2
    3 3
    1 2 1
    2 3 2
    3 1 3
    4 4
    1 2 2
    2 3 2
    3 4 2
    4 1 2



## **Sample Output**

    3
    Not Unique!


## **题意**

给定一张图，求它的最小生成树是否唯一，若唯一输出最小生成树权值和，否则输出 `Not Unique!` 。



## **思路**

直接求给定图的次小生成树，然后枚举所有不在 `MST` 中的边，替换掉最大边权的边以后若此时的结果仍是原 `MST` 边权和，说明最小生成树不唯一，否则唯一。



## **AC 代码**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxn = 110;
const int inf = 0x3f3f3f;
bool vis[maxn];
int lowc[maxn];
int pre[maxn];
int Max[maxn][maxn];
bool used[maxn][maxn];
int cost[maxn][maxn];

int prim(int n)
{
    int ans=0;
    memset(vis,false,sizeof(vis));
    memset(Max,0,sizeof(Max));
    memset(used,false,sizeof(used));
    vis[0]=true;
    pre[0]=-1;
    for(int i=1; i<n; i++)
    {
        lowc[i]=cost[0][i];
        pre[i]=0;
    }
    lowc[0]=0;
    for(int i=1; i<n; i++)
    {
        int minc=inf;
        int p=-1;
        for(int j=0; j<n; j++)
        {
            if(!vis[j]&&minc>lowc[j])
            {
                minc=lowc[j];
                p=j;
            }
        }
        if(minc==inf)return -1;
        ans+=minc;
        vis[p]=true;
        used[p][pre[p]]=used[pre[p]][p]=true;
        for(int j=0; j<n; j++)
        {
            if(vis[j]&&j!=p)
                Max[j][p]=Max[p][j]=max(Max[j][pre[p]],lowc[p]);
            if(!vis[j]&&lowc[j]>cost[p][j])
            {
                lowc[j]=cost[p][j];
                pre[j]=p;
            }
        }
    }
    return ans;
}

void init(int n)
{
    memset(cost,inf,sizeof(cost));
    for(int i=0; i<n; i++)
        cost[i][i]=0;
}

void solve(int n)
{
    int ans=prim(n);    // 最小生成树权值和
    int ss=inf;
    for(int i=0; i<n; i++)  // 枚举两点之间的边
        for(int j=i+1; j<n; j++)
            if(cost[i][j]!=inf&&!used[i][j])    // 如果 (i,j) 间存在边并且不在MST中
                ss=min(ss,ans+cost[i][j]-Max[i][j]);
    if(ss==ans)
        printf("Not Unique!\n");
    else printf("%d\n",ans);
}

int main()
{
    int T,n,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        init(n);
        for(int i=0; i<m; i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            cost[a-1][b-1]=cost[b-1][a-1]=c;
        }
        solve(n);
    }
    return 0;
}
```

