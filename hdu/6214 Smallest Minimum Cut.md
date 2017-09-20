# Smallest Minimum Cut

## **Description**

> Consider a network G=(V,E) with source s and sink t. An s-t cut is a partition of nodes set V into two parts such that s and t belong to different parts. The cut set is the subset of E with all edges connecting nodes in different parts. A minimum cut is the one whose cut set has the minimum summation of capacities. The size of a cut is the number of edges in the cut set. Please calculate the smallest size of all minimum cuts.



## **Input**

> The input contains several test cases and the first line is the total number of cases T (1≤T≤300).
>
> Each case describes a network G, and the first line contains two integers n (2≤n≤200) and m (0≤m≤1000) indicating the sizes of nodes and edges. All nodes in the network are labelled from 1 to n.
>
> The second line contains two different integers s and t (1≤s,t≤n) corresponding to the source and sink.
>
> Each of the next m lines contains three integers u,v and w (1≤w≤255) describing a directed edge from node u to v with capacity w.



## **Output**

> For each test case, output the smallest size of all minimum cuts in a line.



## **Sample Input**

    2
    4 5
    1 4
    1 2 3
    1 3 1
    2 3 1
    2 4 1
    3 4 2
    4 5
    1 4
    1 2 3
    1 3 1
    2 3 1
    2 4 1
    3 4 3



## **Sample Output**

    2
    3



## **题意**

求图中最小割的前提下的最少边数。



## **思路**

经典的题目啦，我们把一条边的大小附加到该边的流量中，然后求出此时的最大流，流中即包含了所选择的边数。

另外：最大流 = 最小割



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int64 LL;

const int MAXN=10000;
const int MAXM=10000;
const int INF=0x3f3f3f3f;

struct Node
{
    int from,to,next;
    int cap;
} edge[MAXM];
int tol;
int head[MAXN];
int dep[MAXN];
int gap[MAXN];

int n;
void init()
{
    tol=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int w)
{
    edge[tol].from=u;
    edge[tol].to=v;
    edge[tol].cap=w;
    edge[tol].next=head[u];
    head[u]=tol++;
    edge[tol].from=v;
    edge[tol].to=u;
    edge[tol].cap=0;
    edge[tol].next=head[v];
    head[v]=tol++;
}

void BFS(int start,int end)
{
    memset(dep,-1,sizeof(dep));
    memset(gap,0,sizeof(gap));
    gap[0]=1;
    int que[MAXN];
    int front,rear;
    front=rear=0;
    dep[end]=0;
    que[rear++]=end;
    while(front!=rear)
    {
        int u=que[front++];
        if(front==MAXN)front=0;
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            int v=edge[i].to;
            if(dep[v]!=-1)continue;
            que[rear++]=v;
            if(rear==MAXN)rear=0;
            dep[v]=dep[u]+1;
            ++gap[dep[v]];
        }
    }
}
int SAP(int start,int end)
{
    int res=0;
    BFS(start,end);
    int cur[MAXN];
    int S[MAXN];
    int top=0;
    memcpy(cur,head,sizeof(head));
    int u=start;
    int i;
    while(dep[start]<n)
    {
        if(u==end)
        {
            int temp=INF;
            int inser;
            for(i=0; i<top; i++)
                if(temp>edge[S[i]].cap)
                {
                    temp=edge[S[i]].cap;
                    inser=i;
                }
            for(i=0; i<top; i++)
            {
                edge[S[i]].cap-=temp;
                edge[S[i]^1].cap+=temp;
            }
            res+=temp;
            top=inser;
            u=edge[S[top]].from;
        }
        if(u!=end&&gap[dep[u]-1]==0)
            break;
        for(i=cur[u]; i!=-1; i=edge[i].next)
            if(edge[i].cap!=0&&dep[u]==dep[edge[i].to]+1)
                break;
        if(i!=-1)
        {
            cur[u]=i;
            S[top++]=i;
            u=edge[i].to;
        }
        else
        {
            int min=n;
            for(i=head[u]; i!=-1; i=edge[i].next)
            {
                if(edge[i].cap==0)continue;
                if(min>dep[edge[i].to])
                {
                    min=dep[edge[i].to];
                    cur[u]=i;
                }
            }
            --gap[dep[u]];
            dep[u]=min+1;
            ++gap[dep[u]];
            if(u!=start)u=edge[S[--top]].from;
        }
    }
    return res;
}

template <class T>
inline void scan_d(T &ret)
{
    char c;
    ret = 0;
    while ((c = getchar()) < '0' || c > '9');
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0'), c = getchar();
    }
}
template <class T>
inline void print_d(T x)
{
    if (x > 9)
    {
        print_d(x / 10);
    }
    putchar(x % 10 + '0');
}
int main()
{
    int T;
    scan_d(T);
    while(T--)
    {
        int m,st,ed;
        scan_d(n);
        scan_d(m);
        scan_d(st);
        scan_d(ed);
        init();
        for(int i=0; i<m; i++)
        {
            int u,v,cap;
            scan_d(u);
            scan_d(v);
            scan_d(cap);
            addedge(u-1,v-1,cap*1000+1);
        }
        print_d(SAP(st-1,ed-1)%1000);
        putchar('\n');
    }
    return 0;
}
```

