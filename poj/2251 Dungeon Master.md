# Dungeon Master

## **Description**

> You are trapped in a 3D dungeon and need to find the quickest way out! The dungeon is composed of unit cubes which may or may not be filled with rock. It takes one minute to move one unit north, south, east, west, up or down. You cannot move diagonally and the maze is surrounded by solid rock on all sides. 
>
> Is an escape possible? If yes, how long will it take? 



## **Input**

> The input consists of a number of dungeons. Each dungeon description starts with a line containing three integers L, R and C (all limited to 30 in size). 
>
> L is the number of levels making up the dungeon. 
>
> R and C are the number of rows and columns making up the plan of each level. 
>
> Then there will follow L blocks of R lines each containing C characters. Each character describes one cell of the dungeon. A cell full of rock is indicated by a '#' and empty cells are represented by a '.'. Your starting position is indicated by 'S' and the exit by the letter 'E'. There's a single blank line after each level. Input is terminated by three zeroes for L, R and C.



## **Output**

> Each maze generates one line of output. If it is possible to reach the exit, print a line of the form 
>
> Escaped in x minute(s).
>
> where x is replaced by the shortest time it takes to escape. 
>
> If it is not possible to escape, print the line 
>
> Trapped!



## **Sample Input**

    3 4 5
    S....
    .###.
    .##..
    ###.#
    
    #####
    #####
    ##.##
    ##...
    
    #####
    #####
    #.###
    ####E
    
    1 3 3
    S##
    #E#
    ###
    
    0 0 0



## **Sample Output**

    Escaped in 11 minute(s).
    Trapped!



## **题意**

给出一个三维的地图，问从S走到E最少需要多少步，不过走不到，输出`Trapped!` 。



简单的BFS，好久没有遇到这样的问题了，先水一道，哈哈~



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<string.h>
using namespace std;
#define MAXX 35
int l,r,c;
char mapp[MAXX][MAXX][MAXX];
bool visited[MAXX][MAXX][MAXX];
int move[6][3]= {{0,0,1},{0,0,-1},{0,1,0},{1,0,0},{0,-1,0},{-1,0,0}};
struct point
{
    int x;
    int y;
    int z;
    int time;
    void init(int x,int y,int z,int time)
    {
        this->x=x;
        this->y=y;
        this->z=z;
        this->time=time;
    }
} s;

int bfs()
{
    queue<point> sk;
    sk.push(s);
    visited[s.z][s.y][s.x]=true;
    while(!sk.empty())
    {
        point p=sk.front();
        sk.pop();
        if(mapp[p.z][p.y][p.x]=='E')
            return p.time;
        for(int i=0; i<6; i++)
        {
            int xi=p.x+move[i][0];
            int yi=p.y+move[i][1];
            int zi=p.z+move[i][2];
            if(xi<0||xi>=c||yi<0||yi>=r||zi<0||zi>=l)
                continue;
            if(visited[zi][yi][xi]==false)
            {
                point tmp;
                tmp.init(xi,yi,zi,p.time+1);
                visited[zi][yi][xi]=true;
                sk.push(tmp);
            }
        }
    }
    return -1;
}
int main()
{
    while(~scanf("%d%d%d%*c",&l,&r,&c)&&(l||r||c))
    {
        memset(visited,false,sizeof(visited));
        for(int i=0; i<l; i++)
        {
            for(int j=0; j<r; j++)
            {
                int len;
                while(gets(mapp[i][j]))
                {
                    len= strlen(mapp[i][j]);
                    if(len!=0)break;
                }
                for(int k=0; k<c; k++)
                {
                    if(mapp[i][j][k]=='S')
                        s.init(k,j,i,0);
                    else if(mapp[i][j][k]=='#')
                        visited[i][j][k]=true;
                }
            }
        }
        int ans=bfs();
        printf(ans==-1?"Trapped!\n":"Escaped in %d minute(s).\n",ans);
    }
    return 0;
}
```

