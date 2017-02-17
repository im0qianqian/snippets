# Radar Installation

## **Description**

> Assume the coasting is an infinite straight line. Land is in one side of coasting, sea in the other. Each small island is a point locating in the sea side. And any radar installation, locating on the coasting, can only cover d distance, so an island in the sea can be covered by a radius installation, if the distance between them is at most d. 
>
> We use Cartesian coordinate system, defining the coasting is the x-axis. The sea side is above x-axis, and the land side below. Given the position of each island in the sea, and given the distance of the coverage of the radar installation, your task is to write a program to find the minimal number of radar installations to cover all the islands. Note that the position of an island is represented by its x-y coordinates. 
>
> ![img](http://poj.org/images/1328_1.jpg)
>
> Figure A Sample Input of Radar Installations



## **Input**

> The input consists of several test cases. The first line of each case contains two integers n (1<=n<=1000) and d, where n is the number of islands in the sea and d is the distance of coverage of the radar installation. This is followed by n lines each containing two integers representing the coordinate of the position of each island. Then a blank line follows to separate the cases. 
>
> The input is terminated by a line containing pair of zeros 



## **Output**

> For each test case output one line consisting of the test case number followed by the minimal number of radar installations needed. "-1" installation means no solution for that case.



## **Sample Input**

    3 2
    1 2
    -3 1
    2 1
    
    1 2
    0 2
    
    0 0



## **Sample Output**

    Case 1: 2
    Case 2: 1



## **题意**

海上有n多岛，在海岸线上（x轴）建一个雷达能覆盖到与它距离不超过d的岛，求覆盖所有岛的最小雷达数。



## **思路**

以岛屿为圆心，d为半径画圆，交x轴于s,e两点，然后以线段末尾为排序标准对所有这样的线段排序，从左至右依次判断，假设雷达放置在一个线段的末端，然后忽略它所能涉及到的岛屿。



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

struct point
{
    double x,y;
    double s,e;
    bool operator<(const point &o)const
    {
        return e<o.e;
    }
} land[1005];

int solve(int n,int d)
{
    for(int i=0; i<n; i++)  //计算所有的线段
    {
        double t=sqrt(d-land[i].y*land[i].y);
        land[i].s=land[i].x-t;
        land[i].e=land[i].x+t;
    }   
    sort(land,land+n);      //排序
    int ans=1;
    double r=land[0].e;
    for(int i=1; i<n; i++)
    {
        if(land[i].s>r)
        {
            ++ans;
            r=land[i].e;
        }
    }
    return ans;
}

int main()
{
    int n,d,cat=1;
    while(~scanf("%d%d",&n,&d)&&(n||d))
    {
        bool flag=false;
        for(int i=0; i<n; i++)
        {
            scanf("%lf%lf",&land[i].x,&land[i].y);
            if(land[i].y>d)flag=true;   //是否可以检测到该岛屿
        }
        if(flag)printf("Case %d: -1\n", cat++);
        else printf("Case %d: %d\n", cat++, solve(n,d*d));
    }
    return 0;
}
```

