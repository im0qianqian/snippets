/*
POJ 3070 Fibonacci

题意：求第k个斐波那契数mod10000

思路：矩阵快速幂求解斐波那契数
*/

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
int mod = 10000;
struct node
{
    __int64 mp[2][2];
    void init(__int64 a,__int64 b,__int64 c,__int64 d)  //初始化
    {
        mp[0][0]=a;
        mp[0][1]=b;
        mp[1][0]=c;
        mp[1][1]=d;
    }
    void mult(node x,node y)    //矩阵乘法
    {
        memset(mp,0,sizeof(mp));
        for(int i=0; i<2; i++)
            for(int j=0; j<2; j++)
                for(int k=0; k<2; k++)
                    mp[i][j]=(mp[i][j]+x.mp[i][k]*y.mp[k][j])%mod;
    }
} a;

struct node expo(struct node x,__int64 k)   //快速幂
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
};
int main()
{
    __int64 k;
    while(~scanf("%I64d",&k)&&k!=-1)
    {
        a.init(1,1,1,0);
        printf("%I64d\n",expo(a,k).mp[0][1]%mod);
    }
}
