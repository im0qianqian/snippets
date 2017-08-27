# Mysterious Treasure

## **Description**

> WNJXYK and DIDIDI is playing a game. DIDIDI draws a directed graph G on the paper which contains n points, m directed edges and no cycle. WNJXYK starts from point 1. For every round, WNJXYK will randomly select one of the directed edges which start from current point with equal possibility, and go to next point by this edge. And the game will continue until such edge doesn’t exist. DIDIDI will place the treasure on point n, if WNJXYK go through this point, he can get the treasure. WNJXYK have one chance to delete one edge(he can also don’t choose to delete), that he can increase the probability of getting a treasure. Your assignment is to calculate the probability of WNJXYK getting the treasure in the optimal condition.



## **Input**

> The first line of input contains a positive integer T telling you there are T test cases followed.
>
> For each test case, the first line contains two integers n , m, indicating the number of points ,the number of edges.
>
> Then the following are m lines, each of which contains two integers x and y, indicating there is a edge from x to y.
>
> It is guaranteed that there does not exist multiple edge.



## **Output**

> For each test case, print a line “Case #x: y”, where x is the case number (starting from 1) and y is the probability of he getting the treasure. (round to six decimal places).



## **Sample Input**

    2
    4 4
    1 2
    1 3
    1 4
    2 3
    4 5
    1 2
    1 3
    1 4
    2 3
    2 4



## **Sample Output**

    Case #1: 0.500000
    Case #2: 0.750000



## **题意**

一个有向图，我们可以从中至多删除一条边，求从 1 到 n 的概率最大是多少。



## **思路**

反向建图，枚举删除每一条边。

图中不存在环，因此到达每一个点的值都是由其父节点等概率分配来的，于是我们可以统计每个点有多少个孩子，然后进行记忆化搜索。

时间复杂度： $O(T \times m \times n)$



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define eps (1e-7)

const int maxn = 200;
struct node
{
    int to;
    int next;
} edge[maxn*maxn];
int head[maxn],tot,n,m;
int out[maxn];
double viss[maxn],ans;
bool vis[maxn][maxn];
int delx,dely;

void init()
{
    memset(viss,0,sizeof(viss));
    memset(head,-1,sizeof(head));
    memset(out,0,sizeof(out));
    memset(vis,false,sizeof(vis));
    tot=0;
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

double dfs(int x)
{
    double ans=0.0;
    if(x==1)        // 起点
        ans = 1.0;
    else
    {
        if(fabs(viss[x])>eps)return viss[x];    // 之前计算过的部分
        for(int i=head[x]; i!=-1; i=edge[i].next)
        {
            int to=edge[i].to;
            if(to==delx&&x==dely)continue;
            ans+=dfs(to)/out[to];       // 等概率分配
        }
    }
    viss[x]=ans;
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1; ti<=T; ti++)
    {
        init();
        scanf("%d%d",&n,&m);
        for(int i=0; i<m; i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            addedge(v,u);
            vis[u][v]=true;
            out[u]++;
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                if(vis[i][j])   // 枚举删除每一条边
                {
                    delx=i,dely=j;
                    memset(viss,0.0,sizeof(viss));
                    out[i]--;
                    ans=max(ans,dfs(n));
                    out[i]++;
                }
            }
        memset(viss,0.0,sizeof(viss));
        delx=dely=-1;
        ans=max(ans,dfs(n));    // 不删边的情况
        printf("Case #%d: %.6lf\n",ti,ans);
    }
    return 0;
}
```

