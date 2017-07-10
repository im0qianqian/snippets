# QTREE - Query on a tree

## **Description**

> You are given a tree (an acyclic undirected connected graph) with N nodes, and edges numbered 1, 2, 3...N-1. 
>
> We will ask you to perfrom some instructions of the following form:
>
> - CHANGE i ti : change the cost of the i-th edge to ti
> - QUERY a b : ask for the maximum edge cost on the path from node a to node b 



## **Input**

> The first line of input contains an integer t, the number of test cases (t <= 20). t test cases follow. 
>
> For each test case:
>
> - In the first line there is an integer N (N <= 10000), 
> - In the next N-1 lines, the i-th line describes the i-th edge: a line with three integers a b c denotes an edge between a, b of cost c (c <= 1000000), 
> - The next lines contain instructions "CHANGE i ti" or "QUERY a b", 
> - The end of each test case is signified by the string "DONE". 
>
> There is one blank line between successive tests. 



## **Output**

> For each "QUERY" operation, write one integer representing its result.



## **Example**

    Input:
    1
    
    3
    1 2 1
    2 3 2
    QUERY 1 2
    CHANGE 1 3
    QUERY 1 2
    DONE
    
    Output:
    1
    3



## **题意**

给出一棵树，有两种操作：修改边权与查询 `u->v` 路径边权最大值。



## **思路**

树链剖分，将树剖分为若干条链，利用线段树去维护每一条链即可。（以后在其他文章中介绍这种算法）



## **AC 代码**

```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 10010;
struct Edge
{
    int to;
    int next;
} edge[maxn<<1];

int head[maxn],tot; //链式前向星存储
int top[maxn];      //v所在重链的顶端节点
int fa[maxn];       //父亲节点
int deep[maxn];     //节点深度
int num[maxn];      //以v为根的子树节点数
int p[maxn];        //v与其父亲节点的连边在线段树中的位置
int fp[maxn];       //与p[]数组相反
int son[maxn];      //重儿子
int pos;
int e[maxn][3];

void init()
{
    memset(head,-1,sizeof(head));
    memset(son,-1,sizeof(son));
    tot=0;
    pos=0;
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

void dfs1(int u,int pre,int d)         //第一遍dfs，求出 fa,deep,num,son (u为当前节点,pre为其父节点,d为深度)
{
    deep[u]=d;
    fa[u]=pre;
    num[u]=1;
    for(int i=head[u]; i!=-1; i=edge[i].next)   //遍历u的邻接点
    {
        int v=edge[i].to;
        if(v!=pre)
        {
            dfs1(v,u,d+1);
            num[u]+=num[v];
            if(son[u]==-1||num[v]>num[son[u]])  //寻找重儿子
                son[u]=v;
        }
    }
}

void dfs2(int u,int sp)                 //第二遍dfs，求出 top,p
{
    top[u]=sp;
    p[u]=pos++;
    fp[p[u]]=u;
    if(son[u]!=-1)                      //如果当前点存在重儿子，继续延伸形成重链
        dfs2(son[u],sp);
    else return;
    for(int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].to;
        if(v!=son[u]&&v!=fa[u])         //遍历所有轻儿子新建重链
            dfs2(v,v);
    }
}

int maxx[maxn<<2],dep=1;                //存储线段树各节点的值以及最底层元素个数

void build()           //一棵完美二叉树的初始化
{
    while(dep<pos)
        dep<<=1;
    memset(maxx,0,sizeof(maxx));
}

void update(int o,int val)              //自底向上更新数据
{
    o+=dep;
    maxx[o]=val;
    while(o>1)
    {
        o>>=1;
        maxx[o]=max(maxx[o<<1],maxx[(o<<1)^1]);
    }
}

int query(int a,int b,int k,int l,int r)    //查询[a,b]最大值，[l,r]为当前查询区间，k为当前所在节点
{
    if(r<a||b<l)return 0;                   //如果当前查询区间与[a,b]交集为空，返回0
    if(a<=l&&b>=r)return maxx[k];           //如果[a,b]包含[l,r]返回当前节点的值
    else
    {
        int v1=query(a,b,k<<1,l,(l+r)>>1);  //左子树
        int v2=query(a,b,(k<<1)^1,((l+r)>>1)+1,r);  //右子树
        return max(v1,v2);
    }
}

int find(int u,int v)
{
    int f1=top[u],f2=top[v];
    int tmp=0;
    while(f1!=f2)
    {
        if(deep[f1]<deep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        tmp=max(tmp,query(p[f1],p[u],1,0,dep-1));
        u=fa[f1];
        f1=top[u];
    }
    if(u==v)return tmp;
    if(deep[u]>deep[v])swap(u,v);
    return max(tmp,query(p[son[u]],p[v],1,0,dep-1));
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        init();
        for(int i=0; i<n-1; i++)
        {
            for(int j=0; j<3; j++)
                cin>>e[i][j];
            addedge(e[i][0],e[i][1]);
            addedge(e[i][1],e[i][0]);
        }
        dfs1(1,0,0);
        dfs2(1,1);
        build();
        for(int i=0; i<n-1; i++)
        {
            if(deep[e[i][0]]>deep[e[i][1]])
                swap(e[i][0],e[i][1]);
            update(p[e[i][1]],e[i][2]);
        }
        char op[10];
        while(cin>>op)
        {
            if(op[0]=='D')break;
            int a,b;
            cin>>a>>b;
            if(op[0]=='C')
                update(p[e[a-1][1]],b);
            else if(op[0]=='Q')
                cout<<find(a,b)<<endl;
        }
    }
    return 0;
}
```

