# Robot Motion

## **Description**

> ![img](http://poj.org/images/1573_1.jpg)
>
> A robot has been programmed to follow the instructions in its path. Instructions for the next direction the robot is to move are laid down in a grid. The possible instructions are 
>
> N north (up the page) 
>
> S south (down the page) 
>
> E east (to the right on the page) 
>
> W west (to the left on the page) 
>
> For example, suppose the robot starts on the north (top) side of Grid 1 and starts south (down). The path the robot follows is shown. The robot goes through 10 instructions in the grid before leaving the grid. 
>
> Compare what happens in Grid 2: the robot goes through 3 instructions only once, and then starts a loop through 8 instructions, and never exits. 
>
> You are to write a program that determines how long it takes a robot to get out of the grid or how the robot loops around. 



## **Input**

> There will be one or more grids for robots to navigate. The data for each is in the following form. On the first line are three integers separated by blanks: the number of rows in the grid, the number of columns in the grid, and the number of the column in which the robot enters from the north. The possible entry columns are numbered starting with one at the left. Then come the rows of the direction instructions. Each grid will have at least one and at most 10 rows and columns of instructions. The lines of instructions contain only the characters N, S, E, or W with no blanks. The end of input is indicated by a row containing 0 0 0.



## **Output**

> For each grid in the input there is one line of output. Either the robot follows a certain number of instructions and exits the grid on any one the four sides or else the robot follows the instructions on a certain number of locations once, and then the instructions on some number of locations repeatedly. The sample input below corresponds to the two grids above and illustrates the two forms of output. The word "step" is always immediately followed by "(s)" whether or not the number before it is 1.



## **Sample Input**

    3 6 5
    NEESWE
    WWWESS
    SNWWWW
    4 5 1
    SESWE
    EESNW
    NWEEN
    EWSEN
    0 0 0



## **Sample Output**

    10 step(s) to exit
    3 step(s) before a loop of 8 step(s)


## **题意**

给出一个迷宫与人物的起始位置，人物沿地图的标记行走，输出他在第多少步时走出迷宫或者在第多少步时陷入循环以及循环的长度。



## **思路**

迷宫可以用二维数组来存储，每一个点存储的是它的移动方向。

然后从初始位置模拟行走，如果某一次脱离地图边缘，即成功离开；

走过的点都标记为第一次走到这里所需要的步数，若在行走过程中遇到已经走过的点，则说明当前陷入循环，循环的长度即两个步数之差。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

int mv[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; //移动方向
int mapp[15][15];
int x,y,s;

void solve()
{
    int vis[15][15]= {0};
    int mx=0,my=s-1,step=0,sx,sy;
    while(true)
    {
        if(mx<0||mx>=x||my<0||my>=y)    //离开地图边缘
        {
            printf("%d step(s) to exit\n",step);
            break;
        }
        if(vis[mx][my])                 //走到一个已经访问过的点
        {
            printf("%d step(s) before a loop of %d step(s)\n",vis[mx][my]-1,step-vis[mx][my]+1);
            break;
        }
        vis[mx][my]=++step;
        sx=mx;
        sy=my;
        mx+=mv[mapp[sx][sy]][0];
        my+=mv[mapp[sx][sy]][1];
    }
}

int main()
{

    while(~scanf("%d%d%d%*c",&x,&y,&s)&&(x||y||s))
    {
        char str[15];
        for(int i=0; i<x; i++)
        {
            gets(str);
            for(int j=0; j<y; j++)
                if(str[j]=='N')mapp[i][j]=0;    //这里的方向与mv数组相对应
                else if(str[j]=='S')mapp[i][j]=1;
                else if(str[j]=='W')mapp[i][j]=2;
                else if(str[j]=='E')mapp[i][j]=3;
        }
        solve();
    }
    return 0;
}
```

