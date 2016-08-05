/*
51nod 1007 正整数分组
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
int a[105],dp[10005];
int main()
{
    int N,s=0;
    cin>>N;
    for(int i=0; i<N; i++)
    {
        cin>>a[i];
        s+=a[i];                //求和
    }
    int flag=(s%2)?1:0;         //如果是奇数，*2+1
    for(int i=0; i<N; i++)
        for(int j=s/2; j>=a[i]; j--)    //利用01背包求解，背包容量是s/2
            dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
    cout<<2*(s/2-dp[s/2])+flag<<endl;   //输出dp[s/2]距离s/2的距离 然后*2 + s是否为奇数
    return 0;
}
