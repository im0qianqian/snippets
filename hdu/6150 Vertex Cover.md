# Vertex Cover

## **Description**

> As we know, minimumvertexcover is a classical NP-complete problem. There will not be polynomial time algorithm for it unless P=NP.
>
> You can see the definition of vertex cover in https://en.wikipedia.org/wiki/Vertex_cover.
>
> Today, little M designs an "approximate" algorithm for vertex cover. It is a greedy algorithm. The main idea of her algorithm is that always choosing the maximum degree vertex into the solution set. The pseudo code of her algorithm is as follows:
>
> We assume that the labels of the vertices are from 1 to n.
>
> ```cpp
> for (int i = 1; i <= n; ++i) {
>   use[i] = false;
>     deg[i] = degree of the vertex i;
> }
> int ans = 0;
> while (true) {
>   int mx = -1, u;
>     for (int i = 1; i <= n; ++i) {
>       if (use[i])
>           continue;
>         if (deg[i] >= mx) {
>           mx = deg[i];
>             u = i;
>         }
>     }
>     if (mx <= 0)
>       break;
>     ++ans;
>     use[u] = true;
>     for (each vertex v adjacent to u)
>       --deg[v];
> }
> return ans;
> ```
>
> As a theory computer scientist, you immediately find that it is a bad algorithm. To show her that this algorithm dose not have a constant approximate factor, you need to construct an instance of vertex cover such that the solution get by this algorithm is much worse than the optimal solution.
>
> Formally, your program need to output a simple undirected graph of at most 500 vertices. Moreover, you need to output a vertex cover solution of your graph. Your program will get Accept if and only if the solution size get by the above algorithm is at least three times as much as yours. 



## **Input**

> There is no input.



## **Output**

> First, output two integer n and m in a line, separated by a space, means the number of the vertices and the number of the edges in your graph.
>
> In the next m lines, you should output two integers u and v for each line, separated by a space, which denotes an edge of your graph. It must be satisfied that 1≤u,v≤n and your graph is a simple undirected graph.
>
> In the next line, output an integer k(1≤k≤n), means the size of your vertex cover solution.
>
> Then output k lines, each line contains an integer u(1≤u≤n) which denotes the label of a vertex in your solution. It must be satisfied that your solution is a vertex cover of your graph.



## **Sample Output**

    4 4
    1 2
    2 3
    3 4
    4 1
    2
    1
    3


## **题意**

在解决最小顶点覆盖问题时有一种贪心算法总是挑选度最大的节点删去，但是这种算法是错误的，我们需要构造一组数据使得其误差至少是正确结果的三倍。



## **思路**

我们把所有的点分成两部分，左边的点为正确结果需要选取的部分，右边的点为贪心算法的结果。

然后对左边的点进行 `n` 次分块，块大小分别为 $1..2..3..n$ 。

对于每一次分得的大小为 $x$ 的块，我们新建右边的一个节点与这 $x$ 个块相连。（如下图所示）

![img](https://www.dreamwings.cn/wp-content/uploads/2017/08/hdu6150.png)

最终的结果是，左边的节点只有一个度为 $n$ 的点，其余节点度都小于 $n$ ，右边也一样，我们看到贪心算法中总是选取度最大编号最大的节点删掉，于是我们在编号时将左边的节点分别编号为 `1-n` ，右边为 `n+1-...` ，这样构建出的图在贪心解法中一定总是选取右边的节点。

接下来便是确定一个合适的 `n` 使得两边点的数量倍数满足题意即可。

**PS：要是这道题出在蓝桥杯的填空题会怎么样呢？**



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+10;
typedef __int64 LL;
typedef pair<int,int> P;
const int mod = 1e9+7;

P e[maxn];
int tot,st;
void solve(int n)
{
    st = n;
    for(int i=2; i<=n; i++)
    {
        for(int j=0; j<n/i*i; j++)
        {
            int fe = j/i;
            e[tot++]=P(j,fe+st);
        }
        st+=n/i;
    }
}

int main()
{
    int n=100;
    solve(n);
    cout<<st<<" "<<tot<<endl;
    for(int i=0; i<tot; i++)
        cout<<e[i].first+1<<" "<<e[i].second+1<<endl;
//    cout<<(st-n)*1.0/n<<endl;
    cout<<n<<endl;
    for(int i=1; i<=n; i++)
        cout<<i<<endl;
    return 0;
}
```

