# Popular Cows

## **Description**

> Every cow's dream is to become the most popular cow in the herd. In a herd of N (1 <= N <= 10,000) cows, you are given up to M (1 <= M <= 50,000) ordered pairs of the form (A, B) that tell you that cow A thinks that cow B is popular. Since popularity is transitive, if A thinks B is popular and B thinks C is popular, then A will also think that C is popular, even if this is not explicitly specified by an ordered pair in the input. Your task is to compute the number of cows that are considered popular by every other cow. 



## **Input**

> Line 1: Two space-separated integers, N and M 
>
> Lines 2..1+M: Two space-separated numbers A and B, meaning that A thinks B is popular. 



## **Output**

> Line 1: A single integer that is the number of cows who are considered popular by every other cow. 



## **Sample Input**

    3 3
    1 2
    2 1
    2 3



## **Sample Output**

    1



## **题意**

查找图中有多少个点，满足其他所有点都可以直接或者间接到达该点。



## **思路**

首先，我们可以想到，最终的结果可能出现在原图的一个强连通子图中。

因此，对原图进行缩点，缩点以后的图是一个有向无环图，而此时，要想某个节点可以被其他任意点直接或者间接到达，则该点一定可以沿着反向边到达图中任意节点。

于是我们考虑反向建立缩点图，然后寻找一个入度为 $0$ 的点开始 $dfs$ ，若无法到达缩点图中其他所有点，则结果为 $0$ ，否则结果为起始点中所包含的所有原图点的个数。



## **AC 代码**

```cpp
#include<iostream>
#include<cstring>
#include<set>
#include<vector>
using namespace std;

const int maxn = 1e4+10;
const int maxm = 1e5+10;

struct node
{
    int to;
    int next;
} edge[maxm];               //原图
int head[maxn],tot;
int fa[maxn],rk[maxn];
int dfn[maxn],low[maxn],ind;
int Stack[maxn],Stop,Bcnt;
int in[maxn];               //缩点以后反向图的入度
int BcntNum[maxn];          //每个缩点所包含原图点的个数
int color[maxn];            //原图点属于哪一个缩点
bool instack[maxn];
vector<int> G[maxn];        //缩点反向图
set<int> all_node;          //缩点集合
int n,m;

void init()
{
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(instack,false,sizeof(instack));
    memset(rk,0,sizeof(rk));
    memset(in,0,sizeof(in));
    memset(BcntNum,0,sizeof(BcntNum));
    memset(color,0,sizeof(color));
    all_node.clear();
    for(int i=0; i<=n; i++)
        fa[i]=i;
    for(int i=0; i<=n; i++)
        G[i].clear();
    Bcnt = Stop = ind = tot = 0;
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

int find_set(int x)         //并查集查找
{
    if(x!=fa[x])
        fa[x]=find_set(fa[x]);
    return fa[x];
}

void union_set(int x,int y)     //并查集合并
{
    x=find_set(x);
    y=find_set(y);
    if(rk[x]<rk[y])
        fa[x]=y;
    else
    {
        fa[y]=x;
        if(rk[x]==rk[y])
            rk[y]++;
    }
}

void tarjan(int x)
{
    dfn[x]=low[x]=++ind;
    instack[x]=true;
    Stack[++Stop]=x;
    for(int i=head[x]; i!=-1; i=edge[i].next)
    {
        int to=edge[i].to;
        if(!dfn[to])
        {
            tarjan(to);
            if(low[to]<low[x])
                low[x]=low[to];
        }
        else if(instack[to]&&dfn[to]<low[x])
            low[x]=dfn[to];
    }
    if (dfn[x]==low[x]) //相等说明 x 为强连通子图搜索树的根节点
    {
        Bcnt++;
        int top,last = -1;
        do  //退栈
        {
            top=Stack[Stop--];
            if(last == -1) last = top;  //缩点该强连通分量
            else union_set(last,top);
            instack[top]=false;
        }
        while (top!=x);
    }
}

void dfs(int x)         //沿着缩点后的反向图遍历
{
    all_node.erase(color[x]);   //遇到的节点从缩点集合删除
    for(int i=0; i<(int)G[x].size(); i++)
        dfs(G[x][i]);
}

void sub_ans()
{
    int last = -1;
    for(set<int>::iterator i = all_node.begin(); i!=all_node.end(); i++)
        if(in[*i]==0)       //查找入度为 0 的节点
            last = *i;
    dfs(last);
    if(all_node.size())     //如果集合中还有元素，说明从 last 不能遍历到所有元素
        cout<<0<<endl;
    else
        cout<<BcntNum[last]<<endl;
}

void solve()
{
    for(int i=1; i<=n; i++)
        if(!dfn[i])
            tarjan(i);
    for(int i=1; i<=n; i++)
    {
        color[i] = find_set(i);
        all_node.insert(color[i]);
        BcntNum[color[i]]++;
    }
    for(int i=1; i<=n; i++)
    {
        for(int j=head[i]; j!=-1; j=edge[j].next)
        {
            int to = edge[j].to;
            int f1 = find_set(i);
            int f2 = find_set(to);
            if(f1!=f2)
            {
                G[color[to]].push_back(color[i]);   //建立反向缩点图
                in[color[i]]++;
                union_set(f1,f2);   //合并当前这两个集合
            }
        }
    }
    sub_ans();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>n>>m)
    {
        init();
        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            addedge(u,v);
        }
        solve();
    }
    return 0;
}
```

