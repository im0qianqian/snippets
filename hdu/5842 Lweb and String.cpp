/*
HDU 5842 Lweb and String
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
char c[100005];
int a[30];
int main()
{
    int n;
    scanf("%d%*c",&n);
    for(int i=1; i<=n; i++)
    {
        gets(c);
        int s=0;
        memset(a,0,sizeof(a));
        for(int j=0; j<(int)strlen(c); j++)
        {
            if(!a[c[j]-'a'])
            {
                a[c[j]-'a']=true;
                s++;
            }
        }
        printf("Case #%d: %d\n",i,s);
    }
    return 0;
}
