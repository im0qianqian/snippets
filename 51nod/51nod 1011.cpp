/*
51nod 1011 最大公约数GCD
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
    cout<<solve(a,b)<<endl;
    return 0;
}