# Colorful Tree

## **Description**

> There is a tree with n nodes, each of which has a type of color represented by an integer, where the color of node i is ci.
>
> The path between each two different nodes is unique, of which we define the value as the number of different colors appearing in it.
>
> Calculate the sum of values of all paths on the tree that has n(n−1)2 paths in total.



## **Input**

> The input contains multiple test cases.
>
> For each test case, the first line contains one positive integers n, indicating the number of node. (2≤n≤200000)
>
> Next line contains n integers where the i-th integer represents ci, the color of node i. (1≤ci≤n)
>
> Each of the next n−1 lines contains two positive integers x,y (1≤x,y≤n,x≠y), meaning an edge between node x and node y.
>
> It is guaranteed that these edges form a tree.



## **Output**

> For each test case, output "Case #x: y" in one line (without quotes), where x indicates the case number starting from 1 and y denotes the answer of corresponding case.



## **Sample Input**

    3
    1 2 1
    1 2
    2 3
    6
    1 2 1 3 2 1
    1 2
    1 3
    2 4
    2 5
    3 6



## **Sample Output**

    Case #1: 6
    Case #2: 29



## **题意**

给出一棵树，定义两点之间权值为这两点路径上颜色集合的大小，求任意两点权值之和。



## **思路**

换一个方向，任意两点路径颜色集合的大小其实等价于每种颜色至少经过一次这样的路径条数之和。

反过来思考只需要求有多少条路径没有经过这种颜色即可，对于每一种颜色，它可以把树分成一个个树块或单个节点，而每一个树块中的路径条数可以通过其节点数目求得： $\frac{n(n-1)}{2}$ 。

**整个过程我们通过一次 dfs 来实现**

设 $sons[u]$ 为以 $u$ 为根节点的子树大小， $sum[i]$ 表示颜色 $i$ 已经合并的树块大小。

（比如颜色为 $a$ 的某个节点已经合并了两个与它不同颜色的子节点，那么如果它的先辈节点的颜色也为 $a$ ，递归结束回到上面计算时就要排除那两个不同颜色节点的影响，也就是只计算被同一种颜色分割出来的这一块）

最后，除了 $col[1]$ 可以全部合并完（ $sum[col[1]]=n$ ，因为我们从 $1$ 开始向下 dfs），其它节点可能未完全合并，我们通过 $n-sum[i]$ 来计算颜色 $i$ 还未合并的节点数量（这些节点一定是连在一起的）。

分别计算出每一个树块的路径个数，然后用总路径个数减掉即可。



## **AC 代码**

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<set>
using namespace std;

typedef __int64 LL;
typedef set<int> SET;

const int maxn = 210000;
int sum[maxn];
int col[maxn];
SET color;
int sons[maxn];
int n;
LL ans;

struct node
{
    int to;
    int next;
} edge[maxn<<1];
int head[maxn<<1],tot;

void init()
{
    memset(head,-1,sizeof(head));
    memset(sum,0,sizeof(sum));
    tot=ans=0;
    color.clear();
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

void dfs(int u, int fa)
{
    sons[u] = 1;
    sum[col[u]]++;
    for(int i = head[u]; i!=-1; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v != fa)
        {
            int last=sum[col[u]];
            dfs(v, u);
            sons[u] += sons[v];
            LL cnt = sons[v] - sum[col[u]] + last;
            ans-= 1LL * cnt * (cnt - 1) / 2;
            sum[col[u]] += cnt;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int kcase=0;
    while(cin>>n)
    {
        init();
        for(int i=1; i<=n; i++)
        {
            cin>>col[i];
            color.insert(col[i]);
        }
        for(int i=1; i<n; i++)
        {
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs(1,0);
        for(SET::iterator i=color.begin(); i!=color.end(); i++)     //计算那些未完全合并的节点
        {
            int sv=n-sum[*i];
            ans-=1LL*sv*(sv-1)/2;
        }
        ans+=1LL*n*(n-1)/2*color.size();        //总路径
        cout<<"Case #"<<++kcase<<": "<<ans<<endl;
    }
    return 0;
}
```

