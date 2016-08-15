/*
HDU 5832 A water problem
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

char s[11000000];
int ans,b=73*137;
int main()
{
    for(int i=1; gets(s); i++)
    {
        ans=0;
        int l=strlen(s);
        for(int j=0; j<l; j++)
            ans=(ans*10+(s[j]-'0'))%b;
        if(!ans)printf("Case #%d: YES\n",i);
        else printf("Case #%d: NO\n",i);
    }
    return 0;
}
