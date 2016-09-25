/*
HDU 5902 GCD is Funny

题意：Alex发明了一个有趣的游戏. 一开始他在黑板上写了nn个正整数, 然后他开始重复进行如下的操作:

    1. 他选择黑板上三个数字aa, bb和cc, 把他们从黑板上擦掉.
    2. 他从这三个数aa, bb和cc中选择了两个数, 并计算出他们的最大公约数, 记这个数为dd (dd 可以是\gcd(a,b)gcd(a,b), \gcd(a,c)gcd(a,c)或者\gcd(b, c)gcd(b,c)).
    3. 他在黑板上写下两次数字dd.

    显然, 在操作n−2次后, 黑板上只会留下两个相同的数字. Alex想要知道哪些数字可以最终留在黑板上.

思想：考虑到, 最后留下来的数一定是某个子集的gcd. 我们只要在一开始丢掉了一个数, 考虑留下来两个数是x,x, 那么又选了另一个数y的话, 我们只要丢掉其中一个x就能获得了两个gcd(x,y), 也就是说接下来每次操作我们都有了一个额外的数用来丢弃, 且不会改变子集gcd的种类数.
    所以我们可以先求出给出数字的两两GCD，然后用已有的GCD数列再一次与原数求一次GCD，依次输出.
*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
int num[1100],a[1100];
int gcd(int a,int b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
int main()
{
    int T,n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        memset(num,0,sizeof(num));
        for(int i=0; i<n; i++)
            cin>>a[i];
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                num[gcd(a[i],a[j])]=1;      //记录初始两两的GCD
        int flag=1,cnt=n;
        while(flag&&--cnt>2)
        {
            flag=0;
            for(int i=1; i<=1000; i++)      //对已有的GCD再次与数字进行GCD运算
                if(num[i])
                    for(int j=0; j<n; j++)
                    {
                        int t=gcd(i,a[j]);
                        if(!num[t])num[t]=1,flag=1;
                    }
        }
        int t=0;
        for(int i=1; i<=1000; i++)          //输出
            if(num[i])
            {
                if(t)printf(" %d",i);
                else
                {
                    printf("%d",i);
                    t=1;
                }
            }
        printf("\n");
    }
}
