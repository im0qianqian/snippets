/*

POJ 2192 Zipper

*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
char a[205],b[205],c[405];
int k[405][405];
int main()
{
    int n;
    cin>>n;
    for(int s=1; s<=n; s++)
    {
        cin>>a>>b>>c;
        int n=strlen(a),m=strlen(b);
        memset(k,0,sizeof(k));
        k[0][0]=1;
        for(int i=0; i<=n; i++)
            for(int j=0; j<=m; j++)
            {
                if(i>0&&c[i+j-1]==a[i-1])k[i][j]=(k[i][j]||k[i-1][j]);
                if(j>0&&c[i+j-1]==b[j-1])k[i][j]=(k[i][j]||k[i][j-1]);
            }
        printf("Data set %d: ",s);
        if(k[n][m])cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    }
    return 0;
}
