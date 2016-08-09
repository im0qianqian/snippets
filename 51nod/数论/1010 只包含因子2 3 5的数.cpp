/*
51nod 1010 只包含因子2 3 5的数
*/

#include <iostream>
#include<algorithm>
using namespace std;
#define maxx 1e18+1005
__int64 a[110000];

void init(__int64 &num)
{
    num=1;
    for(__int64 i=1; i<maxx; i*=2)
        for(__int64 j=1; i*j<maxx; j*=3)
            for(__int64 k=1; i*j*k<maxx; k*=5)
                a[num++]=i*j*k;
    sort(a+1,a+num);
}
__int64 findd(__int64 k,__int64 n)
{
    if(k<=2)return 2;
    __int64 left=1,right=n-1,mid;
    while(left<right)
    {
        mid=(left+right)/2;
        if(a[mid]>=k)right=mid;
        else left=mid+1;
    }
    return a[right];
}
int main()
{
    __int64 n,m;
    init(m);
    cin>>n;
    while(n--)
    {
        __int64 k;
        cin>>k;
        cout<<findd(k,m)<<endl;
    }
    return 0;
}