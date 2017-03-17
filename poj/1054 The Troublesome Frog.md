# The Troublesome Frog

## **Description**

> In Korea, the naughtiness of the cheonggaeguri, a small frog, is legendary. This is a well-deserved reputation, because the frogs jump through your rice paddy at night, flattening rice plants. In the morning, after noting which plants have been flattened, you want to identify the path of the frog which did the most damage. A frog always jumps through the paddy in a straight line, with every hop the same length: 
>
> ![img](http://poj.org/images/1054/frog1.jpg)
>
> Your rice paddy has plants arranged on the intersection points of a grid as shown in Figure-1, and the troublesome frogs hop completely through your paddy, starting outside the paddy on one side and ending outside the paddy on the other side as shown in Figure-2: 
>
> ![img](http://poj.org/images/1054/frog2.jpg)
>
> Many frogs can jump through the paddy, hopping from rice plant to rice plant. Every hop lands on a plant and flattens it, as in Figure-3. Note that some plants may be landed on by more than one frog during the night. Of course, you can not see the lines showing the paths of the frogs or any of their hops outside of your paddy ?for the situation in Figure-3, what you can see is shown in Figure-4: 
>
> ![img](http://poj.org/images/1054/frog3.jpg)
>
> From Figure-4, you can reconstruct all the possible paths which the frogs may have followed across your paddy. You are only interested in frogs which have landed on at least 3 of your rice plants in their voyage through the paddy. Such a path is said to be a frog path. In this case, that means that the three paths shown in Figure-3 are frog paths (there are also other possible frog paths). The vertical path down column 1 might have been a frog path with hop length 4 except there are only 2 plants flattened so we are not interested; and the diagonal path including the plants on row 2 col. 3, row 3 col. 4, and row 6 col. 7 has three flat plants but there is no regular hop length which could have spaced the hops in this way while still landing on at least 3 plants, and hence it is not a frog path. Note also that along the line a frog path follows there may be additional flattened plants which do not need to be landed on by that path (see the plant at (2, 6) on the horizontal path across row 2 in Figure-4), and in fact some flattened plants may not be explained by any frog path at all. 
>
> Your task is to write a program to determine the maximum number of landings in any single frog path (where the maximum is taken over all possible frog paths). In Figure-4 the answer is 7, obtained from the frog path across row 6. 



## **Input**

> Your program is to read from standard input. The first line contains two integers R and C, respectively the number of rows and columns in your rice paddy, 1 <= R,C <= 5000. The second line contains the single integer N, the number of flattened rice plants, 3 <= N <= 5000. Each of the remaining N lines contains two integers, the row number (1 <= row number <= R) and the column number (1 <= column number <= C) of a flattened rice plant, separated by one blank. Each flattened plant is only listed once.



## **Output**

> Your program is to write to standard output. The output contains one line with a single integer, the number of plants flattened along a frog path which did the most damage if there exists at least one frog path, otherwise, 0.



## **Sample Input**

    6 7
    14
    2 1
    6 6
    4 2
    2 5
    2 6
    2 7
    3 4
    6 1
    6 2
    2 3
    6 3
    6 4
    6 5
    6 7



## **Sample Output**

    7



## **题意**

青蛙需要沿着直线踩着踏点通过田地，并且踏点需要至少为3。

问哪条路径青蛙踩坏的作物最多，很好的一个条件是青蛙每次移动都是等间距的。



## **思路**

**枚举+剪枝**

首先对所有踏点按照x坐标大小排序，然后分别用两个变量i j来代表青蛙跳的过程中的前两个点。

**则这两个点之间的间距：** `dx=a[j].x-a[i].x` 、 `dy=a[j].y-a[i].y` 

- 假如用两点的间距计算出i前面一个点不在界内，则重新挑选点进行计算。
- 假如用这两点间距以及已知的最大踩坏作物的数量来计算，当前所允许的最后一个点不在界内，跳出。

否则使用当前间距尝试扩充ans。



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

#define MAXN 5010
bool G[MAXN][MAXN];
int row,col,N;

struct node
{
    int x,y;
    bool operator<(const node &o)
    {
        if(x==o.x)return y<o.y;
        return x<o.x;
    }
} a[MAXN];

bool judge(int x,int y) //判断当前点是否在界内
{
    if(x>0&&x<=row&&y>0&&y<=col)
        return true;
    return false;
}

int solve()
{
    int ans=2;
    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++)
        {
            int dx=a[j].x-a[i].x;       //间距
            int dy=a[j].y-a[i].y;
            if(a[j].x+(ans-2)*dx>row)   //如果试探之后发现青蛙一定会在界外，则剪枝
                break;
            if(a[j].y+(ans-2)*dy>col||a[j].y+(ans-2)*dy<1)
                continue;
            if(judge(a[i].x-dx,a[i].y-dy))  //如果前一个点也在范围内，则排除
                continue;
            int t=1;
            int x=a[j].x,y=a[j].y;
            while(judge(x,y)&&G[x][y])      //扩充当前点集数目
                x+=dx,y+=dy,t++;
            if(!judge(x+dx,y+dy))           //如果扩充之后青蛙可以正常跳出去，更新ans
                ans=max(ans,t);
        }
    return ans>2?ans:0;
}

int main()
{
    while(~scanf("%d%d",&row,&col))
    {
        scanf("%d",&N);
        memset(G,false,sizeof(G));
        for(int i=0; i<N; i++)
        {
            scanf("%d%d",&a[i].x,&a[i].y);
            G[a[i].x][a[i].y]=true;         //标记这些点被青蛙踩过
        }
        sort(a,a+N);
        printf("%d\n",solve());
    }
    return 0;
}
```

