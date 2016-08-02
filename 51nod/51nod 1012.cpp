/*
51nod 1012 最小公倍数LCM
*/

#include<cmath>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
using namespace std;
__int64 solve(__int64 a,__int64 b)
{
    if(a==0)return b;
    return solve(b%a,a);
}
int main()
{
    __int64 a,b;
    cin>>a>>b;
    if(a>b)swap(a,b);
    __int64 s=solve(a,b);
    __int64 k=a/s*b;
    cout<<k<<endl;
    return 0;
}
