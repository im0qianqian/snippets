# transaction transaction transaction

## **Description**

> Kelukin is a businessman. Every day, he travels around cities to do some business. On August 17th, in memory of a great man, citizens will read a book named "the Man Who Changed China". Of course, Kelukin wouldn't miss this chance to make money, but he doesn't have this book. So he has to choose two city to buy and sell. 
>
> As we know, the price of this book was different in each city. It is ai yuan in it city. Kelukin will take taxi, whose price is 1yuan per km and this fare cannot be ignored.
>
> There are n−1 roads connecting n cities. Kelukin can choose any city to start his travel. He want to know the maximum money he can get.



## **Input**

> The first line contains an integer T (1≤T≤10) , the number of test cases. 
>
> For each test case:
>
> first line contains an integer n (2≤n≤100000) means the number of cities;
>
> second line contains n numbers, the ith number means the prices in ith city; (1≤Price≤10000) 
>
> then follows n−1 lines, each contains three numbers x, y and z which means there exists a road between x and y, the distance is zkm (1≤z≤1000). 



## **Output**

> For each test case, output a single number in a line: the maximum money he can get.



## **Sample Input**

    1  
    4  
    10 40 15 30  
    1 2 30
    1 3 2
    3 4 10



## **Sample Output**

    8



## **题意**

给一棵树，每个节点都有权值（书的价格），树中的边是消耗，从任意一点买一本书，卖到另一个点，求最大的利益。



## **思路**

树形 dp ，树中任意两点都可以找到其最近公共祖先，且这两点之间的路线一定经过该点。

我们利用这个性质，设 $in[x]$ 代表 $x$ 的子树中我们找一点买一本书到当前点的最小消耗。

$out[x]$ 代表 $x$ 的子树中找一点卖一本书到当前点的最大利益。

则最终的结果便是最大的 $in[x]+out[x]$ 。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define inf 0x3f3f3f3f
const int maxn = 2e5+10;
struct node
{
    int to;
    int next;
    int cost;
} edge[maxn];
int head[maxn],tot;
int n;
int pri[maxn];
LL ans;
LL in[maxn];
LL out[maxn];

void init()
{
    memset(head,-1,sizeof(head));
    memset(in,-inf,sizeof(in));
    ans=tot=0;
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
    in[x]=-pri[x];
    out[x]=pri[x];
    for(int i=head[x]; i!=-1; i=edge[i].next)
    {
        int to=edge[i].to;
        if(to==fa)continue;
        dfs(to,x);
        in[x]=max(in[x],in[to]-edge[i].cost);
        out[x]=max(out[x],out[to]-edge[i].cost);
        ans=max(ans,in[x]+out[x]);
    }
}

int main()
{
    int T;
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)
    {
        init();
        cin>>n;
        for(int i=1; i<=n; i++)
            cin>>pri[i];
        for(int i=1; i<n; i++)
        {
            int u,v,cost;
            cin>>u>>v>>cost;
            addedge(u,v,cost);
            addedge(v,u,cost);
        }
        dfs(1,-1);
        cout<<ans<<endl;
    }
    return 0;
}
```

