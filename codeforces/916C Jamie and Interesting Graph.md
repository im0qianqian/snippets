# C. Jamie and Interesting Graph

## **Description**

> Jamie has recently found undirected weighted graphs with the following properties very interesting:
>
> - The graph is connected and contains exactly n vertices and m edges.
> - All edge weights are integers and are in range [1, 10^9] inclusive.
> - The length of shortest path from 1 to n is a prime number.
> - The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
> - The graph contains no loops or multi-edges.
>
> If you are not familiar with some terms from the statement you can find definitions of them in notes section.
>
> Help Jamie construct any graph with given number of vertices and edges that is interesting!



## **Input**

> First line of input contains 2 integers n, m $(2≤n≤10^5, n-1≤m≤\min(\frac{n(n-1)}{2},10^5))$ — the required number of vertices and edges.



## **Output**

> In the first line output 2 integers sp, mstw (1 ≤ sp, mstw ≤ 10^14) — the length of the shortest path and the sum of edges' weights in the minimum spanning tree.
>
> In the next m lines output the edges of the graph. In each line output 3 integers u, v, w (1 ≤ u, v ≤ n, 1 ≤ w ≤ 10^9) describing the edge connecting u and v and having weight w.



## **Examples input**

    4 4


## **Examples output**

    7 7
    1 2 3
    2 3 2
    3 4 2
    2 4 4



## **题意**

构造一张包含 n 个点， m 条边的简单图，使得从 1 -> n 的最短路径以及图的最小生成树边权和都为素数。



## **思路**

我们可以构造图的最小生成树为一条链，即 1 -> 2 -> 3 ... -> n，在链中有 n-2 条边权值为 1，而另一条边刚好补充使得整个边权和为一个素数。

此外，对于剩余的边就可以随意连接了，只需保证它不会破坏我们之前所构造的 MST 即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 3e5+10;

int n,m;
const int prime = 1e5+3;

int main()
{
    IO;
    cin>>n>>m;
    int last = m - n + 1;
    cout<<prime<<" "<<prime<<endl;
    cout<<"1 2 "<<prime - n + 2<<endl;
    for(int i=2; i<=n-1; i++)
        cout<<i<<" "<<i+1<<" "<<1<<endl;
    for(int i=1; i<=n-1; i++)
        for(int j=i+2; j<=n; j++)
        {
            if(last--==0)
                return 0;
            cout<<i<<" "<<j<<" "<<(prime<<1)<<endl;
        }
    return 0;
}
```

