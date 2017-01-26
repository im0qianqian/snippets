# A Knight's Journey

## **Description**

> **Background** 
>
> The knight is getting bored of seeing the same black and white squares again and again and has decided to make a journey 
>
> around the world. Whenever a knight moves, it is two squares in one direction and one square perpendicular to this. The world of a knight is the chessboard he is living on. Our knight lives on a chessboard that has a smaller area than a regular 8 * 8 board, but it is still rectangular. Can you help this adventurous knight to make travel plans? 
>
> **Problem** 
>
> Find a path such that the knight visits every square once. The knight can start and end on any square of the board.



## **Input**

> The input begins with a positive integer n in the first line. The following lines contain n test cases. Each test case consists of a single line with two positive integers p and q, such that 1 <= p * q <= 26. This represents a p * q chessboard, where p describes how many different square numbers 1, . . . , p exist, q describes how many different square letters exist. These are the first q letters of the Latin alphabet: A, . . .



## **Output**

> The output for every scenario begins with a line containing "Scenario #i:", where i is the number of the scenario starting at 1. Then print a single line containing the lexicographically first path that visits all squares of the chessboard with knight moves followed by an empty line. The path should be given on a single line by concatenating the names of the visited squares. Each square name consists of a capital letter followed by a number. 
>
> If no such path exist, you should output impossible on a single line.



## **Sample Input**

    3
    1 1
    2 3
    4 3



## **Sample Output**

    Scenario #1:
    A1
    
    Scenario #2:
    impossible
    
    Scenario #3:
    A1B3C1A2B4C2A3B1C3A4B2C4



## **题意**

马要走遍p*q的棋盘的所有格，它可以从任意点出发，问能否成功，若能，输出所能走的最小字典序的路径。



## **思路**

简单dfs，判断马是否走遍了所有格我们可以用搜索的深度来判断，如果它等于棋盘格的数量，则已经走遍了所有，在dfs过程中，我们要保证走过的点不会被重复踏入，另外一个便是如何保证字典序最小，可以采用搜索的顺续来确定，具体顺续见move数组。



## **AC 代码**

```cpp
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include<algorithm>
#include <queue>
using namespace std;

bool visited[30][30],flag;

int move[8][2]= {{-1,-2},{1,-2},{-2,-1},{2,-1},{-2,1},{2,1},{-1,2},{1,2}};
int p,q;

struct node
{
    char x;
    char y;
    void init(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
} sk[1005];

void dfs(int x,int y,int deep)
{
    if(deep==p*q)       //已经走遍了所有格
    {
        for(int i=0; i<deep; i++)
            printf("%c%c",sk[i].x,sk[i].y);
        printf("\n");
        flag=true;      //找到路径
        return;
    }
    for(int i=0; i<8; i++)
    {
        int xi=move[i][0]+x;
        int yi=move[i][1]+y;
        if(xi<0||xi>=p||yi<0||yi>=q)continue;   //棋盘外
        if(visited[xi][yi]==false)              //该位置为空
        {
            visited[xi][yi]=true;
            sk[deep].init(yi+'A',xi+'1');
            dfs(xi,yi,deep+1);
            if(flag)return;
            visited[xi][yi]=false;
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int ni=1; ni<=n; ni++)
    {
        printf("Scenario #%d:\n",ni);
        scanf("%d%d",&p,&q);
        flag=false;         //当前未找到路径
        memset(visited,false,sizeof(visited));
        for(int j=0; j<q; j++)      //先枚举列是为了保证字典序最小
            for(int i=0; i<p; i++)
            {
                visited[i][j]=true;
                sk[0].init(j+'A',i+'1');
                dfs(i,j,1);
                visited[i][j]=false;
            }
        if(!flag)       //没有找到路径
            printf("impossible\n");
        if(ni!=n)puts("");
    }
    return 0;
}
```

