/*
ural 1057 Amount of degrees

题意：求[x,y]区间转化为 c 进制 1 的个数为 k 的数的出现次数。

分析：满足区间减法
*/

#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<vector>
#include<iostream>
using namespace std;
int f[33][33];      //一个i位的数中出现j个1的个数
void init()
{
    f[0][0] = 1;
    for(int i=1; i<32; i++)
    {
        f[i][0] = f[i-1][0];
        for(int j=1; j<=i; j++)
            f[i][j] = f[i-1][j] + f[i-1][j-1];
    }
}
int solve(int n,int b,int k)
{
    int st[60],len=0;
    while(n)            //转换为k进制
    {
        st[len++]=n%k;
        n/=k;
    }
    int sum=0,to=0;
    for(int i=len-1; i>=0; i--) //枚举每一位，从高位到低位
    {
        if(st[i]==1)            //如果当前位是1，直接求解
        {
            sum+=f[i][b-to];
            if(++to==b)break;
        }
        else if(st[i]>1)        //如果当前位>1，其后可以随意选取0||1
        {
            sum+=f[i+1][b-to];
            break;
        }
    }
    return (to==b)?sum+1:sum;
}
int main()
{
    init();
    int x,y,a,b;
    while(~scanf("%d%d%d%d",&x,&y,&a,&b))
        printf("%d\n",solve(y,a,b)-solve(x-1,a,b)); //区间减法
    return 0;
}
