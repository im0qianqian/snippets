/*
HDU 5752 Sqrt Bo
*/

#include <iostream>
#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<string.h>
using namespace std;

int main()
{
    char c[1120];
    while(gets(c))
    {
        if(strlen(c)>11||strcmp(c,"0")==0)cout<<"TAT"<<endl;
        else
        {
            __int64 a;
            sscanf(c,"%I64d",&a);
            int i=0;
            while(sqrt(a)!=1)
            {
                a=sqrt(a);
                i++;
                if(i>5)break;
            }
            if(i<=5)cout<<i<<endl;
            else cout<<"TAT"<<endl;
        }
    }
    return 0;
}