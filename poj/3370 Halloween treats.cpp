/*
POJ 2356 Find a multiple+

题意：

给定n个正数，请你从中找出若干个数，其和刚好是n的倍数。


思路：

抽屉原理。

sum[0]=0;

sum[i]=(a[1]+a[2]+a[3]...a[i])%n;

如果存在i>0 使得sum[i]=0;则直接输出a[1],a[2],,....a[i]即可满足题意。

如果不存在，考虑sum[ j ]-sum[ i ]=a [ i+1 ],a[ i+2 ]....a[ j ]。

即如果存在sum[ j ]-sum[ i ]==0,则输出 a [ i+1 ],a[ i+2 ]....a[ j ] 即可。

接下来用抽屉原理证明 i , j 必然存在。


抽屉原理：

如果将大于n个数量的物品放入n个抽屉，则必然存在某个抽屉放了大于1个物品。


因为sum [ i ] 的值只能是1,....n-1.sum [ i ]的数量有n个。

所以由抽屉原理可知，必然存在某两个sum [ i ] 值一样。
*/

#include <iostream>
#include<cstdio>
#include<string.h>
using namespace std;

int a[15010],sum[15010],ha[11000];
int main()
{
    int n;
    scanf("%d",&n);
    memset(ha,-1,sizeof(ha));
    ha[0]=0;
    for(int i=1; i<=n; i++)
    {
        scanf("%d",a+i);
        sum[i]=(sum[i-1]+a[i])%n;
    }
    for(int i=1; i<=n; i++)
    {
        int *temp=&ha[sum[i]];
        if(*temp==-1)
            *temp=i;
        else
        {
            printf("%d\n",i-*temp);
            for(int j=*temp+1; j<=i; j++)
                printf("%d\n",a[j]);
            break;
        }
    }
    return 0;
}
