# I Curse Myself

## **Description**

> There is a connected undirected graph with weights on its edges. It is guaranteed that each edge appears in at most one simple cycle.
>
> Assuming that the weight of a weighted spanning tree is the sum of weights on its edges, define $V(k)$ as the weight of the k-th smallest weighted spanning tree of this graph, however, $V(k)$ would be defined as zero if there did not exist k different weighted spanning trees.
>
> Please calculate $(\sum _{k=1}^Kk⋅V(k))mod~2^{32}$ .



## **Input**

> The input contains multiple test cases.
>
> For each test case, the first line contains two positive integers $n,m (2≤n≤1000,n−1≤m≤2n−3)$ , the number of nodes and the number of edges of this graph.
>
> Each of the next m lines contains three positive integers $x,y,z (1≤x,y≤n,1≤z≤10^6)$ , meaning an edge weighted z between node x and node y. There does not exist multi-edge or self-loop in this graph.
>
> The last line contains a positive integer $K (1≤K≤10^5)$ .



## **Output**

> For each test case, output "Case #x: y" in one line (without quotes), where x indicates the case number starting from 1 and y denotes the answer of corresponding case.



## **Sample Input**

    4 3
    1 2 1
    1 3 2
    1 4 3
    1
    3 3
    1 2 1
    2 3 2
    3 1 3
    4
    6 7
    1 2 4
    1 3 2
    3 5 7
    1 5 3
    2 4 1
    2 6 2
    6 4 5
    7



## **Sample Output**

    Case #1: 6
    Case #2: 26
    Case #3: 493


## **题意**

求一棵无向仙人掌图中前 $k$ 小的生成树权值和。



## **思路**

首先我们需要清楚什么是无向仙人掌图，它是一张连通图，且任意一条边都至多属于一个环。

也就是说，仙人掌图的一棵生成树就是其每个环去掉一条边所形成的图。

那么我们可以一次通过 $dfs$ 找出所有环，然后存储每个环中的所有边长，此时问题就变成了在 $n$ 个数组中各取一个数，求其和的前 $k$ 大的数，也算一个经典问题啦~

PS：在最后求解前 $k$ 大的和时千万不要用 $O(n^3)$ 的算法，否则 TLE 到 cry 😭



## **AC 代码**

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 2100;
typedef pair<int,int> P;
typedef __int64 LL;

struct node
{
    int to;
    int next;
    int cost;
} edge[maxn<<1];

int head[maxn<<1],tot;
int Stack[maxn],stop;
bool instack[maxn];
int n,m,k;
bool isStart;
bool vis[maxn];
int g[maxn][maxn];
int Bcnt;
vector<int>G[maxn];
vector<int> f,tmpf;
LL mod = 1LL<<32;

void init()
{
    memset(head,-1,sizeof(head));
    memset(vis,false,sizeof(vis));
    memset(instack,false,sizeof(instack));
    tot=stop=Bcnt=0;
    isStart=false;
    f.clear();
    tmpf.clear();
}

void addedge(int u,int v,int cost)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    edge[tot].cost=cost;
    head[u]=tot++;
}

void dfs(int x,int fa)
{
    Stack[++stop]=x;
    instack[x]=true;
    vis[x]=true;
    for(int i=head[x]; i!=-1; i=edge[i].next)
    {
        int to=edge[i].to;
        if(to==fa)continue;
        if(!vis[to])
            dfs(to,x);
        else if(instack[to])        // 找到仙人掌的一个环
        {
            vector<int> G;
            int top=stop;
            int p=to;
            while(Stack[top]!=to)   // 统计环中所有边长
            {
                G.push_back(g[p][Stack[top]]);
                p=Stack[top--];
            }
            G.push_back(g[p][Stack[top]]);
            sort(G.begin(),G.end(),[](const int &a,const int &b)    // 边长从大到小排序
            {
                return a>b;
            });
            int len=G.size();
            if(!isStart)            // 第一次计算
            {
                for(int j=0; j<len; j++)
                    f.push_back(G[j]);
                isStart=true;
            }
            else
            {
                int cnt=f.size()*len;
                cnt=min(cnt,k);
                priority_queue<P> que;
                for(int j=0; j<len; j++)
                    que.push(P(f[0]+G[j],0));
                tmpf.clear();
                while(cnt--)
                {
                    P p=que.top();
                    que.pop();
                    tmpf.push_back(p.first);
                    if(p.second!=(int)f.size()-1)
                    {
                        p.first-=f[p.second++];
                        p.first+=f[p.second];
                        que.push(p);
                    }
                }
                swap(f,tmpf);
            }
        }
    }
    instack[x]=false;
    stop--;
}

int main()
{
    for(int ti=1; ~scanf("%d%d",&n,&m); ti++)
    {
        init();
        LL cnt=0,ans=0;
        for(int i=0; i<m; i++)
        {
            int u,v,cost;
            cin>>u>>v>>cost;
            addedge(u,v,cost);
            addedge(v,u,cost);
            g[u][v]=g[v][u]=cost;
            cnt+=cost;
        }
        scanf("%d",&k);
        dfs(1,-1);
        int len=f.size();
        if(!len)ans=cnt;
        for(int i=0; i<len; i++)
            ans=(ans+(1LL*(i+1)*(cnt-f[i]))%mod)%mod;
        printf("Case #%d: %I64d\n",ti,ans);
    }
    return 0;
}
```

