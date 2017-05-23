# Apple Tree

## **Description**

> Wshxzt is a lovely girl. She likes apple very much. One day HX takes her to an apple tree. There are N nodes in the tree. Each node has an amount of apples. Wshxzt starts her happy trip at one node. She can eat up all the apples in the nodes she reaches. HX is a kind guy. He knows that eating too many can make the lovely girl become fat. So he doesn’t allow Wshxzt to go more than K steps in the tree. It costs one step when she goes from one node to another adjacent node. Wshxzt likes apple very much. So she wants to eat as many as she can. Can you tell how many apples she can eat in at most K steps.



## **Input**

> There are several test cases in the input
>
> Each test case contains three parts.
>
> The first part is two numbers N K, whose meanings we have talked about just now. We denote the nodes by 1 2 ... N. Since it is a tree, each node can reach any other in only one route. (1<=N<=100, 0<=K<=200)
>
> The second part contains N integers (All integers are nonnegative and not bigger than 1000). The ith number is the amount of apples in Node i.
>
> The third part contains N-1 line. There are two numbers A,B in each line, meaning that Node A and Node B are adjacent.
>
> Input will be ended by the end of file.
>
> Note: Wshxzt starts at Node 1.



## **Output**

> For each test case, output the maximal numbers of apples Wshxzt can eat at a line.



## **Sample Input**

    2 1 
    0 11
    1 2
    3 2
    0 1 2
    1 2
    1 3



## **Sample Output**

    11
    2



## **题意**

给你一颗苹果树，每个节点都有相应的苹果，求从节点 `1` 开始最多走 `k` 步，能吃到的最大苹果数。



## **思路**

树形dp，很容易想到 `dp[root][k]` 代表以 `root` 为根，最多走 `k` 步所能得到的最大值。

然后这 `k` 步便可以分配给它的各个子树啦！

如果对于二叉树的话还是比较好解决的，但是对于这道题，我们还要引入另一个状态： `遍历完子树后是否回到根节点`

**我们定义**

`dp[root][k][1]` 代表以 `root` 为根，最多走 `k` 步并且最终回到 `root` 所能得到的最大值。

`dp[root][k][0]` 代表以 `root` 为根，最多走 `k` 步并且最终不回到 `root` 所能得到的最大值。



**于是便有状态转移方程：**

`dp[root][k][0]=max(dp[root][k][0],dp[root][k-s][1]+dp[son][s-1][0]);`

`dp[root][k][0]=max(dp[root][k][0],dp[root][k-s][0]+dp[son][s-2][1]);`

`dp[root][k][1]=max(dp[root][k][1],dp[root][k-s][1]+dp[son][s-2][1]);`

![img](https://www.dreamwings.cn/wp-content/uploads/2017/05/665491174.jpg)

`s` 是我们为当前判断的子节点所分配的步数， `s-1` 是从 `root` 到 `son` 需要一步， `s-2` 是从 `root` 到 `son` ，然后从 `son` 返回到 `root` 需要的两步。



## **AC 代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define INF 0x3f3f3f3f
typedef __int64 LL;

struct node
{
    int u,v,next;
} tree[510];

int head[210];
int cnt;
int n,k;
int dp[210][510][2];
int val[210];

void add(int u,int v)
{
    tree[cnt].u=u;
    tree[cnt].v=v;
    tree[cnt].next=head[u];
    head[u]=cnt++;
}

void dfs(int root,int mark)
{
    for(int i=head[root]; i!=-1; i=tree[i].next)
    {
        int son=tree[i].v;
        if(son==mark)continue;
        dfs(son,root);
        for(int j=k; j>=1; j--)
        {
            for(int s=1; s<=j; s++)
            {
                dp[root][j][0]=max(dp[root][j][0],dp[root][j-s][1]+dp[son][s-1][0]);
                dp[root][j][0]=max(dp[root][j][0],dp[root][j-s][0]+dp[son][s-2][1]);
                dp[root][j][1]=max(dp[root][j][1],dp[root][j-s][1]+dp[son][s-2][1]);
            }
        }
    }
}
int main()
{
    while(~scanf("%d%d",&n,&k))
    {
        memset(dp,0,sizeof(dp));
        memset(head,-1,sizeof(head));
        for(int i=1; i<=n; i++)
        {
            scanf("%d",val+i);
            for(int j=0; j<=k; j++)
                dp[i][j][0]=dp[i][j][1]=val[i];
        }
        cnt=0;
        for(int i=1; i<n; i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            add(a,b);
            add(b,a);
        }
        dfs(1,0);
        printf("%d\n",max(dp[1][k][0],dp[1][k][1]));
    }
    return 0;
}
```

