# CaoHaha's staff

## **Description**

> "You shall not pass!"
>
> After shouted out that,the Force Staff appered in CaoHaha's hand.
>
> As we all know,the Force Staff is a staff with infinity power.If you can use it skillful,it may help you to do whatever you want.
>
> But now,his new owner,CaoHaha,is a sorcerers apprentice.He can only use that staff to send things to other place.
>
> Today,Dreamwyy come to CaoHaha.Requesting him send a toy to his new girl friend.It was so far that Dreamwyy can only resort to CaoHaha.
>
> The first step to send something is draw a Magic array on a Magic place.The magic place looks like a coordinate system,and each time you can draw a segments either on cell sides or on cell diagonals.In additional,you need 1 minutes to draw a segments.
>
> If you want to send something ,you need to draw a Magic array which is not smaller than the that.You can make it any deformation,so what really matters is the size of the object.
>
> CaoHaha want to help dreamwyy but his time is valuable(to learn to be just like you),so he want to draw least segments.However,because of his bad math,he needs your help.



## **Input**

> The first line contains one integer T(T<=300).The number of toys.
>
> Then T lines each contains one intetger S.The size of the toy(N<=1e9).



## **Output**

> Out put T integer in each line ,the least time CaoHaha can send the toy.



## **Sample Input**

    5
    1
    2
    3
    4
    5



## **Sample Output**

    4
    4
    6
    6
    7


## **题意**

有一个大小为 `n` 的玩具，我们需要画出面积不小于它的多边形（只能沿着格子边缘或者对角线），每个边缘或者对角线为一步，问最少需要多少步。



## **思路**

**当步数为偶数时**，显然我们需要找一个最接近正方形的矩形（长宽差值最小）才可以使得总面积最大，此时所有边都覆盖在对角线上。

假设当前步数为 `i` ，则该矩形面积为 `2.0 * (i/4) * (i/2 - (i/4))` 。

**而当步数为奇数时**，我们需要在比它小的一个偶数步的基础上，将其最长边拆开，增加一条边使其面积增大 `(d * 2 - 1) * 0.5` 。

根据步数打表以后二分输出答案即可。



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
typedef __int64 LL;
const int mod = 1e9+7;

double ans[maxn];
void init()
{
    double lastL,lastR;
    for(int i=4; i<maxn; i++)
    {
        if(i&1)
        {
            double d = max(lastL,lastR);
            ans[i] = ans[i-1] + (d * 2 - 1) * 0.5;
        }
        else
        {
            lastL = i/4;
            lastR = i/2 - lastL;
            ans[i] = 2.0 * lastL * lastR;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int T;
    cin>>T;
    while(T--)
    {
        LL n;
        cin>>n;
        cout<<lower_bound(ans,ans+maxn,n)-ans<<endl;
    }
    return 0;
}
```

