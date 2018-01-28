# 2219 StarCraft

## **Description**

> ZB loves playing StarCraft and he likes Zerg most!
>
> One day, when ZB was playing SC2, he came up with an idea:
>
> He wants to change the queen's ability, the queen's new ability is to choose a worker at any time, and turn it into an egg, after K units of time, two workers will born from that egg. The ability is not consumed, which means you can use it any time without cooling down.
>
> Now ZB wants to build N buildings, he has M workers initially, the i-th building costs t[i] units of time, and a worker will die after he builds a building. Now ZB wants to know the minimum time to build all N buildings.



## **Input**

> The first line contains an integer T, meaning the number of the cases. 1 <= T <= 50.
>
> For each test case, the first line consists of three integers N, M and K. (1 <= N, M <= 100000, 1 <= K <= 100000).
>
> The second line contains N integers t[1] ... t[N] (1 <= t[i] <= 100000).



## **Output**

> For each test case, output the answer of the question.



## **Sample Input**

    2
    3 1 1
    1 3 5
    5 2 2
    1 1 1 1 10



## **Sample Output**

    6
    10



## **题意**

有 m 个员工，一共要建 n 个建筑，每个建筑需要 ti 的时间，一个员工只能建一个建筑，对于某个员工可以用 k 的时间将其一分为二，求建完 n 个建筑的最少时间。



## **思路**

- 当初始员工数目 m 大于等于建筑数目 n ，显然结果是所有建筑建筑时间的最大值。
- 对于其他情况，我们需要工人总共分裂 m-n 次，此时便需要考虑哪两个建筑是由一个工人分裂以后解决的，显然可以像类似于哈夫曼树那样找当前状态下两个建筑时间最小的，然后将较大者 +k 放回树中，较小者去除。（因为较大者 + k > 较小者）



## **代码**

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <queue>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
const int maxn = 1e6+10;
const int mod = 1e9+7;
typedef long long LL;

int n,m,k;
priority_queue<int,vector<int>,greater<int> > sk;
int main()
{
    IO;
    int T;
    cin>>T;
    while(T--)
    {
        while(!sk.empty())sk.pop();
        cin>>n>>m>>k;
        for(int i=0; i<n; i++)
        {
            int x;
            cin>>x;
            sk.push(x);
        }
        int some = n - m;
        while(some>0)
        {
            sk.pop();
            sk.push(sk.top()+k);
            sk.pop();
            some--;
        }
        while(sk.size()>1)
            sk.pop();
        cout<<sk.top()<<endl;
    }
    return 0;
}
```

