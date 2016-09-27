/*
HDU 2048 神、上帝和老天爷
*/

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<iostream>
using namespace std;
__int64 a[25],an[25];
void init()
{
    for(int i=2; i<21; i++)         //计算全错排
        a[i]=i*a[i-1]+((i%2==0)?1:-1);
    __int64 s=1;
    for(int i=1; i<21; i++)         //计算全排列
    {
        s*=i;
        an[i]=s;
    }
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        printf("%.2lf%%\n",(double)a[n]/an[n]*100.0);
    }
}
