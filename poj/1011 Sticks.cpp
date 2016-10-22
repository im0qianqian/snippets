/*
POJ 1011 Sticks
*/

#include <stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;
int a[105],n,len;
bool use[105],flag;

void dfs(int dep, int now_len, int u)    // dep为当前已被用过的小棒数，u为当前要处理的小棒。
{
    if(flag) return;
    if(now_len == 0)                     //  当前长度为0，寻找下一个当前最长小棒。
    {
        int k = 0;
        while(use[k]) k ++;              //  寻找第一个当前最长小棒。
        use[k] = true;
        dfs(dep + 1, a[k], k + 1);
        use[k] = false;
        return;
    }
    if(now_len == len)                   //  当前长度为len，即又拼凑成了一根原棒。
    {
        if(dep == n) flag = true;        //  完成的标志：所有的n根小棒都有拼到了。
        else dfs(dep, 0, 0);
        return;
    }
    for(int i = u; i < n; i ++)
        if(!use[i] && now_len + a[i] <= len)
        {
            if(!use[i-1] && a[i] == a[i-1]) continue;      //  不重复搜索：最重要的剪枝。
            use[i] = true;
            dfs(dep + 1, now_len + a[i], i + 1);
            use[i] = false;
        }
}

bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    while(scanf("%d", &n) && n != 0)
    {
        int sum = 0;
        flag = false;
        for(int i = 0; i < n; i ++)
        {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        sort(a, a + n, cmp);     //  从大到小排序。
        for(len = a[0]; len < sum; len ++)
            if(sum % len == 0)           //  枚举能被sum整除的长度。
            {
                memset(use, 0, sizeof(use));
                dfs(0, 0, 0);
                if(flag) break;
            }
        printf("%d\n", len);
    }
    return 0;
}
