/*
POJ 3090 Visible Lattice Points

题意：在一个n*n的点阵中，站在(0,0)最多可以看到多少个点

思路：首先我们可以发现，在整个对角线两侧都是对称的
    假如点阵为1*1的，我们可以看到斜率为0/1,1/1,1/0这三个点
    假如点阵为2*2的，只考虑对角线一侧的话，我们可以看到0/2,1/2,2/2，显然2/2在前面1/1的时候已经计算了。
    然后我们发现，我们所能看到第n层的点的个数刚好是n的欧拉函数(小于n与n互质数的个数)，然后ans*2(对角线两侧对称)+1(斜率为1)
*/

#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
typedef __int64 LL;

int euler[1005];
void geteuler()     //筛法求欧拉函数
{
    memset(euler,0,sizeof(euler));
    euler[1]=1;
    for(int i=2; i<1005; i++)
    {
        if(!euler[i])
        {
            for(int j=i; j<1005; j+=i)
            {
                if(!euler[j])
                    euler[j]=j;
                euler[j]=euler[j]/i*(i-1);
            }
        }
    }
}
int main()
{
    int m,t;
    geteuler();
    cin>>t;
    for(int i=1; i<=t; i++)
    {
        cin>>m;
        LL ans=0;
        for(int j=1; j<=m; j++)
            ans+=euler[j];
        printf("%d %d %I64d\n",i,m,ans*2+1);
    }
    return 0;
}
