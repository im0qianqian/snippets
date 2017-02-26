# Skip the Class

## **问题描述**

> 终于又开学啦。呃喵最喜欢的就是开学了，因为这样她又可以愉快地翘课了（啊？）
>
> 呃喵接下来有n节课程需要上（换句话说，可以翘。）
>
> 每节课程有相应的课程类型与课程翘课价值。
>
> 有一点需要注意的是，呃喵不可以翘同一类课程超过两次，就是如果这类课已经翘了两次，接下来就一定要上。
>
> 问你在这个条件下，呃喵可以获得的最大翘课价值。



## **输入描述**

> 第一行为一个整数T，代表数据组数。
>
> 接下来，对于每组数据——
>
> 第一行一个整数n，表示接下来需要依次上的课程数量，
>
> 接下来有n行，每行包括一个仅由'a'~'z'构成的长度不超过10的字符串s与一个正整数v。
>
> 其中字符串表示课程的类型，相同的字符串代表相同的课程。
>
> 数据保证——
>
> 1 <= T <= 1000
>
> 对于每组数据，1 <= n <= 100，1 <= |s| <= 10, 1 <= v <= 1000



## **输出描述**

> 对于每组数据，输出一行。
>
> 该行有1个整数，表示呃喵可以获得的最大翘课价值。



## **输入样例**

    2
    5
    english 1
    english 2
    english 3
    math 10
    cook 100
    2
    a 1
    a 2



## **输出样例**

    115
    3


## **思路**

只需要把同一种课程的按照价值排序，挑选最大的两个逃掉，或者选择最大的一个，然后把这些相加便是最大翘课价值。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<map>

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,v;
        char str[15];
        cin>>n;
        map<string,priority_queue<int> >sk; //课程名称与价值优先队列的映射
        for(int i=0; i<n; i++)
        {
            cin>>str>>v;
            sk[str].push(v);
        }
        int ans=0;
        for(map<string,priority_queue<int> >::iterator i=sk.begin(); i!=sk.end(); i++)
        {
            int maxx=0;
            while(maxx++<2&&!sk[i->first].empty())
            {
                ans+=sk[i->first].top();
                sk[i->first].pop();
            }
        }
        cout<<ans<<endl;
    }
}
```

