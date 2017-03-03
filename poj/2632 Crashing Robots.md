# Crashing Robots

## **Description**

> In a modernized warehouse, robots are used to fetch the goods. Careful planning is needed to ensure that the robots reach their destinations without crashing into each other. Of course, all warehouses are rectangular, and all robots occupy a circular floor space with a diameter of 1 meter. Assume there are N robots, numbered from 1 through N. You will get to know the position and orientation of each robot, and all the instructions, which are carefully (and mindlessly) followed by the robots. Instructions are processed in the order they come. No two robots move simultaneously; a robot always completes its move before the next one starts moving. 
>
> A robot crashes with a wall if it attempts to move outside the area of the warehouse, and two robots crash with each other if they ever try to occupy the same spot.



## **Input**

> The first line of input is K, the number of test cases. Each test case starts with one line consisting of two integers, 1 <= A, B <= 100, giving the size of the warehouse in meters. A is the length in the EW-direction, and B in the NS-direction. 
>
> The second line contains two integers, 1 <= N, M <= 100, denoting the numbers of robots and instructions respectively. 
>
> Then follow N lines with two integers, 1 <= Xi <= A, 1 <= Yi <= B and one letter (N, S, E or W), giving the starting position and direction of each robot, in order from 1 through N. No two robots start at the same position. 
>
> ![img](http://poj.org/images/2632_1.jpg)
>
> Figure 1: The starting positions of the robots in the sample warehouse
>
> Finally there are M lines, giving the instructions in sequential order. 
>
> An instruction has the following format: < robot #> < action> < repeat> 
>
> Where is one of 
>
> L: turn left 90 degrees, 
>
> R: turn right 90 degrees, or 
>
> F: move forward one meter,and 1 <= < repeat> <= 100 is the number of times the robot should perform this single move.



## **Output**

> Output one line for each test case: 
>
> Robot i crashes into the wall, if robot i crashes into a wall. (A robot crashes into a wall if Xi = 0, Xi = A + 1, Yi = 0 or Yi = B + 1.) 
>
> Robot i crashes into robot j, if robots i and j crash, and i is the moving robot. 
>
> OK, if no crashing occurs.
>
> Only the first crash is to be reported.



## **Sample Input**

    4
    5 4
    2 2
    1 1 E
    5 4 W
    1 F 7
    2 F 7
    5 4
    2 4
    1 1 E
    5 4 W
    1 F 3
    2 F 1
    1 L 1
    1 F 3
    5 4
    2 2
    1 1 E
    5 4 W
    1 L 96
    1 F 2
    5 4
    2 3
    1 1 E
    5 4 W
    1 F 4
    1 L 1
    1 F 20



## **Sample Output**

    Robot 1 crashes into the wall
    Robot 1 crashes into robot 2
    OK
    Robot 1 crashes into robot 2


## **题意**

给出所有机器人的初始位置以及它的方向，然后对这些机器人进行操作，操作的方式有三种：左转、右转、前行，判断并输出在执行这些操作的时候机器人是否碰到墙（边界），或者是否与其他机器人相遇，若都没有，则输出 `OK` 。



## **思路**

因为题目给出的数据范围很小，所以直接模拟便可，左转n次或者右转n次都相当于转动n%4次。



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
#include<stack>

int mv[4][2]= {{1,0},{0,-1},{-1,0},{0,1}};  //移动数组 逆时针

struct point
{
    int x;
    int y;
    int face;
    void init(int x,int y,char f)
    {
        this->x=x;
        this->y=y;
        if(f=='E')face=3;
        else if(f=='N')face=0;
        else if(f=='W')face=1;
        else if(f=='S')face=2;
    }
} a[105];
int mapx,mapy;      //地图边界
int mapp[105][105]; //地图各点的状态 -1表示空 其他表示当前点的机器人编号

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m,x,y;
        char c;
        bool flag=true;
        memset(mapp,-1,sizeof(mapp));
        scanf("%d%d%d%d",&mapy,&mapx,&n,&m);
        for(int i=0; i<n; i++)
        {
            scanf("%d%d %c",&y,&x,&c);
            a[i].init(x-1,y-1,c);   //先初始化各机器人
            mapp[x-1][y-1]=i+1;     //在地图上标记
        }
        for(int i=0; i<m; i++)
        {
            scanf("%d %c %d",&x,&c,&y);
            if(!flag)continue;
            if(c=='F')      //直行
            {
                int *nx=&a[x-1].x,*ny=&a[x-1].y,*f=&a[x-1].face;    //获取当前位置与方向
                mapp[*nx][*ny]=-1;  //走过之后原位置为空
                for(int j=0; j<y; j++)  //重复y次
                {
                    *nx+=mv[*f][0];     //行走
                    *ny+=mv[*f][1];
                    if(*nx<0||*ny<0||*nx>=mapx||*ny>=mapy)  //如果越过边界
                    {
                        printf("Robot %d crashes into the wall\n",x);
                        flag=false;
                        break;
                    }
                    else if(mapp[*nx][*ny]>0)   //如果当前点有其他机器人
                    {
                        printf("Robot %d crashes into robot %d\n",x,mapp[*nx][*ny]);
                        flag=false;
                        break;
                    }
                }
                mapp[*nx][*ny]=x;   //标记当前点所在机器人
            }
            else
            {
                y%=4;   //转4次相当于没有转动
                if(c=='L')
                    a[x-1].face=(a[x-1].face+y)%4;  //计算转完之后的方向
                else if(c=='R')
                    a[x-1].face=(a[x-1].face+4-y)%4;
            }
        }
        if(flag)printf("OK\n");
    }
    return 0;
}
```

