/*
HDU 1714 RedField
*/

#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
    int t;
    double a,b,c,d,x,s;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
        x=sqrt(1.0/(a*a*d*d+c*c*b*b))*a*c*b;
        s=(a*b/2.0)*acos(x/a);
        printf("%.2f\n",s);
    }
    return 0;
}