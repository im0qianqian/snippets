/*
51nod 1080 两个数的平方和
*/

#include<cmath>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
using namespace std;
void solve(__int64 s)
{
    bool flag=true;
    for(__int64 i=0; i*i*2<=s; i++)
    {
        __int64 t=sqrt(s-i*i);
        if(t*t+i*i==s)
        {
            flag=false;
            printf("%I64d %I64d\n",i,t);
        }
    }
    if(flag)printf("No Solution\n");
}
int main()
{
    __int64 s;
    scanf("%I64d",&s);
    solve(s);
}