/*
51nod 1106 ÖÊÊı¼ì²â
*/

#include<cmath>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
using namespace std;
bool judge(__int64 a)
{
    if(a<2)return false;
    for(int i=2; i*i<=a; i++)
        if(a%i==0)return false;
    return true;
}
int main()
{
    __int64 n;
    scanf("%I64d",&n);
    while(n--)
    {
        __int64 a;
        scanf("%I64d",&a);
        printf(judge(a)?"Yes\n":"No\n");
    }
}