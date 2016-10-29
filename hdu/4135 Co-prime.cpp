/*
HDU 4135 Co-prime

思路：通常我们求１-ｎ中与ｎ互质的数的个数都是用欧拉函数！ 但如果ｎ比较大或者是求１～ｍ中与ｎ互质的数的个数等等问题，要想时间效率高的话还是用容斥原理！

容斥：先对n分解质因数，分别记录每个质因数， 那么所求区间内与某个质因数不互质的个数就是n / r(i)，假设r(i)是r的某个质因子 假设只有三个质因子， 总的不互质的个数应该为p1+p2+p3-p1*p2-p1*p3-p2*p3+p1*p2*p3, 及容斥原理，可以转向百度百科查看相关内容 pi代表n/r(i),即与某个质因子不互质的数的个数 ，当有更多个质因子的时候， 可以用状态压缩解决，二进制位上是1表示这个质因子被取进去了。 如果有奇数个1，就相加，反之则相减。
*/

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
typedef __int64 LL;
using namespace std;
vector<LL>prime;
void jprime(LL n)   //分解质因子
{
    for(LL i=2; i*i<=n; i++)
        if(n%i==0)
        {
            prime.push_back(i); //质因子
            while(n%i==0)
                n/=i;
        }
    if(n>1)prime.push_back(n);
}

LL solve(LL a,LL b,LL n)    //[a,b]中与n互质的数的个数
{
    LL sum=0;
    LL size=prime.size();
    for(LL msk=1; msk<(1<<size); msk++) //共有2^size种组合情况
    {
        LL mult=1,bits=0;
        for(LL i=0; i<size; i++)    //枚举每一种情况
        {
            if(msk&(1<<i))  //如果在当前判断之内
            {
                ++bits;
                mult*=prime[i];
            }
        }
        LL cur=b/mult-(a-1)/mult;   //中间结果
        if(bits&1)sum+=cur;
        else sum-=cur;
    }
    return b-a-sum+1;
}
int main()
{
    LL T;
    scanf("%I64d",&T);
    for(LL t=1; t<=T; t++)
    {
        LL a,b,n;
        scanf("%I64d%I64d%I64d",&a,&b,&n);
        prime.clear();
        jprime(n);
        printf("Case #%I64d: %I64d\n",t,solve(a,b,n));
    }
    return 0;
}
