/*
51nod 1256 乘法逆元
*/

#include<iostream>
using namespace std;
int exgcd(int m,int n,int &x,int &y)
{
    if(n==0)
    {
        x=1;
        y=0;
        return m;
    }
    int r=exgcd(n,m%n,x,y);
    int t=x;
    x=y;
    y=t-(m/n)*y;
    return r;
}
int main()
{
    int n,m,x,y;
    cin>>m>>n;
    exgcd(m,n,x,y);
    cout<<(x%n+n)%n<<endl;
    return 0;
}