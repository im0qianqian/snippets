/*
51nod 1066 Bash游戏
*/

#include <stdio.h>
#include<iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int a,b;
        cin>>a>>b;
        if(a%(b+1))cout<<"A"<<endl;
        else cout<<"B"<<endl;
    }
    return 0;
}
