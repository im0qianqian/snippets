/*
51nod 1136 欧拉函数
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
__int64 eular(__int64 n)
{
    __int64 ret=1,i;
    for(i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            n/=i,ret*=i-1;
            while(n%i==0) n/=i,ret*=i;
        }
    }
    if(n>1) ret*=n-1;
    return ret;
}
int main()
{
    __int64 s;
    cin>>s;
    cout<<eular(s)<<endl;
    return 0;
}