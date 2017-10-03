/*
51nod 1181 质数中的质数（质数筛法）
*/

#include <iostream>
#include <cstdio>
#include<string.h>
#include <cmath>
using namespace std;
bool isprime[1000005],isplprime[1000005];
__int64 prime[1000005],s=1;
void init()
{
    memset(isprime,1,sizeof(isprime));
    isprime[0]=isprime[1]=0;
    for(__int64 i=2; i<1000005; i++)
        if(isprime[i])
        {
            prime[s++]=i;
            for(__int64 j=2*i; j<1000005; j+=i)
                isprime[j]=0;
        }
    memset(isplprime,1,sizeof(isplprime));
    isplprime[0]=isplprime[1]=0;
    for(__int64 i=2; i<s; i++)
    {
        if(isplprime[i])
        {
            for(__int64 j=2*i; j<s; j+=i)
                isplprime[j]=0;
        }
    }
}
int main()
{
    init();
    __int64 n;
    cin>>n;
    for(__int64 i=1; i<s; i++)
        if(prime[i]>=n&&isplprime[i])
        {
            cout<<prime[i]<<endl;
            break;
        }
    return 0;
}