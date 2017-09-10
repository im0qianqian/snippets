# Aragorn's Story

## **Problem Description**

> Our protagonist is the handsome human prince Aragorn comes from The Lord of the Rings. One day Aragorn finds a lot of enemies who want to invade his kingdom. As Aragorn knows, the enemy has N camps out of his kingdom and M edges connect them. It is guaranteed that for any two camps, there is one and only one path connect them. At first Aragorn know the number of enemies in every camp. But the enemy is cunning , they will increase or decrease the number of soldiers in camps. Every time the enemy change the number of soldiers, they will set two camps C1 and C2. Then, for C1, C2 and all camps on the path from C1 to C2, they will increase or decrease K soldiers to these camps. Now Aragorn wants to know the number of soldiers in some particular camps real-time.



## **Input**

> Multiple test cases, process to the end of input.
>
> For each case, The first line contains three integers N, M, P which means there will be N(1 ≤ N ≤ 50000) camps, M(M = N-1) edges and P(1 ≤ P ≤ 100000) operations. The number of camps starts from 1.
>
> The next line contains N integers A1, A2, ...AN(0 ≤ Ai ≤ 1000), means at first in camp-i has Ai enemies.
>
> The next M lines contains two integers u and v for each, denotes that there is an edge connects camp-u and camp-v.
>
> The next P lines will start with a capital letter 'I', 'D' or 'Q' for each line.
>
> 'I', followed by three integers C1, C2 and K( 0≤K≤1000), which means for camp C1, C2 and all camps on the path from C1 to C2, increase K soldiers to these camps.
>
> 'D', followed by three integers C1, C2 and K( 0≤K≤1000), which means for camp C1, C2 and all camps on the path from C1 to C2, decrease K soldiers to these camps.
>
> 'Q', followed by one integer C, which is a query and means Aragorn wants to know the number of enemies in camp C at that time.



## **Output**

> For each query, you need to output the actually number of enemies in the specified camp.



## **Sample Input**

    3 2 5
    1 2 3
    2 1
    2 3
    I 1 3 5
    Q 2
    D 1 2 2
    Q 1 
    Q 3



## **Sample Output**

    7
    4
    8



## **题意**

在一棵树中，我们定义了两种操作：

1. 给树中 `u->v` 路径上的所有点的权值增加或减少 `k`
2. 查询树中的某一个点的当前权值



## **思路**

基础的树链剖分题目，先对树进行剖分，然后用线段树或者树状数组等去维护这些链。

树状数组的话我们可以利用区间减法的性质，把对一个区间 `[a,b]` 的更新拆解成对两个区间 `[0,a]、[0,b]` 相反的更新。



## **AC 代码**

```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long LL;
const int maxn = 50010;

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
int w[maxn];

int ad[maxn<<2];    //树状数组
int n;              //节点数目

void init()
{
    memset(head,-1,sizeof(head));
    memset(son,-1,sizeof(son));
    tot=0;
    pos=1;          //因为使用树状数组，所以我们pos初始值从1开始
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

int lowbit(int x)
{
    return x&-x;
}

int query(int i)                        //查询
{
    int s=0;
    while(i>0)
    {
        s+=ad[i];
        i-=lowbit(i);
    }
    return s;
}

void add(int i,int val)                 //增加
{
    while(i<=n)
    {
        ad[i]+=val;
        i+=lowbit(i);
    }
}

void update(int u,int v,int val)
{
    int f1=top[u],f2=top[v];
    while(f1!=f2)
    {
        if(deep[f1]<deep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        add(p[f1],val);   //因为区间减法成立，所以我们把对某个区间[f1,u] 的更新拆分为 [0,f1] 和 [0,u] 的操作
        add(p[u]+1,-val);
        u=fa[f1];
        f1=top[u];
    }
    if(deep[u]>deep[v])
        swap(u,v);
    add(p[u],val);
    add(p[v]+1,-val);
}


int main()
{
    ios::sync_with_stdio(false);
    int m,ps;
    while(cin>>n>>m>>ps)
    {
        int a,b,c;
        for(int i=1; i<=n; i++)
            cin>>w[i];
        init();
        for(int i=0; i<m; i++)
        {
            cin>>a>>b;
            addedge(a,b);
            addedge(b,a);
        }
        dfs1(1,0,0);
        dfs2(1,1);
        memset(ad,0,sizeof(ad));
        for(int i=1; i<=n; i++)
        {
            add(p[i],w[i]);
            add(p[i]+1,-w[i]);
        }
        for(int i=0; i<ps; i++)
        {
            char op;
            cin>>op;
            if(op=='Q')
            {
                cin>>a;
                cout<<query(p[a])<<endl;
            }
            else
            {
                cin>>a>>b>>c;
                if(op=='D')c=-c;
                update(a,b,c);
            }
        }
    }
    return 0;
}
```

