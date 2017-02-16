# Flip Game

## **Description**

> Flip game is played on a rectangular 4x4 field with two-sided pieces placed on each of its 16 squares. One side of each piece is white and the other one is black and each piece is lying either it's black or white side up. Each round you flip 3 to 5 pieces, thus changing the color of their upper side from black to white and vice versa. The pieces to be flipped are chosen every round according to the following rules: 
>
> Choose any one of the 16 pieces. 
>
> Flip the chosen piece and also all adjacent pieces to the left, to the right, to the top, and to the bottom of the chosen piece (if there are any).
>
> ![img](http://poj.org/images/1753_1.jpg)
>
> Consider the following position as an example: 
>
> bwbw 
> wwww 
> bbwb 
> bwwb 
>
> Here "b" denotes pieces lying their black side up and "w" denotes pieces lying their white side up. If we choose to flip the 1st piece from the 3rd row (this choice is shown at the picture), then the field will become: 
>
> bwbw 
> bwww 
> wwwb 
> wwwb 
>
> The goal of the game is to flip either all pieces white side up or all pieces black side up. You are to write a program that will search for the minimum number of rounds needed to achieve this goal. 



## **Input**

> The input consists of 4 lines with 4 characters "w" or "b" each that denote game field position.



## **Output**

> Write to the output file a single integer number - the minimum number of rounds needed to achieve the goal of the game from the given position. If the goal is initially achieved, then write 0. If it's impossible to achieve the goal, then write the word "Impossible" (without quotes).



## **Sample Input**

    bwwb
    bbwb
    bwwb
    bwww



## **Sample Output**

    4


## **题意**

有4\*4的正方形，每个格子要么是黑色，要么是白色，当把一个格子的颜色改变(黑->白 || 白->黑)时，其周围上下左右(如果存在的话)的格子的颜色也被反转，问至少反转几个格子可以使4\*4的正方形变为纯白或者纯黑？



## **思路**

- 对于每一个格子，只有两个状态，将它翻转一次与翻转奇数次效果是一样的，翻转零次与翻转偶数次的效果是一样的。

- 因为只有16个格子，选择0个、1个、2个...16个所有的情况有

  $C_{16}^0+C_{16}^1+C_{16}^2+C_{16}^3+...+C_{16}^{15}+C_{16}^{16}=2^{16}$

- 枚举不会超时，所以我们可以用递归的思想模拟0-16重循环，分别表示选择翻转的棋子个数。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;
bool bits[16];
bool flag=false;

void rese(int n)    //翻转
{
    int x=n/4,y=n%4;
    for(int i=max(0,y-1); i<min(y+2,4); i++)
        bits[x*4+i]=!bits[x*4+i];
    if(x!=0)
        bits[(x-1)*4+y]=!bits[(x-1)*4+y];
    if(x!=3)
        bits[(x+1)*4+y]=!bits[(x+1)*4+y];
}

bool jud()          //判断是否一致
{
    bool ini=bits[0];
    for(int i=1; i<16; i++)
        if(ini!=bits[i])
            return false;
    return true;
}

void solve(int maxx,int now,int step)
{
    if(maxx==step)  //翻转完最后一枚棋子
    {
        if(jud())   //满足状态
        {
            flag=true;
            printf("%d\n",maxx);
        }
        return;
    }
    for(int i=now; i<16; i++)   //从上次翻转位置继续
    {
        rese(i);                //翻转i
        solve(maxx,i+1,step+1);
        if(flag)return;         //找到答案，返回
        rese(i);                //恢复原来状态
    }
}

int main()
{
    char str[4][4];
    for(int i=0; i<4; i++)
    {
        cin>>str[i];
        for(int j=0; j<4; j++)
            bits[i*4+j]=(str[i][j]=='b')?1:0;
    }
    for(int i=0; i<=16; i++)    //i 为要翻转的棋子个数
        solve(i,0,0);
    if(!flag)                   //没有找到答案
        printf("Impossible\n");
    return 0;
}
```

