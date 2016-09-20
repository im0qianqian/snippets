/*
POJ 1113 Wall

题意：给出平面内指定多个点，求与它们所围成的区域相距为d的最少线段长度，也就是围成凸包的边长+半径为d的圆的周长~

思想：
    先对这N个点进行排序，排序的依据有两种，一种是按照纵坐标优先，横坐标次之由小到大排序，另一种是极角排序，它需要找到平面内最左下角的点，然后以该点为起点，连接其他点，由其两点之间与x轴夹角，从下到上排序
    排序完成之后，我们需要一个栈
    逆时针或者顺时针每次检测三个点，用叉积判断这三个点所连接的两个线段是左转还是右转，若左转，入栈，若右转，说明此时为凹。则让第二个点出栈，第三个点入栈，别忘了每一次检测都要向后扫描
    检测完之后栈中便是凸包各个顶点的坐标。
    按照顺序求每两点距离，然后相加
    计算圆的周长
    AC
*/

#include<iostream>
#include<algorithm>
#include<cmath>
#include<stdio.h>
using namespace std;
#define PI acos(-1)
struct point
{
    double x;
    double y;
    double distance(const point &b)const    //计算距离
    {
        return hypot(x-b.x,y-b.y);
    }
} ;
point a[1005];
struct stack
{
    point data[1005];
    int top;
} st;
point minn;
int crossLeft(point p0,point p1,point p2)   //判读左转还是右转
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
bool cmp(point p1,point p2)
{
    int tmp=crossLeft(a[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0&&a[0].distance(p1)<a[0].distance(p2))return true;
    else return false;
}
void init(int n)
{
    int i,k=0;
    point p;
    cin>>a[0].x>>a[0].y;
    p.x=a[0].x;
    p.y=a[0].y;
    for(i=1; i<n; i++)
    {
        cin>>a[i].x>>a[i].y;
        if( (p.y>a[i].y) || ((p.y==a[i].y)&&(p.x>a[i].x)) )
        {
            p.x=a[i].x;
            p.y=a[i].y;
            k=i;
        }
    }
    a[k]=a[0];
    a[0]=p;
    sort(a+1,a+n,cmp);
}
int main()
{
    int N,L;
    cout.sync_with_stdio(false);        //解除同步
    while(cin>>N>>L)
    {
        init(N);
        for(int i=0; i<2; i++)
            st.data[i]=a[i];            //前两个点入栈
        st.top=1;
        for(int i=2; i<N; i++)
        {
            st.data[++st.top]=a[i];     //新点进栈
            while(st.top>1&&crossLeft(st.data[st.top-2],st.data[st.top-1],st.data[st.top])<=0)  //向后遍历判断是否存在凹的区域
                st.data[st.top-1]=st.data[st.top],st.top--;                                     //存在，出栈一个点
        }
        double l=0.0;
        for(int i=0; i<st.top; i++)
            l+=st.data[i].distance(st.data[i+1]);           //求长度
        l+=st.data[st.top].distance(st.data[0])+2*PI*L;     //圆的周长
        printf("%d\n",(int)(l+0.5));
    }
}
