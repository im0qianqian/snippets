# C. Ilya And The Tree

## **Description**

> Ilya is very fond of graphs, especially trees. During his last trip to the forest Ilya found a very interesting tree rooted at vertex 1. There is an integer number written on each vertex of the tree; the number written on vertex i is equal to ai.
>
> Ilya believes that the beauty of the vertex x is the greatest common divisor of all numbers written on the vertices on the path from the root to x, including this vertex itself. In addition, Ilya can change the number in one arbitrary vertex to 0 or leave all vertices unchanged. Now for each vertex Ilya wants to know the maximum possible beauty it can have.
>
> For each vertex the answer must be considered independently.
>
> The beauty of the root equals to number written on it.



## **Input**

> First line contains one integer number n — the number of vertices in tree (1 ≤ n ≤ 2·10^5).
>
> Next line contains n integer numbers ai (1 ≤ i ≤ n, 1 ≤ ai ≤ 2·10^5).
>
> Each of next n - 1 lines contains two integer numbers x and y (1 ≤ x, y ≤ n, x ≠ y), which means that there is an edge (x, y) in the tree.



## **Output**

> Output n numbers separated by spaces, where i-th number equals to maximum possible beauty of vertex i.



## **Sample Input**

    3
    6 2 3
    1 2
    1 3



## **Sample Output**

    6 6 6 



## **题意**

一棵根节点为 1 的树，每个节点都有权值，求从根节点到每个点路径所有权值的最大 gcd 。（我们可以把每条路径上一个点的权值变为 0 ）



## **思路**

**显然，我们可以通过 dfs 来求解这个问题。**

对于每一个点 x ，其结果是一个集合。

- 我们可以不选择 x （权值变为 0 ），此时到这里的贡献为从根节点到当前位置除 x 以外所有数的 gcd ；
- 我们也可以选择 x ，此时的贡献有：
  - 从根节点到当前位置所有数的 gcd
  - 当前数与其父节点所有符合条件的值计算 gcd

然后对于每一个数所拥有的一个集合，取最大值输出即可。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;

int a[maxn],n;
vector<int>g[maxn];
set<int>s[maxn];

void dfs(int x,int fa,int now)
{
    for(auto p:s[fa])
        s[x].insert(__gcd(p,a[x]));
    s[x].insert(now);       //当前点置零
    now=__gcd(now,a[x]);
    s[x].insert(now);       //当前点保留
    for(auto p:g[x])
        if(p!=fa)
            dfs(p,x,now);
}

int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",a+i);
    int u,v;
    for(int i=1; i<n; i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0,0);
    for(int i=1; i<=n; i++)
        printf("%d ",*s[i].rbegin());
    return 0;
}
```

