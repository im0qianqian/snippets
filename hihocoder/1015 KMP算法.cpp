/*
hihocoder 1015 KMP算法
*/

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<stack>
#include<deque>
using namespace std;

char mo[11000],yu[1100000];
void getnext(char* s,int next[])
{
    int j=0,k=-1;
    next[0]=-1;
    int sn=strlen(s);
    while(j<sn)
    {
        if(k==-1||s[j]==s[k])
            next[++j]=++k;
        else k=next[k];
    }
}

int kmp(char *s,char *t,int next[])
{
    int ans=0;
    int i=0,j=0,sn=strlen(s),tn=strlen(t);
    while(i<sn)
    {
        if(j==-1||s[i]==t[j])
        {
            i++,j++;
            if(j==tn)ans++,j=next[j];
        }
        else j=next[j];
    }
    return ans;
}

int main()
{
    int T,next[110000];
    scanf("%d%*c",&T);
    while(T--)
    {
        gets(mo);
        gets(yu);
        getnext(mo,next);
//        for(int i=0; i<=(int)strlen(mo); i++)
//            cout<<next[i]<<" ";
//        cout<<endl;
        printf("%d\n",kmp(yu,mo,next));
    }
    return 0;
}
