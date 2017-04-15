# hihoCoder 搜索一·24点

## **描述**

> 周末，小Hi和小Ho都在家待着。
>
> 在收拾完房间时，小Ho偶然发现了一副扑克，于是两人考虑用这副扑克来打发时间。
>
> 小Ho：玩点什么好呢？
>
> 小Hi：两个人啊，不如来玩24点怎么样，不靠运气就靠实力的游戏。
>
> 小Ho：好啊，好啊。
>
> <经过若干局游戏之后>
>
> 小Ho：小Hi，你说如果要写个程序来玩24点会不会很复杂啊？
>
> 小Hi：让我想想。
>
> <过了几分钟>
>
> 小Hi：我知道了！其实很简单嘛。



## **输入**

> 第1行：1个正整数, t，表示数据组数，2≤t≤100。
>
> 第2..t+1行：4个正整数, a,b,c,d，1≤a,b,c,d≤10。



## **输出**

> 第1..t行：每行一个字符串，第i行表示第i组能否计算出24点。若能够输出”Yes”，否则输出”No”。



## **样例输入**

    2
    5 5 5 1
    9 9 9 9



## **样例输出**

    Yes
    No



## **思路**

刚开始使用搜索枚举出所有类型，然后怎么算也没办法算出 `5 5 5 1` 是怎么样得出 `24` 点的，如果那个时候知道了要考虑**浮点数**，就不会有下面这种方法解题啦！o(╯□╰)o😔

提示中说：枚举所有数字与运算符，然后**通过**

    (((a ⊙ b) ⊙ c ) ⊙ d)
    ((a ⊙ b) ⊙ (c ⊙ d))
这**两种类型的式子**计算，首先我们可以想一想，如果枚举所有数字的话，普通枚举一定会出现重复的情况，比如 `5 5 5 1` ，这组数中有 `3` 个 `5` 存在，即使全部枚举也不会超时，但是，更重要的是算法优化嘛！



**C++中刚好提供了这么一个函数**

```cpp
next_permutation(a,a+4);   //操作对象是数组a前四位
```

它是用来生成一个数组（或容器）的下一个排列。

此处是递增排列，也就是 `1 2 3 4` 的下一排列是 `1 2 4 3`



**另外还有一个与之类似的函数是**

```cpp
prev_permutation(a,a+4);   //操作对象是数组a前4位
```

使用这两个函数不就不会出现那种重复枚举的情况啦！不过首先要对数组进行排序😌

现在数字枚举的问题解决啦！然后就是运算符枚举了！这样的话既然有三个位置需要填充运算符，我们可以用一个**三重循环**来枚举所有的情况，然后针对每一种情况计算所得出的结果！

如果答案是 `24` ，直接停止枚举。输出 `Yes` ，否则输出 `No` 。



## **AC 代码**

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
double a[4];
bool flag;
double so(double a,double b,int k)
{
    double s=0.0;
    switch(k)
    {
        case 0:s=a+b;break;
        case 1:s=a-b;break;
        case 2:s=a*b;break;
        case 3:if(b!=0)s=a/b;break;
        case 4:s=b-a;break;
        case 5:if(a!=0)s=b/a;break;
    }
    return s;
}
bool pan(int i,int j,int k)
{
    if(so(so(so(a[0],a[1],i),a[2],j),a[3],k)==24)return true;
    if(so(so(a[0],a[1],i),so(a[2],a[3],k),j)==24)return true;
    return false;
}
void solve()
{
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            for(int k=0; k<6; k++)
                if(pan(i,j,k))
                {
                    flag=true;
                    return;
                }
}
int main()
{
    int N;
    cin>>N;
    while(N--)
    {
        flag=false;
        for(int i=0; i<4; i++)
            cin>>a[i];
        sort(a,a+4);
        do
        {
            solve();
            if(flag)break;
        }
        while(next_permutation(a,a+4));
        if(flag)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```

