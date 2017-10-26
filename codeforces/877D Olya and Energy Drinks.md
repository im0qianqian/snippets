# D. Olya and Energy Drinks

## **Description**

> Olya loves energy drinks. She loves them so much that her room is full of empty cans from energy drinks.
>
> Formally, her room can be represented as a field of n × m cells, each cell of which is empty or littered with cans.
>
> Olya drank a lot of energy drink, so now she can run k meters per second. Each second she chooses one of the four directions (up, down, left or right) and runs from 1 to k meters in this direction. Of course, she can only run through empty cells.
>
> Now Olya needs to get from cell (x1, y1) to cell (x2, y2). How many seconds will it take her if she moves optimally?
>
> It's guaranteed that cells (x1, y1) and (x2, y2) are empty. These cells can coincide.



## **Input**

> The first line contains three integers n, m and k (1 ≤ n, m, k ≤ 1000) — the sizes of the room and Olya's speed.
>
> Then n lines follow containing m characters each, the i-th of them contains on j-th position "#", if the cell (i, j) is littered with cans, and "." otherwise.
>
> The last line contains four integers x1, y1, x2, y2 (1 ≤ x1, x2 ≤ n, 1 ≤ y1, y2 ≤ m) — the coordinates of the first and the last cells.



## **Output**

> Print a single integer — the minimum time it will take Olya to get from (x1, y1) to (x2, y2).
>
> If it's impossible to get from (x1, y1) to (x2, y2), print -1.



## **Examples input**

    3 4 4
    ....
    ###.
    ....
    1 1 3 1



## **Examples output**

    3



## **题意**

从 $(x_1,y_1)$ 走到 $(x_2,y_2)$ ，每次最多往一个方向走 $k$ 步，且不可穿墙，问最少需要走几次才能达成目标。



## **思路**

每次把可以走到的点加入队列 bfs 即可，注意优化剪枝，如同一个点只计算一次。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
#define inf 0x7f7f7f7f
using namespace std;
typedef __int64 LL;
const int maxm = 1e3+10;
const int maxn = 1e7+10;
const int mv[4][2]= {{0,1},{0,-1},{1,0},{-1,0}};

struct node
{
    int x;
    int y;
    int t;
    node() {}
    node(int xx,int yy,int tt)
    {
        x = xx;
        y = yy;
        t = tt;
    }
} g[maxn];

char c[maxm][maxm];
int f[maxm][maxm];
int n,m,k;
int x1,x2,y1,y2;
queue<node>que;

void init()
{
    for(int j=0; j<4; j++)
        for(int i=1; i<=k; i++)
        {
            int xx = x1+mv[j][0]*i;
            int yy = y1+mv[j][1]*i;
            if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&c[xx][yy]=='.')
            {
                f[xx][yy]=1;
                que.push(node(xx,yy,1));
            }
            else break;
        }
}

void bfs()
{
    if(x1==x2&&y1==y2)
    {
        puts("0");
        return;
    }
    init();
    while(!que.empty())
    {
        node s=que.front();
        que.pop();
        if(f[x2][y2])
        {
            printf("%d\n",f[x2][y2]);
            return;
        }
        for(int j=0; j<4; j++)
            for(int i=1; i<=k; i++)
            {
                int xx = s.x+mv[j][0]*i;
                int yy = s.y+mv[j][1]*i;
                if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&c[xx][yy]=='.')
                {
                    if(f[xx][yy]==0)
                    {
                        f[xx][yy]=s.t+1;
                        que.push(node(xx,yy,s.t+1));
                    }
                }
                else break;
            }
    }
    puts("-1");
}

int main()
{
    scanf("%d%d%d%*c",&n,&m,&k);
    for(int i=1; i<=n; i++)
        gets(c[i]+1);
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    bfs();
    return 0;
}
```

