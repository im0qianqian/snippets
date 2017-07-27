# Regular polygon

## **Description**

> On a two-dimensional plane, give you n integer points. Your task is to figure out how many different regular polygon these points can make.



## **Input**

> The input file consists of several test cases. Each case the first line is a numbers N (N <= 500). The next N lines ,each line contain two number Xi and Yi(-100 <= xi,yi <= 100), means the points’ position.(the data assures no two points share the same position.)



## **Output**

> For each case, output a number means how many different regular polygon these points can make.



## **Sample Input**

    4
    0 0
    0 1
    1 0
    1 1
    6
    0 0
    0 1
    1 0
    1 1
    2 0
    2 1



## **Sample Output**

    1
    2



## **题意**

给出平面内 n 个点，问其中四个点组成正方形总共有多少种情况。



## **思路**

因为 $n≤500$  ，所以我们枚举四个点的话会超时间。

寻找正方形，那么只需要知道其中相对的两个点便可以算出另外两个点咯！

所以我们只需要枚举其中两个点，然后计算出另外两个点的坐标，如果这两个点出现过则找到正方形，否则未找到。

在判断点是否出现过我们可以采用**二分**或者**哈希**等方法。



## **AC 代码**

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include<iostream>
using namespace std ;

#define eps 1e-7
struct node
{
    double x,y;
} p[510];
int n;

bool cmp(node a,node b)
{
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}

bool judge(double x,double y)       // 二分查找
{
    int low=0,high=n-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(fabs(p[mid].x-x)<eps&&fabs(p[mid].y-y)<eps)
            return true;
        else if(p[mid].x-x>eps||(fabs(p[mid].x-x)<eps&&p[mid].y-y>eps))
            high=mid-1;
        else low=mid+1;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    while(cin>>n)
    {
        int ans=0;
        for(int i=0; i<n; i++)
            cin>>p[i].x>>p[i].y;
        sort(p,p+n,cmp);
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(i==j)continue;
                double xa=(p[i].x+p[j].x)/2.0;
                double ya=(p[i].y+p[j].y)/2.0;
                double xb=p[i].x-xa;
                double yb=p[i].y-ya;
                if(judge(xa+yb,ya-xb)&&judge(xa-yb,ya+xb))
                    ans++;
            }
        }
        cout<<ans/2<<endl;
    }
    return 0;
}
```

