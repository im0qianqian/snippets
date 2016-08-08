/*
HDU 5753 Permutation Bo
*/

#include <iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;

int main()
{
    int n;
    while(cin>>n)
    {
        double s=0,a;
        for(int i=0; i<n; i++)
        {
            cin>>a;
            if(i==0||i==n-1)s+=a/2.0;
            else s+=a/3.0;
        }
        if(n==1)printf("%lf\n",a);
        else printf("%lf\n",s);
    }
    return 0;
}
