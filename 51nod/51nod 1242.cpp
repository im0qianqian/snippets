/*
51nod 1242 斐波那契数列的第N项
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;
const __int64 mod=1000000009;
struct node
{
    __int64 mp[2][2];
    void init(__int64 a,__int64 b,__int64 c,__int64 d)
    {
        mp[0][0]=a;
        mp[0][1]=b;
        mp[1][0]=c;
        mp[1][1]=d;
    }
    void mult(node x,node y)
    {
        memset(mp,0,sizeof(mp));
        for(__int64 i=0; i<2; i++)
            for(__int64 j=0; j<2; j++)
                for(__int64 k=0; k<2; k++)
                    mp[i][j]=(mp[i][j]+x.mp[i][k]*y.mp[k][j])%mod;
    };
} init;

struct node expo(struct node x, __int64 k)
{
    struct node tmp;
    tmp.init(1,0,0,1);
    while(k)
    {
        if(k&1)tmp.mult(tmp,x);
        x.mult(x,x);
        k>>=1;
    }
    return tmp;
}
int main()
{
    __int64 k;
    scanf("%I64d",&k);
    init.init(1,1,1,0);
    printf("%I64d\n",expo(init,k).mp[0][1]%mod);
    return 0;
}