# D. Driving Test

## **Description**

> Polycarp has just attempted to pass the driving test. He ran over the straight road with the signs of four types.
>
> - speed limit: this sign comes with a positive integer number — maximal speed of the car after the sign (cancel the action of the previous sign of this type);
> - overtake is allowed: this sign means that after some car meets it, it can overtake any other car;
> - no speed limit: this sign cancels speed limit if any (car can move with arbitrary speed after this sign);
> - no overtake allowed: some car can't overtake any other car after this sign.
>
> Polycarp goes past the signs consequentially, each new sign cancels the action of all the previous signs of it's kind (speed limit/overtake). It is possible that two or more "no overtake allowed" signs go one after another with zero "overtake is allowed" signs between them. It works with "no speed limit" and "overtake is allowed" signs as well.
>
> In the beginning of the ride overtake is allowed and there is no speed limit.
>
> You are given the sequence of events in chronological order — events which happened to Polycarp during the ride. There are events of following types:
>
> 1. Polycarp changes the speed of his car to specified (this event comes with a positive integer number);
> 2. Polycarp's car overtakes the other car;
> 3. Polycarp's car goes past the "speed limit" sign (this sign comes with a positive integer);
> 4. Polycarp's car goes past the "overtake is allowed" sign;
> 5. Polycarp's car goes past the "no speed limit";
> 6. Polycarp's car goes past the "no overtake allowed";
>
> It is guaranteed that the first event in chronological order is the event of type 1 (Polycarp changed the speed of his car to specified).
>
> After the exam Polycarp can justify his rule violations by telling the driving instructor that he just didn't notice some of the signs. What is the minimal number of signs Polycarp should say he didn't notice, so that he would make no rule violations from his point of view?



## **Input**

> The first line contains one integer number n (1 ≤ n ≤ 2·10^5) — number of events.
>
> Each of the next n lines starts with integer t (1 ≤ t ≤ 6) — the type of the event.
>
> An integer s (1 ≤ s ≤ 300) follows in the query of the first and the third type (if it is the query of first type, then it's new speed of Polycarp's car, if it is the query of third type, then it's new speed limit).
>
> It is guaranteed that the first event in chronological order is the event of type 1 (Polycarp changed the speed of his car to specified).



## **Output**

> Print the minimal number of road signs Polycarp should say he didn't notice, so that he would make no rule violations from his point of view.



## **Examples input**

    11
    1 100
    3 70
    4
    2
    3 120
    5
    3 120
    6
    1 150
    4
    3 300



## **Examples output**

    2



## **题意**

在开车时有 6 种情况：

1. 改变速度
2. 超车
3. 限速（路标）
4. 允许超车（路标）
5. 无限速（路标）
6. 不允许超车（路标）

现在问，主角在向教练解释时最少需要忽略多少个路标才可以保证他没有违规。



## **思路**

简单模拟题，随便写写就可以啦~

注意多个限速的路标后者会覆盖前者的数值。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef __int64 LL;
const int maxn = 2e5+10;

int n;
int speed;
int overtakes;
vector<int> speedlimit;

int main()
{
    IO;
    cin>>n;
    int ans = 0;
    for(int i=0; i<n; i++)
    {
        int op,x;
        cin>>op;
        switch(op)
        {
        case 1:     //变速
            cin>>speed;
            for(int s = speedlimit.size()-1; s>=0; s--)
            {
                if(speedlimit[s]>=speed)
                    break;
                else
                {
                    ++ans;
                    speedlimit.pop_back();
                }
            }
            break;
        case 2:     //超车
            ans+=overtakes;
            overtakes = 0;
            break;
        case 3:     //限速
            cin>>x;
            if(x<speed)
                ++ans;
            else
                speedlimit.push_back(x);
            break;
        case 4:     //允许超车
            overtakes = 0;
            break;
        case 5:     //无限速
            speedlimit.clear();
            break;
        case 6:     //不允许超车
            ++overtakes;
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

