/*
51nod 1079 中国剩余定理
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include<algorithm>
#include <queue>
using namespace std;

struct po
{
    int num;
    int last;
} a[105];

bool cmp(po a,po b)
{
    return a.num<b.num;
}
int gcd(int a,int b)
{
    if(a<b)swap(a,b);
    if(b==0)return a;
    return gcd(b,a%b);
}
int main()
{
    int N;
    cin>>N;
    int i;
    for(i=0; i<N; i++)
        cin>>a[i].num>>a[i].last;
    sort(a,a+i,cmp);
    int fri=a[0].num+a[0].last;
    for(int j=0; j<i; j++)
    {
        int s=1;
        for(int k=0; k<j; k++)
            s=s/gcd(a[k].num,s)*a[k].num;
        //cout<<s<<endl;
        for(; fri%a[j].num!=a[j].last; fri+=s);
//            cout<<s<<" "<<fri<<endl;
    }
    cout<<fri<<endl;
    return 0;
}