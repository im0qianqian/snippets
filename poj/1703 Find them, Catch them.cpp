/*
POJ 1703 Find them, Catch them
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define maxx (1<<30)
int n,m;
int set[200010];
int setfind(int d)
{
    if(set[d]<0)return d;
    return set[d]=setfind(set[d]);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%*c",&n,&m);
        memset(set,-1,sizeof(set));
        for(int i=0; i<m; i++)
        {
            int a,b;
            char c[5];
            scanf("%s%d%d",c,&a,&b);
            if(c[0]=='A')
            {
                if(setfind(a)!=setfind(b)&&setfind(a)!=setfind(b+n))
                    printf("Not sure yet.\n");
                else if(setfind(a)==setfind(b))
                    printf("In the same gang.\n");
                else printf("In different gangs.\n");
            }
            else if(setfind(a)!=setfind(b+n))
            {
                set[setfind(a)]=setfind(b+n);
                set[setfind(b)]=setfind(a+n);
            }
        }
    }
}
