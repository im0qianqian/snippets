/*
51nod 1069 Nim游戏
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int main()
{
    int t,s=0;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        s^=n;
    }
    if(s)cout<<"A"<<endl;
    else cout<<"B"<<endl;
    return 0;
}
