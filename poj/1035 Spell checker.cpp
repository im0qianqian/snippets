/*
POJ 1035 Spell checker
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
map<string,bool>k;
char data[10100][20];
bool judge(char *a,char *b,int n,int m)
{
    int i=0;
    for(; i<n; i++)
        if(a[i]!=b[i])break;
    if(i>=n)return true;
    else
    {
        int j=i+1;
        for(; j<m; j++)
            if(a[j-1]!=b[j])break;
        if(j>=m)return true;
    }
    return false;
}
bool jl(char *a,char* s)
{
    int m=strlen(a);
    int n=strlen(s);
    if(m==n)
    {
        if(strcmp(a,s)==0)
            return true;
        else
        {
            int t=0;
            for(int i=0; i<m; i++)
                if(a[i]!=s[i])t++;
            return (t==1);
        }
    }
    else if(abs(m-n)==1)
    {
        if(m<n)return judge(a,s,m,n);
        else return judge(s,a,n,m);
    }
    return false;
}
void solve(char* a,int n)
{
    printf("%s:",a);
    for(int i=0; i<n; i++)
        if(jl(data[i],a))
            printf(" %s",data[i]);
    puts("");
}
int main()
{
    char a[20];
    int i=0;
    for(; gets(data[i]); i++)
    {
        if(data[i][0]=='#')break;
        k[(string)data[i]]=true;
    }
    while(gets(a))
    {
        if(a[0]=='#')break;
        if(k[(string)a])printf("%s is correct\n",a);
        else solve(a,i);
    }
    return 0;
}
