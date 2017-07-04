# Red and Black

## **Problem Description**

> There is a rectangular room, covered with square tiles. Each tile is colored either red or black. A man is standing on a black tile. From a tile, he can move to one of four adjacent tiles. But he can't move on red tiles, he can move only on black tiles.
>
> Write a program to count the number of black tiles which he can reach by repeating the moves described above. 



## **Input**

> The input consists of multiple data sets. A data set starts with a line containing two positive integers W and H; W and H are the numbers of tiles in the x- and y- directions, respectively. W and H are not more than 20.
>
> There are H more lines in the data set, each of which includes W characters. Each character represents the color of a tile as follows.
>
> '.' - a black tile 
>
> '#' - a red tile 
>
> '@' - a man on a black tile(appears exactly once in a data set) 



## **Output**

> For each data set, your program should output a line which contains the number of tiles he can reach from the initial tile (including itself). 



## **Sample Input**

    6 9
    ....#.
    .....#
    ......
    ......
    ......
    ......
    ......
    #@...#
    .#..#.
    11 9
    .#.........
    .#.#######.
    .#.#.....#.
    .#.#.###.#.
    .#.#..@#.#.
    .#.#####.#.
    .#.......#.
    .#########.
    ...........
    11 6
    ..#..#..#..
    ..#..#..#..
    ..#..#..###
    ..#..#..#@.
    ..#..#..#..
    ..#..#..#..
    7 7
    ..#.#..
    ..#.#..
    ###.###
    ...@...
    ###.###
    ..#.#..
    ..#.#..
    0 0



## **Sample Output**

    45
    59
    6
    13


## **思路**

一个简单的深搜题目，给出地图， `.` 是可以走的区域，起点是 `@` ，问在这个起点开始走可以遇到多少个 `.` ;



## **AC 代码**

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
char mapp[25][25];
bool visit[25][25];
int s,w,h;;
void DFS(int x,int y)
{
    if(x>=0&&x<h&&y>=0&&y<w&&mapp[x][y]!='#'&&!visit[x][y]) //如果在地图内并且该电是‘.’并且没有遍历过
    {
        s++;
        visit[x][y]=true;                //标记已遍历
        DFS(x+1,y);                      //四个方向
        DFS(x,y+1);
        DFS(x,y-1);
        DFS(x-1,y);
    }
}
int main()
{
    while(cin>>w>>h&&(w||h))
    {
        int x,y;
        s=0;
        memset(visit,0,sizeof(visit));  //初始化visit数组
        for(int i=0; i<h; i++)
        {
            cin>>mapp[i];
            for(int j=0; j<w; j++)      //对每一行查找起点
                if(mapp[i][j]=='@')x=i,y=j;
        }
        DFS(x,y);                       //深度优先遍历
        cout<<s<<endl;
    }
    return 0;
}
```

