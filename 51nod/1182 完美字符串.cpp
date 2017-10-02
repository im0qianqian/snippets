/*
51nod 1182 完美字符串
*/

#include<cmath>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
using namespace std;
int a[26];
int main()
{
    char c[10005];
    gets(c);
    for(int i=0; i<(int)strlen(c); i++)
    {
        if(c[i]>='a')c[i]-=32;
        a[c[i]-'A']++;
    }
    sort(a,a+26);
    __int64 s=0;
    for(int i=25; i>=0; i--)
        s+=(i+1)*a[i];
    cout<<s<<endl;
    return 0;
}

