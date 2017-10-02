/*
51nod 1432 独木舟
*/

#include<iostream>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
__int64 a[10005];
int main()
{
    __int64 n,v,s=0;
    cin>>n>>v;
    for(int i=0; i<n; i++)
        cin>>a[i];
    __int64 v1=v;
    sort(a,a+n);
    while(true)
    {
        int flag=0;
        __int64 sum=0;
        for(int i=n-1; i>=0; i--)
        {
            if(v1>=a[i]&&a[i]!=0)
            {
                v1-=a[i];
                flag++;
                a[i]=0;
            }
            if(v1==0||flag>=2)break;
        }
        for(int i=0; i<n; i++)
            sum+=a[i];
        s++;
        v1=v;
        if(sum<=0)break;
    }
    cout<<s<<endl;
    return 0;
}
