# Requirements

## **Description**

> An undergraduate student, realizing that he needs to do research to improve his chances of being accepted to graduate school, decided that it is now time to do some independent research. Of course, he has decided to do research in the most important domain: the requirements he must fulfill to graduate from his undergraduate university. First, he discovered (to his surprise) that he has to fulfill 5 distinct requirements: the general institute requirement, the writing requirement, the science requirement, the foreign-language requirement, and the field-of-specialization requirement. Formally, a requirement is a fixed number of classes that he has to take during his undergraduate years. Thus, for example, the foreign language requirement specifies that the student has to take 4 classes to fulfill this requirement: French I, French II, French III, and French IV. Having analyzed the immense multitude of the classes that need to be taken to fulfill the different requirements, our student became a little depressed about his undergraduate university: there are so many classes to take…
>
> Dejected, the student began studying the requirements of other universities that he might have chosen after high school. He found that, in fact, other universities had exactly the same 5 requirements as his own university. The only difference was that different universities had different number of classes to be satisfied in each of the five requirement.
>
> Still, it appeared that universities have pretty similar requirements (all of them require a lot of classes), so he hypothesized that no two universities are very dissimilar in their requirements. He defined the dissimilarity of two universities X and Y as |x1 − y1| + |x2 − y2| + |x3 − y3| + |x4 − y4| + |x5 − y5|, where an xi (yi) is the number of classes in the requirement i of university X (Y) multiplied by an appropriate factor that measures hardness of the corresponding requirement at the corresponding university.



## **Input**

> The first line of the input file contains an integer N (1 ≤ N ≤ 100 000), the number of considered universities. The following N lines each describe the requirements of a university. A university X is described by the five non-negative real numbers x1 x2 x3 x4 x5.



## **Output**

> On a single line, print the dissimilarity value of the two most dissimilar universities. Your answer should be rounded to exactly two decimal places.



## **Sample Input**

    3
    2 5 6 2 1.5
    1.2 3 2 5 4
    7 5 3 2 5



## **Sample Output**

    12.80



## **题意**

给出五维空间 `N` 个点的坐标，求其中两点的最大曼哈顿距离。



## **思路**

我们可以定义**曼哈顿距离**的正式意义为**L1-距离**或**城市区块距离**，也就是在欧几里得空间的固定直角坐标系上两点所形成的线段对轴产生的投影的距离总和。

![img](https://www.dreamwings.cn/wp-content/uploads/2017/05/3386412796.jpg)

例如在平面上，坐标 $(x_1,y_1)$ 的点 $P_1$ 与坐标 $(x_2,y_2)$ 的点 $P_2$ 的曼哈顿距离为： $|x_1-x_2|+|y_1-y_2|$

---

在二维平面中，设距离最远的两点坐标为 $(a_1,b_1)~(a_2,b_2)$ 则其曼哈顿距离为： $|a_1-a_2|+|b_1-b_2|$ 

**去掉绝对值便有四种形式：**

- $(a_1-a_2)+(b_1-b_2)$
- $(a_1-a_2)+(b_2-b_1)$
- $(a_2-a_1)+(b_1-b_2)$
- $(a_2-a_1)+(b_2-b_1)$

**可以对上面的式子变形整理一下转化为：**

- $(a_1+b_1)-(a_2+b_2)$
- $(a_1-b_1)-(a_2-b_2)$
- $(-a_1+b_1)-(-a_2+b_2)$
- $(-a_1-b_1)-(-a_2-b_2)$

我们发现每一项对应坐标的符号都相同，于是可以假设 `1` 代表正号， `0` 代表负号，于是 $(a_1+b_1)$ 可以表示为 `11` 。

要表示空间中所有状态，只需要用 `0~1<<dem` 的所有二进制便可以啦~

于是对所有的点，求出上面的那四种转化过的形式，记录每种状态的最小值与最大值，枚举找最大差值即可。



## **AC 代码**

```cpp
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iomanip>
using namespace std;
const double INF = 1e200;
const int d=5;
double a[d];
double maxx[1<<d],minn[1<<d];

void insert()
{
    for(int i=0; i<1<<d; i++)
    {
        double now=0;
        for(int j=0; j<d; j++)
        {
            if((1<<j)&i)now+=a[j];
            else now-=a[j];
        }
        maxx[i]=max(maxx[i],now);
        minn[i]=min(minn[i],now);
    }
}

void init()
{
    for(int i=0; i<1<<d; i++)
    {
        maxx[i]=-INF;
        minn[i]=INF;
    }
}

int main()
{
    int N;
    while(~scanf("%d",&N))
    {
        init();
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<d; j++)
                scanf("%lf",a+j);
            insert();
        }
        double ans=-INF;
        for(int i=0; i<1<<d; i++)
            ans=max(ans,maxx[i]-minn[i]);
        printf("%.2f\n",ans);
    }
    return 0;
}
```

