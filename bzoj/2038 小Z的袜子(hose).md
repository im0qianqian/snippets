# 小Z的袜子(hose)

## **Description**

> 作为一个生活散漫的人，小Z 每天早上都要耗费很久从一堆五颜六色的袜子中找出一双来穿。终于有一天，小Z 再也无法忍受这恼人的找袜子过程，于是他决定听天由命……
>
> 具体来说， 小Z 把这 N 只袜子从 1 到 N 编号，然后从编号 L 到 R ( L 尽管 小Z 并不在意两只袜子是不是完整的一双，甚至不在意两只袜子是否一左一右，他却很在意袜子的颜色，毕竟穿两只不同色的袜子会很尴尬。
>
> 你的任务便是告诉 小Z ，他有多大的概率抽到两只颜色相同的袜子。当然， 小Z 希望这个概率尽量高，所以他可能会询问多个 (L,R) 以方便自己选择。



## **Input**

> 输入文件第一行包含两个正整数 N 和 M 。 N 为袜子的数量， M 为 小Z 所提的询问的数量。接下来一行包含 N 个正整数 Ci ，其中 Ci 表示第 i 只袜子的颜色，相同的颜色用相同的数字表示。再接下来 M 行，每行两个正整数 L，R 表示一个询问。



## **Output**

> 包含 M 行，对于每个询问在一行中输出分数 A/B 表示从该询问的区间 [L,R] 中随机抽出两只袜子颜色相同的概率。若该概率为 0 则输出 0/1 ，否则输出的 A/B 必须为最简分数。( N,M ≤ 50000，1 ≤ L < R ≤ N，Ci ≤ N )



## **Sample Input**

    6 4
    1 2 3 3 3 2
    2 6
    1 3
    3 5
    1 6



## **Sample Output**

    2/5
    0/1
    1/1
    4/15


## **思路**

区间任意挑选两个的组合数很简单，那剩下的问题便是该区间内有多少组相同的颜色。

我们知道，这样的情况共有 $\sum_{i=1}^{v}C_{f(i)}^{2}$ 种，其中 $v$ 为所有的颜色数目， $f(i)$ 为颜色 $i$ 在区间内的出现次数。

等价于 $\frac{\sum_{i=1}^{v}f(i)^2-f(i)}{2}$ ，即 $\frac{\sum_{i=1}^{v}f(i)^2}{2}-\frac{r-l+1}{2}$ 。

于是我们可以使用**莫队算法**来解决这个问题啦~

每个区间可以抽象成平面中的点，每次转移的花费都相当于从某一点到另一点的曼哈顿距离，所以最好的做法便是在曼哈顿最小生成树上的转移啦。

不过我们有一种更简洁的方式 --- 分块

利用分块，我们可以实现 $O(n\sqrt{n})$ 的时间复杂度。

我们取 $x=\sqrt{n}$ ，以 $[1,x],[x+1,2x],[2x+1,3x]...$ 分块

1. 排序：以左端点为第一关键字，右端点为第二关键字排序
2. 从左到右处理所有的询问（离线）
3. 不断调整 `l,r` 的位置并同时修改结果



## **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 50010;
typedef long long LL;
int n,m,unit;
int col[maxn];
LL ans,s[maxn];

LL gcd(LL a,LL b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}

struct node
{
    int l,r,id;
    LL cnt,res;
    void reduce()
    {
        LL gc=gcd(cnt,res);
        cnt/=gc;
        res/=gc;
    }
} a[maxn];

inline void update(int x,int add)
{
    ans-=(LL)s[col[x]]*s[col[x]];
    s[col[x]]+=add;
    ans+=(LL)s[col[x]]*s[col[x]];
}

inline void init()
{
    ans=0;
    memset(s,0,sizeof(s));
}

bool cmp1(const node &x,const node &y)
{
    if(x.l/unit!=y.l/unit)      // 分块
        return x.l/unit<y.l/unit;
    return x.r<y.r;
}

bool cmp2(const node &x,const node &y)
{
    return x.id<y.id;
}

void solve()
{
    init();
    sort(a,a+m,cmp1);
    for(int i=0,l=1,r=0; i<m; i++)
    {
        for(; r<a[i].r; r++)update(r+1,1);
        for(; r>a[i].r; r--)update(r,-1);
        for(; l<a[i].l; l++)update(l,-1);
        for(; l>a[i].l; l--)update(l-1,1);
        a[i].cnt=ans-(r-l+1);
        a[i].res=(LL)(r-l+1)*(r-l);
        a[i].reduce();
    }
    sort(a,a+m,cmp2);
    for(int i=0; i<m; i++)
        printf("%lld/%lld\n",a[i].cnt,a[i].res);
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        unit=(int)sqrt(n);
        for(int i=1; i<=n; i++)
            scanf("%d",col+i);
        for(int i=0; i<m; i++)
            scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i;
        solve();
    }
    return 0;
}
```

