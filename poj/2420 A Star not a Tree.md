# A Star not a Tree?

## **Description**

> Luke wants to upgrade his home computer network from 10mbs to 100mbs. His existing network uses 10base2 (coaxial) cables that allow you to connect any number of computers together in a linear arrangement. Luke is particulary proud that he solved a nasty NP-complete problem in order to minimize the total cable length.
>
> Unfortunately, Luke cannot use his existing cabling. The 100mbs system uses 100baseT (twisted pair) cables. Each 100baseT cable connects only two devices: either two network cards or a network card and a hub. (A hub is an electronic device that interconnects several cables.) Luke has a choice: He can buy 2N-2 network cards and connect his N computers together by inserting one or more cards into each computer and connecting them all together. Or he can buy N network cards and a hub and connect each of his N computers to the hub. The first approach would require that Luke configure his operating system to forward network traffic. However, with the installation of Winux 2007.2, Luke discovered that network forwarding no longer worked. He couldn't figure out how to re-enable forwarding, and he had never heard of Prim or Kruskal, so he settled on the second approach: N network cards and a hub.
>
> Luke lives in a loft and so is prepared to run the cables and place the hub anywhere. But he won't move his computers. He wants to minimize the total length of cable he must buy.



## **Input**

> The first line of input contains a positive integer N <= 100, the number of computers. N lines follow; each gives the (x,y) coordinates (in mm.) of a computer within the room. All coordinates are integers between 0 and 10,000.



## **Output**

> Output consists of one number, the total length of the cable segments, rounded to the nearest mm.



## **Sample Input**

    4
    0 0
    0 10000
    10000 10000
    10000 0



## **Sample Output**

    28284


## **题意**

给出平面内一个点集，让你求平面内一点距离这些点距离和的最小值~



## **思路**

好像**退火模拟**问题哎~

可惜我不会o(╯□╰)o

只能用**爬山算法**做了，爬山算法讲的是首先在平面内选一点，判断它临近的点所求得的距离和是否比它小，若小，更新点的坐标。

就这样，不过它也存在很大的局限性，如在高峰处无法选择下一点应该去哪儿，只是**局部最优**而已。

我们可以选择自己控制循环次数，类似于随机数之类的，然后根据大数据的判断比较，然后得出最终答案。



## **AC 代码**

```cpp
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#define eps 1e-6
using namespace std;
struct point
{
    double x;
    double y;
    void input()                //输入
    {
        cin>>x>>y;
    }
    double dis(point k)         //求两点之间距离
    {
        return sqrt((x-k.x)*(x-k.x)+(y-k.y)*(y-k.y));
    }
} a[105];
double getsum(point k,int n)    //求距离和
{
    double s=0;
    for(int i=0; i<n; i++)
        s+=k.dis(a[i]);
    return s;
}
int main()
{
    int n;
    while(cin>>n)
    {
        point one;
        one.x=one.y=0;
        for(int i=0; i<n; ++i)
        {
            a[i].input();
            one.x+=a[i].x;
            one.y+=a[i].y;
        }
        one.x/=n;
        one.y/=n;           //选择一个靠中的点
        double ans=getsum(one,n);
        double t=10000;
        while(t>eps)        //循环次数
        {
            double x=0,y=0;
            for(int i=0; i<n; ++i)  //选取临近点
            {
                x+=(a[i].x-one.x)/one.dis(a[i]);
                y+=(a[i].y-one.y)/one.dis(a[i]);
            }
            point ttm;
            ttm.x=one.x+x*t;
            ttm.y=one.y+y*t;
            double tmp=getsum(ttm,n);
            if(tmp<ans)         //判断大小
            {
                ans=tmp;
                one.x+=x*t;
                one.y+=y*t;
            }
            t*=0.99;
        }
        printf("%.0f\n",ans);
    }
    return 0;
}
```

