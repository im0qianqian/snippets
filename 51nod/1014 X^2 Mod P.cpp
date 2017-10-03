/*
51nod 1014 X^2 Mod P
*/

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    __int64 a,b;
    bool flag=true;
    cin>>a>>b;
    for(__int64 i=0; i<=a; i++)
        if(((i%a)*(i%a))%a==b)
        {
            if(flag)
            {
                cout<<i;
                flag=false;
            }
            else cout<<" "<<i;
        }
    if(flag)cout<<"No Solution";
    cout<<endl;
    return 0;
}