/*
POJ 2003 Hire and Fire
*/

#include <stdio.h>
#include<string.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<list>
#include<map>
#define INF (1<<30)
using namespace std;

struct tman
{
    string name;
    tman* fa;
    list<tman*>s;
    tman()
    {
        fa=NULL;
    }
};
map<string,tman*>hash;
tman*root;
void print(int depth,tman *now)
{
    if(now)
    {
        for(int i=0; i<depth; i++)
            cout<<"+";
        cout<<now->name<<endl;
        for(list<tman*>::iterator it=now->s.begin(); it!=now->s.end(); it++)
            print(depth+1,*it);
    }
}
void hires(string s)
{
    tman*f=hash[s];
    tman*f2=new tman();
    cin>>f2->name;
    cin>>f2->name;
    f2->fa=f;
    hash[f2->name]=f2;
    f->s.push_back(f2);
}
void fire()
{
    string n;
    cin>>n;
    tman *s=hash[n];
    hash.erase(n);
    while(s->s.size())
    {
        s->name=s->s.front()->name;
        hash[s->name]=s;
        s=s->s.front();
    }
    s->fa->s.remove(s);
    delete s;
}
int main()
{
    string s;
    root=new tman();
    cin>>root->name;
    hash[root->name]=root;
    while(cin>>s)
    {
        if(s=="print")
        {
            print(0,root);
            for(int i=0; i<60; i++)cout<<'-';
            cout<<endl;
        }
        else if(s=="fire")fire();
        else hires(s);
    }
    return 0;
}
