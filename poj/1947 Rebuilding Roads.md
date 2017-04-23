# Rebuilding Roads

## **Description**

> The cows have reconstructed Farmer John's farm, with its N barns (1 <= N <= 150, number 1..N) after the terrible earthquake last May. The cows didn't have time to rebuild any extra roads, so now there is exactly one way to get from any given barn to any other barn. Thus, the farm transportation system can be represented as a tree. 
>
> Farmer John wants to know how much damage another earthquake could do. He wants to know the minimum number of roads whose destruction would isolate a subtree of exactly P (1 <= P <= N) barns from the rest of the barns.



## **Input**

> Line 1: Two integers, N and P 
>
> Lines 2..N: N-1 lines, each with two integers I and J. Node I is node J's parent in the tree of roads. 



## **Output**

> A single line containing the integer that is the minimum number of roads that need to be destroyed for a subtree of P nodes to be isolated. 



## **Sample Input**

    11 6
    1 2
    1 3
    1 4
    1 5
    2 6
    2 7
    2 8
    4 9
    4 10
    4 11



## **Sample Output**

    2



## **题意**

给出一棵树，问现在要得到一颗有 `p` 个节点的子树，至少需要切除几条边？



## **思路**

`dp[root][i]` 代表以 `root` 为根节点的子树中保留 `i` 个节点所要切除的最小边数。

在我们遍历 `root` 的子节点 `son` 时，可以考虑切除 `son` ，此时仍为 `dp[root][i]` ；也可以考虑保留 `son` 以及其下 `s` 个节点，此时 `dp[root][i]=dp[root][i-s]+dp[son][s]-1` （减一是因为本来两颗子树是独立的，我们现在要把它们合并需要添加一条边）。

**于是便得到了状态转移方程：** `dp[root][i]=min(dp[root][i-s]+dp[son][s]-1,dp[root][i])`

初始化 `dp[root][1]` 为其子节点的个数，因为我们所定义的这颗子树必含根节点。



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define INF 0x3f3f3f3f
typedef __int64 LL;

const int maxn = 200;
struct node
{
    int u;
    int v;
    int next;
} a[maxn];
int head[maxn],cnt;
int dp[maxn][maxn];     //dp[root][j] 代表以 root 为根的子树保留 j 个节点所需要的最小切割次数
int num[maxn];

void addedge(int u,int v)   // 链式前向星建图
{
    a[cnt].u=u;
    a[cnt].v=v;
    a[cnt].next=head[u];
    head[u]=cnt++;
}
int n,p;

int dfs(int x)
{
    int sum=1;
    for(int i=head[x]; i!=-1; i=a[i].next)  // 遍历子节点
    {
        int son=a[i].v;
        sum+=dfs(son);  // 求当前已知节点的个数
        for(int j=sum; j>0; j--)    // 计算 dp[x][j]
            for(int s=1; s<j; s++)  // 分配 s 个节点给 dfs 出的新枝
                dp[x][j]=min(dp[x][j-s]+dp[son][s]-1,dp[x][j]);
    }
    return sum;
}

void init()
{
    memset(head,-1,sizeof(head));
    memset(dp,INF,sizeof(dp));
    memset(num,0,sizeof(num));
    cnt=0;
}

int main()
{
    while(~scanf("%d%d",&n,&p))
    {
        init();
        for(int i=1; i<n; i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            addedge(a,b);
            num[a]++;   // 求点的出度
        }
        for(int i=1; i<=n; i++)
            dp[i][1]=num[i];
        dfs(1);
        int ans=dp[1][p];
        for(int i=2; i<=n; i++)
            ans=min(ans,dp[i][p]+1);
        printf("%d\n",ans);
    }
    return 0;
}
```

