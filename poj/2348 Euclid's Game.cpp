/*

POJ 2348 Euclid's Game

*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int main()
{
    int m,n;
    while(cin>>m>>n&&(m||n))
    {
        bool flag=true;
        while(true)
        {
            if(m<n)swap(m,n);
            if(m%n==0||m-n>n)break;
            m-=n;
            flag=!flag;
        }
        if(flag)cout<<"Stan wins"<<endl;
        else cout<<"Ollie wins"<<endl;
    }
    return 0;
}
