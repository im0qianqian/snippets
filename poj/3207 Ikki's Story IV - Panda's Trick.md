# Ikki's Story IV - Panda's Trick

## **Description**

> liympanda, one of Ikki’s friend, likes playing games with Ikki. Today after minesweeping with Ikki and winning so many times, he is tired of such easy games and wants to play another game with Ikki.
>
> liympanda has a magic circle and he puts it on a plane, there are n points on its boundary in circular border: 0, 1, 2, …, n − 1. Evil panda claims that he is connecting m pairs of points. To connect two points, liympanda either places the link entirely inside the circle or entirely outside the circle. Now liympanda tells Ikki no two links touch inside/outside the circle, except on the boundary. He wants Ikki to figure out whether this is possible…
>
> Despaired at the minesweeping game just played, Ikki is totally at a loss, so he decides to write a program to help him.



## **Input**

> The input contains exactly one test case.
>
> In the test case there will be a line consisting of of two integers: n and m (n ≤ 1,000, m ≤ 500). The following m lines each contain two integers ai and bi, which denote the endpoints of the ith wire. Every point will have at most one link.



## **Output**

> Output a line, either “panda is telling the truth...” or “the evil panda is lying again”.



## **Sample Input**

    4 2
    0 1
    3 2



## **Sample Output**

    panda is telling the truth...



## **题意**

平面中的一个圆，圆的边上按顺时针放着 n 个点，现在要连 m 条边，每条边可以从圆内部或者外部连接，问能否找到一种情况使得这些边互不相交。



## **思路**

2-SAT 问题

我们可以把每条边外部连接和内部连接看作 2-SAT 中的一对节点，然后枚举所有的边组合，判断其划线是否相互约束（比如 $(1,4)$ 与 $(2,5)$ 相互约束）。

若是，加入新边： $xx->yy',yy'->xx,xx'->yy,yy->xx'$

然后根据染色法判断一下图中是否存在冲突即可。



## **AC 代码**

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
typedef __int64 LL;

const int maxn = 1e6+10;

class TwoSAT
{
public:
    struct node
    {
        int to;
        int next;
    } edge[maxn];
    int head[maxn],tot,n;
    bool vis[maxn];         // 染色标记 true 表示选择
    int S[maxn],top;        // 栈

    void init(int n)
    {
        memset(head,-1,sizeof(head));
        tot = 0;
        this->n = n;
    }

    void addedge(int u,int v)
    {
        edge[tot].to = v;
        edge[tot].next = head[u];
        head[u] = tot++;
    }

    bool dfs(int x)
    {
        if(vis[x^1])return false;
        if(vis[x])return true;
        vis[x] = true;
        S[top++] = x;
        for(int i=head[x]; i!=-1; i=edge[i].next)
            if(!dfs(edge[i].to))
                return false;
        return true;
    }

    bool solve()
    {
        memset(vis,false,sizeof(vis));
        for(int i=0; i<n; i+=2)
        {
            if(vis[i]||vis[i^1])continue;
            top = 0;
            if(!dfs(i))
            {
                while(top)
                    vis[S[--top]] = false;
                if(!dfs(i^1))return false;
            }
        }
        return true;
    }
} sat;

typedef pair<int,int> P;
vector<P> cnt;
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        cnt.clear();
        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            if(u>v)swap(u,v);
            cnt.push_back(P(u,v));
        }
        sat.init(2*m);
        for(int i=0; i<m; i++)
        {
            for(int j=i+1; j<m; j++)
            {
                if((cnt[i].first<cnt[j].second&&cnt[i].first>cnt[j].first&&cnt[i].second>cnt[j].second)||(cnt[i].second<cnt[j].second&&cnt[i].second>cnt[j].first&&cnt[i].first<cnt[j].first))
                {
                    int xx = i*2;
                    int yy = j*2;
                    sat.addedge(xx,yy^1);
                    sat.addedge(yy,xx^1);
                    sat.addedge(yy^1,xx);
                    sat.addedge(xx^1,yy);
                }
            }
        }
        puts(sat.solve()?"panda is telling the truth...":"the evil panda is lying again");
    }
    return 0;
}
```

