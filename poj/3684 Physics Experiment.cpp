/*
POJ 3684 Physics Experiment
*/

#include<cstdio>
#include<math.h>
#include<iostream>
#include<algorithm>
#define max(a,b) (a>b?a:b)
using namespace std;
double solve(int h,int r,int T)
{
    if(T<0)return h;
    double t=sqrt(h/5.0);
    int k=T/t;
    if(k&1)return h-5.0*(k*t+t-T)*(k*t+t-T);
    else return h-5.0*(T-k*t)*(T-k*t);
}
int main()
{
    int N;
    scanf("%d",&N);
    while(N--)
    {
        int n,h,r,t;
        scanf("%d%d%d%d",&n,&h,&r,&t);
        double k[n];
        for(int i=0; i<n; i++)
            k[i]=solve(h,r,t-i);
        sort(k,k+n);
        for(int i=0; i<n; i++)
            printf(i!=n-1?"%.2f ":"%.2f\n",k[i]+2*r*i/100.0);
    }
    return 0;
}
