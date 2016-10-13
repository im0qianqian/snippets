/*
HDU 2846 Repository

题意：查询字串在给出的多少个单词中出现过

思路：建立一个单词以及其后缀的字典树，树中每个节点存储当前位置所被覆盖个数，但是还要避免比如abab这样的有一个后缀为ab的字串被重复添加，所以每次增加覆盖次数的时候判断是否在同一个串中已经增加过这一次数
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int now;
struct po
{
    int num;
    int now;
    po *next[26];
    void init()
    {
        now=num=0;
        memset(next,0,sizeof(next));
    }
} *ans;
void init(char *c)  //插入单词
{
    int n=strlen(c);
    po *p=ans;
    for(int i=0; i<n; i++)
    {
        if(p->next[c[i]-'a']==NULL)
        {
            p->next[c[i]-'a']=(po*)malloc(sizeof(po));
            p->next[c[i]-'a']->init();
        }
        p=p->next[c[i]-'a'];
        if(p->now!=now)     //避免同一个字符串因为后缀重复计数
            p->now=now,p->num++;
    }
    if(now!=p->now)
        p->num++;
}

int findall(char *c)    //查询单词个数
{
    int n=strlen(c);
    po *p=ans;
    for(int i=0; i<n; i++)
    {
        if(p->next[c[i]-'a']!=NULL)
            p=p->next[c[i]-'a'];
        else return 0;  //没有此单词
    }
    return p->num;
}

int main()
{
    int n;
    char wo[30];
    scanf("%d%*c",&n);
    ans=(po*)malloc(sizeof(po));
    ans->init();
    while(n--)
    {
        gets(wo);
        now++;
        int len=strlen(wo);
        for(int i=0; i<len; i++)
            init(wo+i);
    }
    scanf("%d%*c",&n);
    while(n--)
    {
        gets(wo);
        printf("%d\n",findall(wo));
    }
    return 0;
}
