/*
HDU 2067 小兔的棋盘
*/

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
using namespace std;
__int64 a[40]= {1,1};
void init()     //卡特兰数打表
{
    for(int n=2; n<37; n++)
        for(int i=0,j=n-1; i<n; i++,j--)
            a[n]+=a[i]*a[j];
}
int main()
{
    int i=0,n;
    init();
    while(++i&&cin>>n&&n!=-1)
        cout<<i<<" "<<n<<" "<<a[n]*2<<endl;
}
