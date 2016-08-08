/*

POJ 2484 A Funny Game

*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int main()
{
    long long int n;
    while(cin>>n&&n)
    {
        if(n<=2)cout<<"Alice"<<endl;
        else cout<<"Bob"<<endl;
    }
    return 0;
}