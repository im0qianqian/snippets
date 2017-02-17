# The Pilots Brothers' refrigerator

## **Description**

> The game “The Pilots Brothers: following the stripy elephant” has a quest where a player needs to open a refrigerator.
>
> There are 16 handles on the refrigerator door. Every handle can be in one of two states: open or closed. The refrigerator is open only when all handles are open. The handles are represented as a matrix 4х4. You can change the state of a handle in any location [i, j] (1 ≤ i, j ≤ 4). However, this also changes states of all handles in row i and all handles in column j.
>
> The task is to determine the minimum number of handle switching necessary to open the refrigerator.



## **Input**

> The input contains four lines. Each of the four lines contains four characters describing the initial state of appropriate handles. A symbol “+” means that the handle is in closed state, whereas the symbol “−” means “open”. At least one of the handles is initially closed.



## **Output**

> The first line of the input contains N – the minimum number of switching. The rest N lines describe switching sequence. Each of the lines contains a row number and a column number of the matrix separated by one or more spaces. If there are several solutions, you may give any one of them.



## **Sample Input**

    -+--
    ----
    ----
    -+--



## **Sample Output**

    6
    1 1
    1 3
    1 4
    4 1
    4 3
    4 4


## **题意**

把题目中给出的状态图,全部翻转成 `-` 的状态

每次翻转一个，它所在的行和列都要进行翻转

问最小翻转次数，同时输出翻转路径。



## **思路**

和 [POJ 1753](https://www.dreamwings.cn/poj1753/4470.html) 一样，只不过在dfs的时候用一个栈或者双端队列存储当前的路径，找到答案之后输出。



## **AC 代码**

```cpp
#include <iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<queue>
using namespace std;
bool bits[16];
bool flag=false;
deque<int>sk;

void rese(int n)    //翻转
{
    int x=n/4,y=n%4;
    for(int i=0; i<4; i++)
        bits[x*4+i]=!bits[x*4+i];
    for(int i=0; i<4; i++)
        if(i!=x)
            bits[i*4+y]=!bits[i*4+y];
}

bool jud()          //判断是否一致
{
    bool ini=bits[0];
    if(!ini)return false;
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
            for(int i=0; i<maxx; i++)
            {
                printf("%d %d\n",sk.front()/4+1,sk.front()%4+1);
                sk.pop_front();
            }
        }
        return;
    }
    for(int i=now; i<16; i++)   //从上次翻转位置继续
    {
        rese(i);                //翻转i
        sk.push_back(i);
        solve(maxx,i+1,step+1);
        if(flag)return;         //找到答案，返回
        sk.pop_back();
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
            bits[i*4+j]=(str[i][j]=='-')?1:0;
    }
    for(int i=0; i<=16; i++)    //i 为要翻转的棋子个数
        solve(i,0,0);
    return 0;
}
```

