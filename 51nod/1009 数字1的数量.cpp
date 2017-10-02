/*
51nod 1009 数字1的数量
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
__int64 sum;
void solve(__int64 a)
{
    __int64 now=1,d=a;
    while(a)
    {
        if(a%10==0)sum+=a/10*now;      //当前位为0 出现1的个数==高位*当前位数
        else if(a%10==1)sum+=a/10*now+d%now+1;      //当前位为1 出现1的个数==高位*当前位数+低位+1
        else sum+=(a/10+1)*now;      //当前位大于1 出现1的个数==（高位+1）*当前位数
        a/=10;
        now*=10;
    }
}
int main()
{
    __int64 s;
    cin>>s;
    solve(s);
    cout<<sum<<endl;
    return 0;
}
