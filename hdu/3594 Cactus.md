# Cactus

## **Description**

> 1. It is a Strongly Connected graph.
>
> 2. Each edge of the graph belongs to a circle and only belongs to one circle.
>
> We call this graph as CACTUS.
>
> ![img](http://acm.hdu.edu.cn/data/images/C306-1002-1.jpg)
>
>
> There is an example as the figure above. The left one is a cactus, but the right one isn’t. Because the edge (0, 1) in the right graph belongs to two circles as (0, 1, 3) and (0, 1, 2, 3).



## **Input**

> The input consists of several test cases. The first line contains an integer T (1<=T<=10), representing the number of test cases.
>
> For each case, the first line contains a integer n (1<=n<=20000), representing the number of points.
>
> The following lines, each line has two numbers a and b, representing a single-way edge (a->b). Each case ends with (0 0).
>
> Notice: The total number of edges does not exceed 50000.



## **Output**

> For each case, output a line contains “YES” or “NO”, representing whether this graph is a cactus or not.

 

## **Sample Input**

    2
    4
    0 1
    1 2
    2 0
    2 3
    3 2
    0 0
    4
    0 1
    1 2
    2 3
    3 0
    1 3
    0 0



## **Sample Output**

    YES
    NO



## **题意**

给出一张有向图，判断其是否是仙人掌图。



## **思路**

在解决这道题之前我们首先要知道什么是仙人掌图。

直观的说，仙人掌图就是一个一个的圈直接“粘”在一起的图，圈之间没有公共边。

**我们主要根据其以下三点性质来做出判断：**

1. 仙人掌图的 DFS 树没有横向边
2. `Low(u)<=DFN(v)` （u 是 v 的儿子）
3. 设某个点 v 有 a(v) 个儿子的 Low 值小于 DFN(v) ，同时 v 自己有 b(v) 条逆向边，那么 `a(v)+b(v)<2`

而 `LOW` 与 `DFN` 之前我们所学习的 [Tarjan](https://www.dreamwings.cn/tarjan/3992.html) 算法中已经遇到了，直接拿来改改就可以了。



## **AC 代码**

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<map>
using namespace std;

const int maxn = 51000;
int DFN[maxn];          //记录搜索到该点的时间
int LOW[maxn];          //记录当前搜索的强连通子图搜索树的根节点
int Stack[maxn],Stop;   //工作栈
int Dindex;             //一个计数器，记录访问节点的次序
bool instack[maxn];     //记录当前点是否在栈中
bool ans;

struct node
{
    int to;
    int next;
} edge[maxn];
int head[maxn],tot,n;

void init()
{
    memset(head,-1,sizeof(head));
    memset(DFN,0,sizeof(DFN));
    memset(instack,false,sizeof(instack));
    tot=Dindex=Stop=0;
    ans=true;
}

void addedge(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

void tarjan(int i)
{
    DFN[i]=LOW[i]=++Dindex;
    instack[i]=true;
    Stack[++Stop]=i;
    int cnt=0;
    for(int k=head[i]; k!=-1; k=edge[k].next)
    {
        int j=edge[k].to;
        if (!DFN[j])    //如果邻接的该点没有被标记
        {
            tarjan(j);
            if (LOW[j]<LOW[i])  //如果邻接点搜索结束后LOW更小，说明在j中找到一个环，然后使环中所有LOW统一
                LOW[i]=LOW[j];
        }
        else if (instack[j] && DFN[j]<LOW[i])   //找到一个环
            LOW[i]=DFN[j];
        else if(!instack[j])    //第一条性质
        {
            ans=false;
            return;
        }
        if(LOW[j]>DFN[i])       //仙人掌第二条性质
        {
            ans=false;
            return;
        }
        if(DFN[j]<DFN[i]||(DFN[j]>DFN[i]&&LOW[j]<LOW[i]))   //仙人掌第三条性质
            cnt++;
    }
    if(cnt>1)
    {
        ans=false;
        return;
    }
    if (DFN[i]==LOW[i]) //相等说明i为强连通子图搜索树的根节点
    {
        int top;
        do  //退栈
        {
            top=Stack[Stop--];
            instack[top]=false;
        }
        while (top!=i);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)
    {
        init();
        cin>>n;
        while(true)
        {
            int a,b;
            cin>>a>>b;
            if(a==0&&b==0)break;
            addedge(a,b);
        }
        tarjan(0);
        cout<<(ans?"YES":"NO")<<endl;
    }
    return 0;
}
```

