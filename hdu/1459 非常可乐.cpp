/*
HDU 1459:非常可乐
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int gcd(int m,int n)
{
    if(n==0)return m;
    return gcd(n,m%n);
}
int main()
{
    int a,b,c;
    while(cin>>a>>b>>c&&(a||b||c))
    {
        if(b<c)swap(b,c);
        int ans=gcd(b,c);
        if(a%ans==0&&a/ans%2!=0)cout<<"NO"<<endl;
        else cout<<a/ans-1<<endl;
    }
    return 0;
}
