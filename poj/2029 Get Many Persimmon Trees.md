# Get Many Persimmon Trees

## **Description**

> Seiji Hayashi had been a professor of the Nisshinkan Samurai School in the domain of Aizu for a long time in the 18th century. In order to reward him for his meritorious career in education, Katanobu Matsudaira, the lord of the domain of Aizu, had decided to grant him a rectangular estate within a large field in the Aizu Basin. Although the size (width and height) of the estate was strictly specified by the lord, he was allowed to choose any location for the estate in the field. Inside the field which had also a rectangular shape, many Japanese persimmon trees, whose fruit was one of the famous products of the Aizu region known as 'Mishirazu Persimmon', were planted. Since persimmon was Hayashi's favorite fruit, he wanted to have as many persimmon trees as possible in the estate given by the lord. 
>
> For example, in Figure 1, the entire field is a rectangular grid whose width and height are 10 and 8 respectively. Each asterisk (*) represents a place of a persimmon tree. If the specified width and height of the estate are 4 and 3 respectively, the area surrounded by the solid line contains the most persimmon trees. Similarly, if the estate's width is 6 and its height is 4, the area surrounded by the dashed line has the most, and if the estate's width and height are 3 and 4 respectively, the area surrounded by the dotted line contains the most persimmon trees. Note that the width and height cannot be swapped; the sizes 4 by 3 and 3 by 4 are different, as shown in Figure 1. 
>
> ![img](http://poj.org/images/2029_1.jpg)
>
> Figure 1: Examples of Rectangular Estates
>
> Your task is to find the estate of a given size (width and height) that contains the largest number of persimmon trees.



## **Input**

> The input consists of multiple data sets. Each data set is given in the following format. 
>
> N 
> W H 
> x1 y1 
> x2 y2 
> ... 
> xN yN 
> S T 
>
> N is the number of persimmon trees, which is a positive integer less than 500. W and H are the width and the height of the entire field respectively. You can assume that both W and H are positive integers whose values are less than 100. For each i (1 <= i <= N), xi and yi are coordinates of the i-th persimmon tree in the grid. Note that the origin of each coordinate is 1. You can assume that 1 <= xi <= W and 1 <= yi <= H, and no two trees have the same positions. But you should not assume that the persimmon trees are sorted in some order according to their positions. Lastly, S and T are positive integers of the width and height respectively of the estate given by the lord. You can also assume that 1 <= S <= W and 1 <= T <= H. 
>
> The end of the input is indicated by a line that solely contains a zero. 



## **Output**

> For each data set, you are requested to print one line containing the maximum possible number of persimmon trees that can be included in an estate of the given size.



## **Sample Input**

    16
    10 8
    2 2
    2 5
    2 7
    3 3
    3 8
    4 2
    4 5
    4 8
    6 4
    6 7
    7 5
    7 8
    8 1
    8 4
    9 6
    10 3
    4 3
    8
    6 4
    1 2
    2 1
    2 4
    3 4
    4 2
    5 3
    6 1
    6 2
    3 2
    0



## **Sample Output**

    4
    3


## **题意**

给出一张地图，以及所有树的位置，然后给出矩形的大小，问地图中可以被这个矩形最多圈进多少棵树。



## **思路**

考虑到数据范围比较小的关系，所以直接枚举即可。

`sum[i][j]` 代表从 `(1,1)` 到 `(i,j)` 范围内树的个数。

所以利用这个便可以求得地图中任意矩形的权值啦！

输入矩形大小，枚举，找最大值即可。



## **AC 代码**

```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stdio.h>
#include<algorithm>
#include<stack>
using namespace std;
#define INF (1<<25)

int sum[105][105],data[105][105],ans;

int get(int a,int b,int x,int y)    //获取 (a,b) 到 (x,y) 矩形中树的个数
{
    return sum[x][y]-sum[x][b-1]-sum[a-1][y]+sum[a-1][b-1];
}

int main()
{
    int N,W,H,x,y;
    while(~scanf("%d",&N)&&N)
    {
        scanf("%d%d",&W,&H);
        ans=0;
        memset(sum,0,sizeof(sum));
        memset(data,0,sizeof(data));
        for(int i=0; i<N; i++)  //标记有树的位置值为1
        {
            scanf("%d%d",&y,&x);
            data[x][y]=1;
        }
        for(int i=1; i<=H; i++)
            for(int j=1; j<=W; j++) //求从 (1,1) 到 (i,j) 矩形中树的个数
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+data[i][j];
        scanf("%d%d",&y,&x);
        for(int i=x; i<=H; i++)
            for(int j=y; j<=W; j++) //枚举满足大小的所有矩形
                ans=max(ans,get(i-x+1,j-y+1,i,j));
        printf("%d\n",ans);
    }
    return 0;
}
```

