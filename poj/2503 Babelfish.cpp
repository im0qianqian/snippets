/*
POJ 2503 Babelfish
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
map<string,string>k;
string a,b;
int main()
{
    char c[10005];
    while(gets(c))
    {
        if(strcmp(c,"")==0)goto end1;
        else
        {
            char c1[20],c2[20];
            sscanf(c,"%s %s",c1,c2);
            k[(string)c2]=(string)c1;
        }
    }
end1:
    while(gets(c))
    {
        string d=k[(string)c];
        if(d!="")cout<<d<<endl;
        else cout<<"eh"<<endl;
    }
    return 0;
}
