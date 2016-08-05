/*
51nod 1240 莫比乌斯函数
*/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
    __int64 a;
    cin>>a;
    bool flag=0;
    __int64 prime=0;
    for(__int64 i=2; i*i<=a; i++)
        if(a%i==0)
        {
            prime++;
            int num=0;
            while(a%i==0)
            {
                a/=i;
                num++;
            }
            if(num>1)
            {
                flag=1;
                break;
            }
        }
    if(flag)cout<<"0"<<endl;
    else
    {
        if(a>1)prime++;
        printf(prime%2==0?"1\n":"-1\n");
    }
    return 0;
}
