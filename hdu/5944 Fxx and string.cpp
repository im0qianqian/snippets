/*
HDU 5944 Fxx and string
*/
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
typedef __int64 LL;
using namespace std;
char c[11000];
void solve(char *c)
{
    __int64 sum=0,len=strlen(c);
    for(int i=1; i<len; i++)
        for(int j=i+i; j<len; j+=i)
        {
            __int64 k=j/i*j;
            if(k<len)
                if((c[i]=='y'&&c[j]=='r'&&c[k]=='x')||(c[i]=='x'&&c[j]=='r'&&c[k]=='y'))
                    sum++;
        }
    printf("%I64d\n",sum);
}
int main()
{
    int T;
    scanf("%d%*c",&T);
    while(T--)
    {
        gets(c+1);
        c[0]='#';
        solve(c);
    }
    return 0;
}