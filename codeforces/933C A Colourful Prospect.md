## C. A Colourful Prospect

## **Description**

> Firecrackers scare Nian the monster, but they're wayyyyy too noisy! Maybe fireworks make a nice complement.
>
> Little Tommy is watching a firework show. As circular shapes spread across the sky, a splendid view unfolds on the night of Lunar New Year's eve.
>
> A wonder strikes Tommy. How many regions are formed by the circles on the sky? We consider the sky as a flat plane. A region is a connected part of the plane with positive area, whose bound consists of parts of bounds of the circles and is a curve or several curves without self-intersections, and that does not contain any curve other than its boundaries. Note that exactly one of the regions extends infinitely.



## **Input**

> The first line of input contains one integer n (1 ≤ n ≤ 3), denoting the number of circles.
>
> The following n lines each contains three space-separated integers x, y and r ( - 10 ≤ x, y ≤ 10, 1 ≤ r ≤ 10), describing a circle whose center is (x, y) and the radius is r. No two circles have the same x, y and r at the same time.



## **Output**

> Print a single integer — the number of regions on the plane.



## **Examples input**

    3
    0 0 1
    2 0 1
    4 0 1



## **Examples output**

    4



## **题意**

给定平面内 n 个圆的信息，求这些圆把平面分成了几个区域。



## **思路**

久违的模板题佯~ 好开心~ 然而模板放在学校了哭唧唧 〒▽〒

---

求圆拆分平面有多少个区域怎么能离得开平面图的欧拉公式呢？

一般平面图欧拉公式：$f=e-v+c+1$

其中 $e$ 代表边的数量，$v$ 代表点的数量，$c$ 代表连通块的数量，$f$ 代表平面区域的个数

我们把圆弧看作边，交点看作顶点，于是很容易便可以算出 $e,v,c$ 啦~

对于 $e$ ，它相当于每个圆上交点的数量和（因为这些交点把圆拆分成了这么多的弧）

对于 $v$ ，枚举求出交点去重即可

对于 $c$ ，我们已经有了无向图的边，那连通块的数量可以直接 dfs/bfs 或者并查集算出来啦~

然后套用公式就是结果了，注意精度问题。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
typedef long double Ldb;
const int maxn = 10;
const Ldb eps = 1e-12;
int n;
struct Point
{
    Ldb x,y;
    Point() {}
    Point(Ldb _x,Ldb _y):x(_x),y(_y) {}
    Point operator + (const Point &t)const
    {
        return Point(x+t.x,y+t.y);
    }
    Point operator - (const Point &t)const
    {
        return Point(x-t.x,y-t.y);
    }
    Point operator * (const Ldb &t)const
    {
        return Point(x*t,y*t);
    }
    Point operator / (const Ldb &t)const
    {
        return Point(x/t,y/t);
    }
    bool operator < (const Point &t)const
    {
        return fabs(x-t.x) < eps ? y<t.y : x<t.x;
    }
    bool operator == (const Point &t)const
    {
        return fabs(x-t.x)<eps && fabs(y-t.y)<eps;
    }
    Ldb len()const
    {
        return sqrt(x*x+y*y);
    }
    Point rot90()const
    {
        return Point(-y,x);
    }
};

struct Circle
{
    Point o;
    Ldb r;
    Circle() {}
    Circle(Point _o,Ldb _r):o(_o),r(_r) {}
    friend vector<Point> operator & (const Circle &c1,const Circle &c2)
    {
        Ldb d=(c1.o-c2.o).len();
        if(d>c1.r+c2.r+eps || d<fabs(c1.r-c2.r)-eps)
            return vector<Point>();
        Ldb dt=(c1.r*c1.r-c2.r*c2.r)/d,d1=(d+dt)/2;
        Point dir=(c2.o-c1.o)/d,pcrs=c1.o+dir*d1;
        dt=sqrt(max(0.0L,c1.r*c1.r-d1*d1)),dir=dir.rot90();
        return vector<Point> {pcrs+dir*dt,pcrs-dir*dt};
    }
} p[maxn];
bool vis[maxn];
int fa[maxn],rk[maxn];
void init()
{
    for(int i=1; i<maxn; i++)
        fa[i] = i,rk[i] = 0;
}

int find_set(int x)
{
    if(fa[x]!=x)
        fa[x] = find_set(fa[x]);
    return fa[x];
}

void union_set(int x,int y)
{
    x = find_set(x);
    y = find_set(y);
    if(rk[x]>rk[y])
        fa[y] = x;
    else
    {
        fa[x] = y;
        if(rk[x]==rk[y])
            rk[y]++;
    }
}

int main()
{
    IO;
    init();
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>p[i].o.x>>p[i].o.y>>p[i].r;
    int e = 0,v = 0;
    vector<Point> all;
    for(int i=1; i<=n; i++)
    {
        vector<Point> tmp1;
        for(int j=1; j<=n; j++)
        {
            if(i==j)
                continue;
            vector<Point> tmp2 = p[i] & p[j];
            if(tmp2.size())
                union_set(i,j);
            tmp1.insert(tmp1.end(),tmp2.begin(),tmp2.end());
            all.insert(all.end(),tmp2.begin(),tmp2.end());
        }
        sort(tmp1.begin(),tmp1.end());
        e += unique(tmp1.begin(),tmp1.end()) - tmp1.begin();
    }
    sort(all.begin(),all.end());
    v = unique(all.begin(),all.end()) - all.begin();
    set<int> c;
    for(int i=1; i<=n; i++)
        c.insert(find_set(i));
    cout<<e-v+c.size()+1<<endl;
    return 0;
}
```

