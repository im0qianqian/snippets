# **HDU 3394 Railway**

## **Problem Description**

> There are some locations in a park, and some of them are connected by roads. The park manger needs to build some railways along the roads, and he would like to arrange tourist routes to each circuit. If a railway belongs to more than one tourist routes, there might be clash on it, and if a railway belongs to none tourist route, it doesn’t need to build.
>
> Now we know the plan, and can you tell us how many railways are no need to build and how many railways where clash might happen.



## **Input**

> The Input consists of multiple test cases. The first line of each test case contains two integers, n (0 < n <= 10000), m (0 <= m <= 100000), which are the number of locations and the number of the railways. The next m lines, each line contains two integers, u, v (0 <= u, v < n), which means the manger plans to build a railway on the road between u and v.
>
> You can assume that there is no loop and no multiple edges.
>
> The last test case is followed by two zeros on a single line, which means the end of the input.



## **Output**

> Output the number of railways that are no need to build, and the number of railways where clash might happen. Please follow the format as the sample.



## **Sample Input**

    8 10
    0 1
    1 2
    2 3
    3 0
    3 4
    4 5
    5 6
    6 7
    7 4
    5 7
    0 0



## **Sample Output**

    1 5


## **题意**

公园有n个景点，管理员计划要建m条道路，并且安排一些形成回路的参观路径，如果一条道路可以被多条回路共用，那么这条边是冲突边，如果一个块中有多个环，则该块中的每条边都是冲突边。

如果不能形成环的路则为不需要的边，求无向图中冲突边与不需要边的个数。



## **思路**

照着样例数据画一张图，我们可以发现，多余边不在任何一个环中，因此多余边一定是桥，对于多余边，只需要统计图中桥的个数便可。

而对于冲突边，因为它在多个环的共同边里面，因此我们可以把图分成多个块，然后判断每个块中的边数，如果块的边数等于块的点数，则该块只存在一个环，如果边数大于点数，说明这个块中有多个环，并且块的每条边都是多个环里面的一部分。

其实在这里，边数如果小于点数的话，说明当前块中只有两个点(因为不含有环)，并且唯一一条边为桥。(按照定义理解好像是这样，如果有错，还请指点，具体实现看代码部分！)



## **AC代码**

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#define max 10010
using namespace std;

vector <int> edge[max]; //邻接表
int stack[max],stop;    //工作栈
int block[max];         //联通分量各点标号，其中block[0]为环的点的总数
int low[max];           //记录当前搜索的强连通子图搜索树的根节点
int dfn[max];           //记录搜索到该点的时间
int ans1,ans2,n,m;
int Dindex;             //一个计数器，记录访问节点的次序
bool inbox[max];        //是否在同一个子图内

void init()
{
    memset(dfn,0,sizeof(dfn));
    for(int i=0; i<max; i++)
        edge[i].clear();
    stop=Dindex=ans1=ans2=0;
}

void deal_circle()
{
    int num=0;
    for(int i=1; i<=block[0]; i++)  //遍历所有点
    {
        for(int j=0; j<(int)edge[block[i]].size(); j++) //遍历所有点所邻接的点
        {
            int v=edge[block[i]][j];
            if(inbox[v])
                num++;    //如果v属于当前块，则将边数累加一次
        }
    }
    num/=2; //因为每条边的顶点有两个，且都属于该块中，所以每条边被重复计算了一次
    if(block[0]>num)    //如果块的边数大于点的个数，则这个块中有多个环
        ans1+=num;
    else if(block[0]<num)   //如果块的边数小于点个数，说明块中没有环(因为算法的关系，只会出现两个点并且无环的块，其他情况都会在之前的递归中排除)
        ans2+=num;
}
void tarjan(int u)
{
    dfn[u]=low[u]=++Dindex;
    stack[++stop]=u;
    for(int i=0; i<(int)edge[u].size(); i++)
    {
        int v=edge[u][i];
        if(!dfn[v])    //如果邻接的该点没有被标记
        {
            tarjan(v);
            low[u]=min(low[u], low[v]); //如果邻接点搜索结束后LOW更小，说明在v中找到一个环，然后使环中所有LOW统一
            if(low[v]>=dfn[u])  //说明u的子节点没有与u的祖先相连的后向边，即u为割点
            {
                block[0]=0;
                memset(inbox,false,sizeof(inbox));
                int top;
                do
                {
                    top=stack[stop--];
                    block[++block[0]]=top;  //退栈出的元素在同一个块中
                    inbox[top]=true;
                }
                while(v!=top);
                block[++block[0]]=u;    //在子图中加入u，整个子图构成块
                inbox[u]=true;
                deal_circle();
            }
        }
        else    //找到一個环
            low[u]=min(dfn[v], low[u]);
    }
}

int main()
{
    int a, b;
    while(~scanf("%d%d",&n,&m) && (n||m) )
    {
        init();
        for(int i=0; i<m; i++)
        {
            scanf("%d%d",&a,&b);
            edge[a].push_back(b);   //加入一双向边
            edge[b].push_back(a);
        }
        for(int i=0; i<n; i++)
            if(!dfn[i])
                tarjan(i);
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
```

