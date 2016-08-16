/*
POJ 1330 Nearest Common Ancestors
*/

#include <iostream>
#include <algorithm>
#include<stdio.h>
#include<string.h>
using namespace std;
int par[11000];
bool f[11000];
void solve(int a,int b)
{
    while(!f[a])
    {
        f[a]=true;
        a=par[a];
    }
    while(!f[b])
    {
        f[b]=true;
        b=par[b];
    }
    printf("%d\n",b);
}
int main()
{
    int T,n,pa,ch,a,b;
    scanf("%d",&T);
    while(T--)
    {
        memset(par,0,sizeof(par));
        memset(f,0,sizeof(f));
        scanf("%d",&n);
        for(int i=0; i<n-1; i++)
        {
            scanf("%d%d",&pa,&ch);
            par[ch]=pa;
        }
        scanf("%d%d",&a,&b);
        solve(a,b);
    }
    return 0;
}
