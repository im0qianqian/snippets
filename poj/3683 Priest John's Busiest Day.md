# Priest John's Busiest Day

## **Description**

> John is the only priest in his town. September 1st is the John's busiest day in a year because there is an old legend in the town that the couple who get married on that day will be forever blessed by the God of Love. This year N couples plan to get married on the blessed day. The i-th couple plan to hold their wedding from time Si to time Ti. According to the traditions in the town, there must be a special ceremony on which the couple stand before the priest and accept blessings. The i-th couple need Di minutes to finish this ceremony. Moreover, this ceremony must be either at the beginning or the ending of the wedding (i.e. it must be either from Si to Si + Di, or from Ti - Di to Ti). Could you tell John how to arrange his schedule so that he can present at every special ceremonies of the weddings.
>
> Note that John can not be present at two weddings simultaneously.



## **Input**

> The first line contains a integer N ( 1 ≤ N ≤ 1000). 
>
> The next N lines contain the Si, Ti and Di. Si and Ti are in the format of hh:mm.



## **Output**

> The first line of output contains "YES" or "NO" indicating whether John can be present at every special ceremony. If it is "YES", output another N lines describing the staring time and finishing time of all the ceremonies.



## **Sample Input**

    2
    08:00 09:00 30
    08:15 09:00 20



## **Sample Output**

    YES
    08:00 08:30
    08:40 09:00



## **题意**

一个小镇里面只有一个牧师，现在有些新人要结婚，需要牧师分别去主持一个仪式，给出每对新人婚礼的开始时间 s 和结束时间 t ，还有他们俩的这个仪式需要的时间（每对新人需要的时间长短可能不同） d ，牧师可以在婚礼开始的时间 d 内（s 到 s+d）或者是结束前的时间 d 内（t - d 到 t）完成这个仪式。现在问能否给出一种安排，让牧师能完成所有夫妇婚礼的仪式，如果可以，输出一种安排。



## **思路**

对于每一个结婚仪式 $i$ ，只有在开始或结束时进行特别仪式两种选择，因此可以定义变量 $x_i$ ，$x_i$ 为真代表 $i$ 在开始时进行特别仪式。

则对于结婚仪式 $i,j$ ，假如 $x_i,x_j$ 冲突，那么 $\neg x_i \lor \neg x_j$ 为真。

同理我们再对开始和结束、结束和开始、结束和结束这几种情况分别得出所有子句，最终的合取范式为： $(\neg x_i \lor \neg x_j) \land (x_i \lor \neg x_j) \land (\neg x_i \lor x_j) \land (x_i \lor x_j)$ 

于是这个问题便转化为 2-SAT 问题啦。



## **AC 代码**

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
typedef __int64 LL;

const int maxn = 4e6+10;

class TwoSAT
{
public:
    struct node
    {
        int to;
        int next;
    } edge[maxn];
    int head[maxn],tot,n;
    bool vis[maxn];
    int S[maxn],top;

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
int n;

void build()
{
    for(int i=0; i<n; i+=2)
    {
        for(int j=i+2; j<n; j+=2)
        {
            if(min(cnt[i].second,cnt[j].second)>max(cnt[i].first,cnt[j].first))
                sat.addedge(i,j^1),sat.addedge(j,i^1);
            if(min(cnt[i].second,cnt[j^1].second)>max(cnt[i].first,cnt[j^1].first))
                sat.addedge(i,j),sat.addedge(i^1,j^1);
            if(min(cnt[i^1].second,cnt[j].second)>max(cnt[i^1].first,cnt[j].first))
                sat.addedge(i^1,j^1),sat.addedge(j,i);
            if(min(cnt[i^1].second,cnt[j^1].second)>max(cnt[i^1].first,cnt[j^1].first))
                sat.addedge(i^1,j),sat.addedge(j^1,i);
        }
    }
}

int main()
{
    while(~scanf("%d",&n))
    {
        cnt.clear();
        n*=2;
        sat.init(n);
        int h1,m1,h2,m2,d;
        for(int i=0; i<n; i+=2)
        {
            scanf("%d%*c%d%d%*c%d%d",&h1,&m1,&h2,&m2,&d);
            h1 = h1*60+m1;
            h2 = h2*60+m2;
            cnt.push_back(P(h1,h1+d));
            cnt.push_back(P(h2-d,h2));
        }
        build();
        if(!sat.solve())
            puts("NO");
        else
        {
            puts("YES");
            for(int i=0; i<n; i+=2)
            {
                int index = sat.vis[i]?i:i^1;
                printf("%02d:%02d %02d:%02d\n",cnt[index].first/60,cnt[index].first%60,cnt[index].second/60,cnt[index].second%60);
            }
        }
    }
    return 0;
}
```

