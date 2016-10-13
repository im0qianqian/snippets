/*
hihocoder 1014 Trie树
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
struct po
{
    int num;
    po *next[26];
    void init()
    {
        num=1;
        memset(next,0,sizeof(next));
    }
} *ans;
void init(char *c)  //插入单词
{
    int n=strlen(c);
    po *p=ans;
    for(int i=0; i<n; i++)
    {
        if(p->next[c[i]-'a']!=NULL)
        {
            p=p->next[c[i]-'a'];
            p->num++;
        }
        else
        {
            p->next[c[i]-'a']=(po*)malloc(sizeof(po));
            p->next[c[i]-'a']->init();
            p=p->next[c[i]-'a'];
        }
    }
}
int findall(char *c)    //查询单词个数
{
    int n=strlen(c);
    po *p=ans;
    for(int i=0; i<n; i++)
    {
        if(p->next[c[i]-'a']!=NULL)
            p=p->next[c[i]-'a'];
        else return 0;
    }
    return p->num;
}
int main()
{
    int T;
    char c[110000];
    scanf("%d%*c",&T);
    ans=(po*)malloc(sizeof(po));
    ans->init();
    while(T--)
    {
        gets(c);
        init(c);
    }
    scanf("%d%*c",&T);
    while(T--)
    {
        gets(c);
        printf("%d\n",findall(c));
    }
    return 0;
}
