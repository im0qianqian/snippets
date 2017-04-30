# Proxy

## **Problem Description**

> Because of the GFW (Great Firewall), we cannot directly visit many websites, such as Facebook, Twitter, YouTube, etc. But with the help of proxy and proxy server, we can easily get to these website.
>
> You have a list of several proxy servers, some of them can be connected directly but others can’t. But you can visit proxy servers through other proxy server by a one-way connection. 
>
> As we all know, the lag of internet visit will decide our feelings of the visit. You have a very smart proxy software which will find the least lag way to reach the website once you choose a directly reachable proxy server. 
>
> You know the lag of every connection. The lag of your visit is the all the lags in your whole connection. You want to minimize the lag of visit, which proxy server you will choose?



## **Input**

> Multiple test cases, the first line is an integer T (T <= 100), indicating the number of test cases.
>
> The first line of each test case is two integers N (0 <= N <= 1000), M (0 <= M <= 20000). N is the number of proxy servers (labeled from 1 to N). 
>
> 0 is the label of your computer and (N+1) is the label of the server of target website.
>
> Then M lines follows, each line contains three integers u, v, w (0 <= u, v <= N + 1, 1 <= w <= 1000), means u can directly connect to v and the lag is w.



## **Output**

> An integer in one line for each test case, which proxy server you will choose to connect directly. You can only choose the proxy server which can be connected directly from your computer.
>
> If there are multiple choices, you should output the proxy server with the least label. If you can’t visit the target website by any means, output “-1” (without quotes). If you can directly visit the website and the lag is the least, output “0” (without quotes).



## **Example Input**

    4
    3 6
    0 1 10
    1 2 1
    2 4 4
    0 3 2
    3 2 1
    3 4 7
    2 4
    0 2 10
    0 1 5
    1 2 4
    2 1 7
    1 3
    0 2 1
    0 1 2
    1 2 1
    1 3
    0 2 10
    0 1 2
    1 2 1



## **Example Output**

    3
    -1
    0
    1



## **题意**

给你一些代理服务器之间的连接与延时，求出你的计算机（0）与目标服务器（n+1）之间延时最小的路径，以及路径中和你的计算机相连的代理服务器编号，如果存在多个选择的话输出最小的编号。

如果答案刚好是目标服务器的编号，输出 `0` ，无法到达则输出 `-1` 。



## **思路**

只是找寻最短路径长度的话比较容易，但是题目中还要输出路径中第二个点的编号。

假如我们在找寻最短路的时候记录了路径，又会出现一个如何让第二个点编号最小的问题。



**于是考虑反向建图**

求 `n+1` 到 `0` 的最短路，然后记录与 `0` 邻接的点，最终判断这些点加上边的费用是否等于 `dist[0]` 即可。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<stack>
using namespace std;
#define maxx 22000
#define INF 0x3f3f3f3f
typedef pair<int,int> P;
int n,m;
bool vis[maxx];
int dist[maxx];
priority_queue<P,vector<P>,greater<P> >va;

struct node
{
    int v;
    int next;
    int value;
} edge[maxx];
int head[maxx],tot;


void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
    while(!va.empty())va.pop();
}

void addedge(int u,int v,int s)
{
    edge[tot].v=v;
    edge[tot].next=head[u];
    edge[tot].value=s;
    head[u]=tot++;
}

void spfa(int s)    // 求最短路径长度
{
    memset(vis,false,sizeof(vis));
    memset(dist,INF,sizeof(dist));
    vis[s]=true;
    dist[s]=0;
    queue<int>que;
    que.push(s);
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        vis[u]=false;
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            int v=edge[i].v;
            if(dist[v]>dist[u]+edge[i].value)
            {
                dist[v]=dist[u]+edge[i].value;
                if(!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        init();
        for(int i=0; i<m; i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            addedge(y,x,z);
            if(x==0)    // 存储与0邻接的点
                va.push(P(y,z));
        }
        spfa(n+1);
        if(dist[0]==INF)    // 无法到达
            printf("-1\n");
        else
        {
            while(!va.empty())
            {
                P p=va.top();
                va.pop();
                if(dist[p.first]+p.second==dist[0]) // 找到一个编号最小且在最短路上的点
                {
                    if(p.first==n+1)    // 如果该点是 n+1
                        printf("0\n");
                    else
                        printf("%d\n",p.first);
                    break;
                }
            }
        }
    }
    return 0;
}
```

