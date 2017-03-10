# Candies

## **Description**

> During the kindergarten days, flymouse was the monitor of his class. Occasionally the head-teacher brought the kids of flymouse’s class a large bag of candies and had flymouse distribute them. All the kids loved candies very much and often compared the numbers of candies they got with others. A kid A could had the idea that though it might be the case that another kid B was better than him in some aspect and therefore had a reason for deserving more candies than he did, he should never get a certain number of candies fewer than B did no matter how many candies he actually got, otherwise he would feel dissatisfied and go to the head-teacher to complain about flymouse’s biased distribution.
>
> snoopy shared class with flymouse at that time. flymouse always compared the number of his candies with that of snoopy’s. He wanted to make the difference between the numbers as large as possible while keeping every kid satisfied. Now he had just got another bag of candies from the head-teacher, what was the largest difference he could make out of it?



## **Input**

> The input contains a single test cases. The test cases starts with a line with two integers N and M not exceeding 30 000 and 150 000 respectively. N is the number of kids in the class and the kids were numbered 1 through N. snoopy and flymouse were always numbered 1 and N. Then follow M lines each holding three integers A, B and c in order, meaning that kid A believed that kid B should never get over c candies more than he did.



## **Output**

> Output one line with only the largest difference desired. The difference is guaranteed to be finite.



## **Sample Input**

    2 2
    1 2 5
    2 1 4



## **Sample Output**

    5



## **题意**

n个人在一起分糖果，给出m组约束，a、b、c 代表b比a多分的糖果不能超过c个，然后求第n个人比第1个最多多多少个糖果。



## **思路**

差分约束

因为 $XB-XA<=C$ ，所有的不等式加起来便是一个差分约束系统，然后对应的最短路模型为 $d[v]>=d[u]+w$ (u->v) ，计算完最短路径之后便是 $d[v]<=d[u]+w$ ，即 $d[v]-d[u]<=w$ 

于是便出现了和上述不等式相同的模式，有向边从 $A->B$ ，权值为 $C$ 

我们想要求的便是 $XN-X1<=res$ ，即从1到n的最短路径。



不过使用dijkstra算法的时候要加上堆优化，否则会超时。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define INF (1<<25)
#define MAXN 30100

int head[MAXN],tol,dis[MAXN],n,m;
bool vis[MAXN];
typedef pair<int,int> P;

struct edge
{
    int v,cost,next;
} edge[150100];

int dijkstra()
{
    memset(vis,false,sizeof(vis));
    for(int i=1; i<=n; i++) //初始化距离
        dis[i]=INF;
    priority_queue<P,vector<P>,greater<P> >sk;  //小顶堆优化
    dis[1]=0;               //从1出发
    sk.push(P(0,1));
    while(!sk.empty())
    {
        P p=sk.top();
        sk.pop();
        int u=p.second;
        if(vis[u])continue;
        vis[u]=true;
        for(int i=head[u]; i!=-1; i=edge[i].next)   //遍历u的邻接点
        {
            int v=edge[i].v;
            int cost=edge[i].cost;
            if(!vis[v]&&dis[v]>dis[u]+cost)
            {
                dis[v]=dis[u]+cost;
                sk.push(P(dis[v],v));
            }
        }
    }
    return dis[n];
}

void addedge(int from,int to,int val)   //加边
{
    edge[tol].v=to;
    edge[tol].cost=val;
    edge[tol].next=head[from];
    head[from]=tol++;
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,-1,sizeof(head));
        int from,to,val;
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d",&from,&to,&val);
            addedge(from,to,val);
        }
        printf("%d\n",dijkstra());
    }
    return 0;
}
```

