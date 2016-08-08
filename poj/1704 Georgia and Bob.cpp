/*
POJ 1704 Georgia and Bob
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int a[n+10],s=0;
        for(int i=0; i<n; i++)
            cin>>a[i];
        if(n&1)a[n++]=0;
        sort(a,a+n);
        for(int i=1; i<n; i+=2)
            s^=a[i]-a[i-1]-1;
        if(s)cout<<"Georgia will win"<<endl;
        else cout<<"Bob will win"<<endl;
    }
    return 0;
}
