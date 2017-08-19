# Apple Tree

## **Description**

> There is an apple tree outside of kaka's house. Every autumn, a lot of apples will grow in the tree. Kaka likes apple very much, so he has been carefully nurturing the big apple tree.
>
> The tree has N forks which are connected by branches. Kaka numbers the forks by 1 to N and the root is always numbered by 1. Apples will grow on the forks and two apple won't grow on the same fork. kaka wants to know how many apples are there in a sub-tree, for his study of the produce ability of the apple tree.
>
> The trouble is that a new apple may grow on an empty fork some time and kaka may pick an apple from the tree for his dessert. Can you help kaka?



## **Input**

> The first line contains an integer N (N ≤ 100,000) , which is the number of the forks in the tree.
>
> The following N - 1 lines each contain two integers u and v, which means fork u and fork v are connected by a branch.
>
> The next line contains an integer M (M ≤ 100,000).
>
> The following M lines each contain a message which is either
>
> "C x" which means the existence of the apple on fork x has been changed. i.e. if there is an apple on the fork, then Kaka pick it; otherwise a new apple has grown on the empty fork.
>
> or
>
> "Q x" which means an inquiry for the number of apples in the sub-tree above the fork x, including the apple (if exists) on the fork x
>
> Note the tree is full of apples at the beginning



## **Output**

> For every inquiry, output the correspond answer per line.



## **Sample Input**

    3
    1 2
    1 3
    3
    Q 1
    C 2
    Q 1



## **Sample Output**

    3
    2


## **题意**

给出一棵苹果树，每个节点一开始都有苹果。

C X ：如果 `X` 点有苹果，则拿掉，如果没有，则新长出一个。

Q X ：查询 `X` 点与它的所有后代分支一共有几个苹果。



## **思路**

通过一次 dfs 记录每个节点的 dfs 序 `num[i]` 以及其所有后代 dfs 序中的最大值 `son[i]` 。

我们按照 dfs 序将每个节点维护在数组中，则节点 `a` 的所有后代分支部分即 `num[i]` 与 `son[i]` 之间的部分。

于是问题便变成了区间点修改以及查询了，用线段树或者树状数组都可以解决。



## **AC 代码**

```cpp
#include<iostream>
#include<cstring>
using namespace std;
typedef __int64 LL;
const int maxn = 1e5+10;

int sum[maxn];
int vis[maxn];
int num[maxn];
int son[maxn];
int n;

struct node
{
    int to;
    int next;
} edge[maxn<<1];

int head[maxn<<1],tot,ind;

inline int lowbit(int x)
{
    return x&-x;
}

int query(int o)
{
    int ans=0;
    while(o>0)
    {
        ans+=sum[o];
        o-=lowbit(o);
    }
    return ans;
}

void add(int o,int val)
{
    while(o<=n)
    {
        sum[o]+=val;
        o+=lowbit(o);
    }
}

void init()
{
    memset(sum,0,sizeof(sum));
    memset(vis,-1,sizeof(vis));
    memset(head,-1,sizeof(head));
    tot=ind=0;
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

void dfs(int u,int fa)
{
    num[u]=++ind;
    son[u]=num[u];
    for(int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==fa)continue;
        dfs(v,u);
        son[u]=max(son[u],son[v]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while(cin>>n)
    {
        init();
        for(int i=1; i<n; i++)
        {
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,-1);
        for(int i=1; i<=n; i++)
            add(i,1);
        int m,x;
        char c;
        cin>>m;
        while(m--)
        {
            cin>>c>>x;
            if(c=='Q')
                cout<<query(son[x])-query(num[x]-1)<<endl;
            else
            {
                add(num[x],vis[x]);
                vis[x]=-vis[x];
            }
        }
    }
    return 0;
}
```

