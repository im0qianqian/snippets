# D. Substring

## **Description**

> You are given a graph with n nodes and m directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is 3. Your task is find a path whose value is the largest.



## **Input**

> The first line contains two positive integers n, m (1 ≤ n, m ≤ 300 000), denoting that the graph has n nodes and m directed edges.
>
> The second line contains a string s with only lowercase English letters. The i-th character is the letter assigned to the i-th node.
>
> Then m lines follow. Each line contains two integers x, y (1 ≤ x, y ≤ n), describing a directed edge from x to y. Note that x can be equal to y and there can be multiple edges between x and y. Also the graph can be not connected.



## **Output**

> Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.



## **Examples input**

    5 4
    abaca
    1 2
    1 3
    3 4
    4 5



## **Examples output**

    3



## **题意**

在图中找一条路径，满足该路径上某字母的出现频率最高，输出该字母的出现次数。（图中可能存在自环以及重边）



## **思路**

记忆化搜索， $dp[o][ch]$ 代表节点 $o$ 及以下字符 $ch$ 出现的最大次数。

tarjan 判环，注意存在自环情况。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 3e5+10;
const int mod = 1e9+7;
typedef __int64 LL;
#define inf 0x7f7f7f

struct node
{
    int to;
    int next;
} edge[maxn];
int head[maxn],tot,dfn[maxn],low[maxn];
int dp[maxn][26],idx;
int ch[maxn],in[maxn];
bool instack[maxn];
int Stack[maxn],top;
int n,m;
bool flag;
char str[maxn];
void init()
{
    memset(dp,0,sizeof dp);
    memset(dfn,0,sizeof dfn);
    memset(low,0,sizeof low);
    memset(instack,false,sizeof instack);
    memset(head,-1,sizeof head);
    top = idx = tot = 0;
    flag = true;
}

void addedge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int x)
{
    dfn[x] = low[x] = ++idx;
    instack[x] = true;
    Stack[top++] = x;
    for(int i=head[x]; i!=-1; i=edge[i].next)
    {
        int to = edge[i].to;
        if(!dfn[to])
        {
            dfs(to);
            low[x] = min(low[x],low[to]);
        }
        else if(instack[to] && dfn[to]<low[x])
            low[x] = dfn[to];
        for(int j=0; j<26; j++)
            dp[x][j] = max(dp[x][j],dp[to][j]);
    }
    if(dfn[x]==low[x])
    {
        int Size = 0,now;
        do
        {
            now = Stack[--top];
            instack[now] = false;
            ++Size;
        }
        while(now!=x);
        if(Size>1)
            flag = false;
    }
    if(!flag)
        return;
    ++dp[x][ch[x]];
}

void solve()
{
    for(int i=1; i<=n; i++)
        ch[i] = str[i-1] - 'a';
    int ans = -1;
    for(int i=1; i<=n; i++)
        if(in[i]==0)
        {
            dfs(i);
            for(int j=0; j<26; j++)
                ans = max(ans,dp[i][j]);
        }
    cout<<(flag?ans:-1)<<endl;
}

int main()
{
    IO;
    init();
    cin>>n>>m;
    cin>>str;
    for(int i=0; i<m; i++)
    {
        int u,v;
        cin>>u>>v;
        if(u==v)
            flag = false;
        ++in[v];
        addedge(u,v);
    }
    solve();
    return 0;
}
```

