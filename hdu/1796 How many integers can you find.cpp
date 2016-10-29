/*
HDU 1796 How many integers can you find

题意：给定n和一个大小为m的集合，集合元素为非负整数。求1...n内能被集合里任意一个数整除的数字个数。
 
思路：容斥原理的简单应用。
先找出1...n内能被集合中任意一个元素整除的个数，再减去能被集合中任意两个整除的个数，即能被它们两只的最小公倍数整除的个数，因为这部分被计算了两次，然后又加上三个的时候的个数，然后又减去四个时候的倍数...判断集合元素的个数为奇还是偶，奇加偶减。

注意：集合中的数可能有0存在，此时要排除0。
*/

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
typedef __int64 LL;
using namespace std;
LL a[105];

LL gcd(LL a,LL b)
{
    return b==0?a:gcd(b,a%b);
}
LL solve(LL n,LL m)
{
    LL ans=0;
    for(LL msk=1; msk<(1<<m); msk++)    //共2^m种组合情况
    {
        LL mult=1,cnt=0;
        for(LL i=0; i<m; i++)
        {
            if(msk&(1<<i))
            {
                mult=mult/gcd(mult,a[i])*a[i];  //计算当前组合的最小公倍数
                ++cnt;
            }
        }
        LL ks=(n-1)/mult;
        if(cnt&1)ans+=ks;
        else ans-=ks;
    }
    return ans;
}

int main()
{
    LL n,m;
    while(~scanf("%I64d%I64d",&n,&m))
    {
        for(int i=0; i<m; i++)
        {
            scanf("%I64d",a+i);
            if(a[i]==0)i--,m--;
        }
        printf("%I64d\n",solve(n,m));
    }
    return 0;
}
