/*
HDU 5690 All X

    一个由x组成的m位数也可以表示成(10^m-1)*x/9对吧！
    既然这样，只需要证明((10^m-1)*x)/9%k==c成立就可以了！
    可以把这个式子变换一下，就是((10^m)%(9*k)*x)%(9*k)-x==9*c;

*/

#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
typedef __int64 LL;

LL mult(LL n,LL k,LL mod)
{
    LL s=1;
    while(k)
    {
        if(k&1)s=(s*n)%mod;
        n=(n*n)%mod;
        k>>=1;
    }
    return s;
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int si=1; si<=t; si++)
    {
        LL x,m,k,c;
        scanf("%I64d%I64d%I64d%I64d",&x,&m,&k,&c);
        LL mod = 9*k;
        LL l = (mult(10,m,mod)*x)%mod-x;
        LL r = 9*c;
        printf("Case #%d:\n",si);
        printf(l==r?"Yes\n":"No\n");
    }
    return 0;
}
