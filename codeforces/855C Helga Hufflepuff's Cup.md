# C. Helga Hufflepuff's Cup

## **Description**

> Harry, Ron and Hermione have figured out that Helga Hufflepuff's cup is a horcrux. Through her encounter with Bellatrix Lestrange, Hermione came to know that the cup is present in Bellatrix's family vault in Gringott's Wizarding Bank.
>
> The Wizarding bank is in the form of a tree with total n vaults where each vault has some type, denoted by a number between 1 to m. A tree is an undirected connected graph with no cycles.
>
> The vaults with the highest security are of type k, and all vaults of type k have the highest security.
>
> There can be at most x vaults of highest security.
>
> Also, if a vault is of the highest security, its adjacent vaults are guaranteed to not be of the highest security and their type is guaranteed to be less than k.
>
> Harry wants to consider every possibility so that he can easily find the best path to reach Bellatrix's vault. So, you have to tell him, given the tree structure of Gringotts, the number of possible ways of giving each vault a type such that the above conditions hold.



## **Input**

> The first line of input contains two space separated integers, n and m — the number of vaults and the number of different vault types possible. (1 ≤ n ≤ 10^5, 1 ≤ m ≤ 10^9).
>
> Each of the next n - 1 lines contain two space separated integers ui and vi (1 ≤ ui, vi ≤ n) representing the i-th edge, which shows there is a path between the two vaults ui and vi. It is guaranteed that the given graph is a tree.
>
> The last line of input contains two integers k and x (1 ≤ k ≤ m, 1 ≤ x ≤ 10), the type of the highest security vault and the maximum possible number of vaults of highest security.



## **Output**

> Output a single integer, the number of ways of giving each vault a type following the conditions modulo 10^9 + 7.



## **Examples input**

    4 2
    1 2
    2 3
    1 4
    1 2



## **Examples output**

    1



## **题意**

给你一棵树，可以染 $m$ 种颜色，现定义一种特殊的颜色 $K$ ，一棵树上最多能有 $X$ 个特殊颜色。如果一个节点为特殊颜色 $K$ ，那么他相邻的节点的值只能选比 $K$ 小的颜色，问一共有多少种染色方案。



## **思路**

$dp[i][j][k]$ 代表以 $i$ 为根的子树中共选择了 $j$ 个特殊颜色，且当前节点 $i$ 的状态为 $k$ 的染色方案数。

对于 $k$ 有三种情况：

1. $k=0$ ，代表当前节点 $i$ 的颜色值小于 $K$ 。
2. $k=1$ ，代表当前节点 $i$ 的颜色值等于 $K$ 。
3. $k=2$ ，代表当前节点 $i$ 的颜色值大于 $K$ 。

显然，很容易得出状态转移方程（因为直接更新会影响当前这一轮的求值，因此我们用 $tmp[j][k]$ 做临时结果存储）：

for j in 0 -> sz[x]:

​    for k in 0 -> sz[to]:

其中 `0 -> sz[x]` 代表当前子树中之前访问过的节点数目， `0 -> sz[to]` 代表这一轮访问的子子树中的节点数目。

**因此，我们有**

$tmp[j+k][0]+=dp[x][j][0] \times (dp[to][k][0]+dp[to][k][1]+dp[to][k][2])%mod$

$tmp[j+k][1] += dp[x][j][1] \times dp[to][k][0]%mod$

$tmp[j+k][2] += dp[x][j][2] \times (dp[to][k][0]+dp[to][k][2])%mod$

上面的状态转移方程挺好理解的，主要是控制了当一个节点是特殊颜色时它相邻节点的状态，然后用乘法原理得出贡献。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int maxm = 20;
const int mod = 1e9+7;
typedef long long LL;

struct node
{
    int to;
    int next;
} edge[maxn<<1];

int head[maxn],tot;
int n,m;
int K,X;
LL dp[maxn][maxm][3];
int sz[maxn];
int tmp[maxm][3];

void init()
{
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    tot=0;
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

void dfs(int x,int fa)
{
    dp[x][0][0] = K-1;
    dp[x][1][1] = 1;
    dp[x][0][2] = m-K;
    sz[x] = 1;
    for(int i=head[x]; i!=-1; i=edge[i].next)
    {
        int to=edge[i].to;
        if(to == fa)continue;
        dfs(to,x);
        memset(tmp,0,sizeof(tmp));
        for(int j=0; j<=sz[x]; j++)
        {
            for(int k=0; k<=sz[to]; k++)
            {
                if(j+k>X) continue;
                tmp[j+k][0] += dp[x][j][0]*(dp[to][k][0]+dp[to][k][1]+dp[to][k][2])%mod;
                tmp[j+k][0]%=mod;
                tmp[j+k][1] += dp[x][j][1]*dp[to][k][0]%mod;
                tmp[j+k][1]%=mod;
                tmp[j+k][2] += dp[x][j][2]*(dp[to][k][0]+dp[to][k][2])%mod;
                tmp[j+k][2]%=mod;
            }
        }
        sz[x] = min(sz[x]+sz[to],X);
        for(int j=0; j<=sz[x]; j++)
            for(int k=0; k<3; k++)
                dp[x][j][k] = tmp[j][k];
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while(cin>>n>>m)
    {
        init();
        for(int i=1; i<n; i++)
        {
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        cin>>K>>X;
        dfs(1,0);
        LL ans = 0;
        for(int i=0; i<=X; i++)
            for(int j=0; j<3; j++)
                ans = (ans+dp[1][i][j])%mod;
        cout<<ans<<endl;
    }
    return 0;
}
```

