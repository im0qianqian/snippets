# Sudoku1

## **Description**

> Sudoku is a very simple task. A square table with 9 rows and 9 columns is divided to 9 smaller squares 3x3 as shown on the Figure. In some of the cells are written decimal digits from 1 to 9. The other cells are empty. The goal is to fill the empty cells with decimal digits from 1 to 9, one digit per cell, in such way that in each row, in each column and in each marked 3x3 subsquare, all the digits from 1 to 9 to appear. Write a program to solve a given Sudoku-task. 
>
> ![img](http://poj.org/images/2676_1.jpg)



## **Input**

> The input data will start with the number of the test cases. For each test case, 9 lines follow, corresponding to the rows of the table. On each line a string of exactly 9 decimal digits is given, corresponding to the cells in this line. If a cell is empty it is represented by 0.



## **Output**

> For each test case your program should print the solution in the same format as the input data. The empty cells have to be filled according to the rules. If solutions is not unique, then the program may print any one of them.



## **Sample Input**

    1
    103000509
    002109400
    000704000
    300502006
    060000050
    700803004
    000401000
    009205800
    804000107



## **Sample Output**

    143628579
    572139468
    986754231
    391542786
    468917352
    725863914
    237481695
    619275843
    854396127


## **题意**

给出一个16*16矩阵的部分格，其中0为空格，要求填充这些空格。

使矩阵满足横竖和九个3*3的方格内的数字都包含1~9这9个数字。



## **思路**

很基础的DFS，先存储当前每行每列和每块的数字状态，然后从左上角开始搜索，遇到零的时候向该点填充一个当前行、当前列、当前块都不存在的一个数字，若无法填充，则结束此层DFS，若可行，继续搜索下一层，直到搜索到右下角，标记已经找到答案，此时结束所有DFS，注意在结束的过程中要保留当前所填充的矩阵。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

int mapp[9][9];     //存储当前状态
bool isx[9][10],isy[9][10],iss[3][3][10],flag;  //行、列、块判断

void dfs(int y)
{
    if(y>=9)    //最后一个数是0的情况下若递归到这里，则说明全部填充完毕
    {
        flag=true;
        return;
    }
    for(int i=y; i<9; i++)  //从第y行开始，遍历剩下的点
        for(int j=0; j<9; j++)
        {
            if(mapp[i][j]==0)   //一个需要判断的点
            {
                bool isc=false;     //这一点是否可以被填充
                for(int k=1; k<=9; k++) //1-9
                    if(!isx[j][k]&&!isy[i][k]&&!iss[i/3][j/3][k])   //三种情况都满足
                    {
                        isc=true;   //假设可以填充
                        mapp[i][j]=k;   //填充的数是k
                        isx[j][k]=isy[i][k]=iss[i/3][j/3][k]=true;  //标记该位置
                        dfs(j!=8?y:y+1);
                        if(flag)return;     //找到答案返回，放在这里可以防止在层层结束递归的时候状态被还原
                        else isc=false;     //下层递归失败，标记该点不能填充
                        mapp[i][j]=0;       //还原状态
                        isx[j][k]=isy[i][k]=iss[i/3][j/3][k]=false;
                    }
                if(!isc)return;
            }
            else if(i==8&&j==8)     //最后一个点不是0的情况
            {
                flag=true;
                return;
            }
        }
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int ni=0; ni<n; ni++)
    {
        memset(isx,false,sizeof(isx));
        memset(isy,false,sizeof(isy));
        memset(iss,false,sizeof(iss));
        flag=false;
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
            {
                scanf("%1d",&mapp[i][j]);
                if(mapp[i][j])
                {
                    isx[j][mapp[i][j]]=true;
                    isy[i][mapp[i][j]]=true;
                    iss[i/3][j/3][mapp[i][j]]=true;
                }
            }
        dfs(0);
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                printf(j!=8?"%d":"%d\n",mapp[i][j]);
    }
    return 0;
}
```

