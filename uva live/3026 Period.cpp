/*
UVA Live 3026 Period

解题思路：本题利用KMP算法中失配函数的性质解决。

我们仔细观察失配函数f就会发现，如果一个字符串P是一个周期串，且它的最后一个位置是i，那么i-f[i]一定是该周期串的一个最小的循环节的长度，这样，最大的k值就是i/(i-f[i])。这样，我们只需要寻找f[i]>0（因为k>0，因此不能让i-f[i]==i）且i%(i-f[i])==0的位置即可。
*/
#include <iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
using namespace std;
char c[1100000];
int f[1100000]= {-1};
void solve(char *c,int n)
{
    int i=0,k=-1;
    while(i<n)  //KMP
    {
        if(k==-1||c[i]==c[k])
            f[++i]=++k;
        else k=f[k];
    }
    for(int i=2; i<=n; i++)
        if(f[i]>0&&(i%(i-f[i])==0))
            printf("%d %d\n",i,i/(i-f[i]));
    printf("\n");
}
int main()
{
    int n,i=0;
    while(~scanf("%d%*c",&n)&&n)
    {
        memset(f+1,0,sizeof(f));
        gets(c);
        printf("Test case #%d\n",++i);
        solve(c,n);
    }
    return 0;
}
