/*
HDU 4372 Count the Buildings

题意：N座高楼，高度均不同且为1~N中的数，从前向后看能看到F个，从后向前看能看到B个，问有多少种可能的排列数。

0 < N, F, B <= 2000


首先我们知道一个结论：n的环排列的个数与n-1个元素的排列的个数相等，因为P(n,n)/n=(n-1)!。

可以肯定，无论从最左边还是从最右边看，最高的那个楼一定是可以看到的.

假设最高的楼的位置固定，最高楼的编号为n，那么我们为了满足条件，可以在楼n的左边分x-1组，右边分y-1组，且用每

组最高的那个元素代表这一组，那么楼n的左边，从左到右，组与组之间最高的元素一定是单调递增的，且每组中的最高元

素一定排在该组的最左边，每组中的其它元素可以任意排列（相当于这个组中所有元素的环排列）。右边反之亦然。

然后，可以这样考虑这个问题，最高的那个楼左边一定有x-1个组，右边一定有y-1个组，且每组是一个环排列，这就引出

了第一类Stirling数（n个人分成k组，每组内再按特定顺序围圈的分组方法的数目）。

我们可以先把n-1个元素分成x-1+y-1组，然后每组内部做环排列。再在所有组中选取x-1组放到楼n的左边。所以答案是

ans(n, f, b) = C[f + b - 2][f - 1] * S[n - 1][f + b - 2];
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<math.h>
#define INF (1<<30)
#define LL long long
using namespace std;
const int MMAX = 2100 ;
const LL mod = 1e9+7;

LL c[MMAX][MMAX],s[MMAX][MMAX];

void init() //第一类Stirling数
{
    for(int i=0; i<MMAX; i++)
    {
        c[i][0]=c[i][i]=s[i][i]=1;
        for(int j=1; j<i; j++)
        {
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
            s[i][j]=((i-1)*s[i-1][j])%mod+s[i-1][j-1]%mod;
        }
    }
}
int main()
{
    init();
    LL T;
    scanf("%I64d",&T);
    while(T--)
    {
        LL n,f,b;
        scanf("%I64d%I64d%I64d",&n,&f,&b);
        printf("%I64d\n",(c[f+b-2][f-1]*s[n-1][f+b-2])%mod);
    }
    return 0;
}
