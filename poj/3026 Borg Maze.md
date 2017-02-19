# Borg Maze

## **Description**

> The Borg is an immensely powerful race of enhanced humanoids from the delta quadrant of the galaxy. The Borg collective is the term used to describe the group consciousness of the Borg civilization. Each Borg individual is linked to the collective by a sophisticated subspace network that insures each member is given constant supervision and guidance. 
>
> Your task is to help the Borg (yes, really) by developing a program which helps the Borg to estimate the minimal cost of scanning a maze for the assimilation of aliens hiding in the maze, by moving in north, west, east, and south steps. The tricky thing is that the beginning of the search is conducted by a large group of over 100 individuals. Whenever an alien is assimilated, or at the beginning of the search, the group may split in two or more groups (but their consciousness is still collective.). The cost of searching a maze is definied as the total distance covered by all the groups involved in the search together. That is, if the original group walks five steps, then splits into two groups each walking three steps, the total distance is 11=5+3+3. 



## **Input**

> On the first line of input there is one integer, N <= 50, giving the number of test cases in the input. Each test case starts with a line containg two integers x, y such that 1 <= x,y <= 50. After this, y lines follow, each which x characters. For each character, a space `` '' stands for an open space, a hash mark ``#'' stands for an obstructing wall, the capital letter ``A'' stand for an alien, and the capital letter ``S'' stands for the start of the search. The perimeter of the maze is always closed, i.e., there is no way to get out from the coordinate of the ``S''. At most 100 aliens are present in the maze, and everyone is reachable. 



## **Output**

> For every test case, output one line containing the minimal cost of a succesful search of the maze leaving no aliens alive. 



## **Sample Input**

    2
    6 5
    ##### 
    #A#A##
    # # A#
    #S  ##
    ##### 
    7 7
    #####  
    #AAA###
    #    A#
    # S ###
    #     #
    #AAA###
    #####  



## **Sample Output**

    8
    11


## **题意**

从 S 出发，去到达每一个 A ，求最小的总路径长度，空格是空地，# 是墙，并且在走的过程中我们可以在 S 或 A 点分裂，也就是从该点可以延伸出多条路径到其他点，但是每一次只能让其中的一个继续行走。



## **思路**

既然每一个 S 或 A 处才可以分裂，并且只能让其中一个行走，求最小的路径长度，便是一棵包含所有 S 或 A 点的树。

那么，首先通过bfs枚举每一个点到其他点的最短路径长度，然后建立这样一个完全图。（其实还有比枚举更好的办法，但是因为点数目较少，枚举便可以啦）

然后在这一个完全图中求一颗最小生成树，最小生成树所有边长度的和便是总路径长度。



不过，在输入x,y之后可能会出现很多空格哦！用一般的`%*c`和`getchar()`都会失效，所以我们用`gets(str)`。看了别人博客才知道，无缘无故WA了好多次。[忧伤]



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stack>
#define inf (1<<25)
using namespace std;

int mapp[55][55];
int mv[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};
bool vis[55][55];
int parent[255];   //父亲节点，当值为-1时表示根节点

struct node
{
    int x,y,time;
    node() {};
    node(int x,int y,int time)
    {
        this->x=x;
        this->y=y;
        this->time=time;
    }
};
struct eage     //边的结构体，u、v为两端点，w为边权值
{
    int u, v, w;
    eage() {};
    eage(int u,int v,int w)
    {
        this->u=u;
        this->v=v;
        this->w=w;
    }
} EG[250*250];
int stop,x,y,etop;

void bfs(int ix,int iy)
{
//    printf("bfs %d,%d\n",ix,iy);
    memset(vis,false,sizeof(vis));      //所有点都没有被访问
    queue<node*>sk;
    vis[ix][iy]=true;
    sk.push(new node(ix,iy,0));         //初始点入队
    while(!sk.empty())
    {
        node* p=sk.front();
        sk.pop();
        if(!(p->x==ix&&p->y==iy)&&mapp[p->x][p->y]>0)   //如果找到其他点
        {
            EG[etop++]=eage(mapp[ix][iy],mapp[p->x][p->y],p->time); //加边
//            printf("%d -> %d ,%d\n",mapp[ix][iy],mapp[p->x][p->y],p->time);
        }
        for(int i=0; i<4; i++)          //移动
        {
            int xi=p->x+mv[i][0],yi=p->y+mv[i][1];
            if(xi<0||xi>=y||yi<0||yi>=x||mapp[xi][yi]<0||vis[xi][yi])continue;  //不合理的
            vis[xi][yi]=true;
            sk.push(new node(xi,yi,p->time+1));
        }
        free(p);
    }
}

bool cmp(eage a, eage b)    //排序调用
{
    return a.w < b.w;
}

int Find(int x)     //寻找根节点，判断是否在同一棵树中的依据
{
    if(parent[x] == -1) return x;
    return Find(parent[x]);
}

void Kruskal()      //Kruskal算法，parent能够还原一棵生成树，或者森林
{
    memset(parent, -1, sizeof(parent));
    int cnt = stop,ans=0;        //初始时根节点数目为n个
    sort(EG, EG+etop, cmp);    //按权值将边从小到大排序
    for(int i = 0; i < etop; i++)     //按权值从小到大选择边
    {
        if(cnt == 1) break;     //当根节点只有1个时，跳出循环
        int t1 = Find(EG[i].u), t2 = Find(EG[i].v);
        if(t1 != t2)    //若不在同一棵树种则选择该边，
        {
            ans += EG[i].w;
            parent[t1] = t2;
            cnt--;      //每次合并，减少一个根节点
        }
    }
    printf("%d\n",ans);
}

int main()
{
    int n;
    char str[55];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d",&x,&y);
        gets(str);                  //这里可能会出现很多空格
        stop=etop=0;
        memset(mapp,-1,sizeof(mapp));
        for(int i=0; i<y; i++)
        {
            gets(str);
            for(int j=0; j<x; j++)
                if(str[j]=='A'||str[j]=='S')
                    mapp[i][j]=++stop;
                else if(str[j]==' ')mapp[i][j]=0;
        }
        for(int i=0; i<y; i++)
            for(int j=0; j<x; j++)
                if(mapp[i][j]>0)    //从 'A' 或 'S' 开始
                    bfs(i,j);
        Kruskal();
    }
    return 0;
}
```

