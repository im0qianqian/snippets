/*
51nod 1050 循环数组最大子段和
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include<string.h>
#include<stack>
using namespace std;
__int64 a[50005],all,sum,maxx,minx;
int main()
{
    __int64 n;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
        all+=a[i];
    }
    for(int i=1; i<=n; i++)
    {
        sum+=a[i];
        if(sum<0)sum=0;
        maxx=max(maxx,sum);
    }
    sum=0;
    for(int i=1; i<=n; i++)
    {
        sum-=a[i];
        if(sum<0)sum=0;
        minx=max(minx,sum);
    }
    cout<<max(maxx,all+minx)<<endl;
    return 0;
}
