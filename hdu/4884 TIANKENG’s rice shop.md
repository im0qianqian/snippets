# TIANKENG’s rice shop

## **Problem Description**

> TIANKENG managers a pan fried rice shop. There are n kinds of fried rice numbered 1-n. TIANKENG will spend t time for once frying. Because the pan is so small, TIANKENG can fry k bowls of fried rice with same kind at most. Assuming that there are m customers coming to the shop, and we know the arriving time of each customer and the brand and number of the fried rice they need. Could you tell TIANKENG the departure time of every customer respectively? Pay attention that TIANKNEG will serve the customer who comes earlier and he will fry the rice as much as possible. Meanwhile, customers are in queue depending on their arriving time(the earlier they arrive, the more front they stand).



## **Input**

> The first line contains a positive integer T(T<=100), referring to T test cases. For each test case, the first line has 4 positive integer n(1<=n<=1000), t(1<=t<=10), k(1<=k<=5), m(1<=m<=1000), then following m lines , each line has a time(the time format is hh:mm, 0<=hh<=23, 0<=mm<=59) and two positive integer id(1<=id<=n), num(1<=num<=10), which means the brand number of the fried rice and the number of the fried rice the customer needs. Pay attention that two or more customers will not come to the shop at the same time, the arriving time of the customer will be ordered by the time(from early time to late time)



## **Output**

> For each test case print m lines, each line contains a time referring to the departure time of the customer. There is a blank line between two test cases.



## **Sample Input**

    3
    2 1 4 2
    08:00 1 5
    09:00 2 1
    2 5 4 3
    08:00 1 4
    08:01 2 2
    08:02 2 2
    2 5 4 2
    08:00 1 1
    08:04 1 1



## **Sample Output**

    08:02
    09:01
    
    08:05
    08:10
    08:10
    
    08:05
    08:10


## **题意**

有n种炒饭，每次炒的时间是t分钟，每次最多炒k份，然后按照进店的顺序给出m个顾客的信息，进店时间，炒饭编号以及份数，输出每个顾客离开的时间。



## **思路**

顾客是先来先服务，并且每次会尽可能多的去炒。

我们可以存储上次炒饭可以容纳的份数以及开炒时间，如果时间晚于当前顾客的到来时间，则把当前顾客的份添加进去一起做，如果有剩余的份，则单独计算离开时间，并维护存储这两个值。



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
#include<stack>

int sk[1100],lt[1100];
int main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1; ti<=T; ti++)
    {
        int n,t,k,m,time=0;
        scanf("%d%d%d%d",&n,&t,&k,&m);
        memset(sk,0,sizeof(sk));    //上次炒饭还可以容纳的份数
        memset(lt,0,sizeof(lt));    //上次炒饭开始的时间
        for(int i=0; i<m; i++)
        {
            int hour,minutm,id,num,ci;
            scanf("%d%*c%d%d%d",&hour,&minutm,&id,&num);
            hour=hour*60+minutm;
            if(lt[id]>=hour)        //如果顾客早于开始炒饭的时间
            {
                if(sk[id]>=num)     //当前顾客的份可以加到前面一起炒
                {
                    sk[id]-=num;
//                    cout<<lt[id]+t<<endl;
                    int time=(lt[id]+t)%1440;   //因为可能会到第二天，所以需要%1440
                    printf("%02d:%02d\n",time/60,time%60);
                    continue;
                }
                else num-=sk[id];   //当前顾客部分份和前面的一起
            }
            ci=(num-1)/k+1;         //还需要几次
            time=max(time,hour)+t*ci;   //计算离开的时间
            printf("%02d:%02d\n",(time%1440)/60,(time%1440)%60);
            if(num%k==0)sk[id]=0;   //如果炒的过程中没有多余
            else sk[id]=k-num%k;    //还可以添加几份一起炒
            lt[id]=time-t;          //当前开始炒饭时间
        }
        if(ti!=T)printf("\n");
    }
    return 0;
}
```

