# D. The Bakery

## **Description**

> ![img](https://www.dreamwings.cn/wp-content/uploads/2018/02/babc0d65dbe3143c2722ff1e61de866d1c7735f7.png)
>
> Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.
>
> Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.
>
> She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of n cakes the oven is going to bake today. Slastyona has to pack exactly k boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).
>
> Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.



## **Input**

> The first line contains two integers n and k (1 ≤ n ≤ 35000, 1 ≤ k ≤ min(n, 50)) – the number of cakes and the number of boxes, respectively.
>
> The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ n) – the types of cakes in the order the oven bakes them.



## **Output**

> Print the only integer – the maximum total value of all boxes with cakes.



## **Examples input**

    4 1
    1 2 2 1



## **Examples output**

    2



## **题意**

有 $n$ 个数字分成 $k$ 段，每一段的价值是其中不同数字的个数，求总的最大价值。



## **思路**

很容易想到的一种 dp 思路，其中，$dp[i][k]$ 代表把前 $i$ 个数字分成 $k$ 段所能得到的最大价值。

显然：

- 当 $k=1$ 时， $dp[i][1]$ 为前 $i$ 个数字的不同个数
- 当 $k>1$ 时， $dp[i][k]=\max_{1≤j≤i}dp[j-1][k-1]+c[j][i]$ （ $c[j][i]$ 代表区间 $[j,i]$ 数字的不同个数）

算得 dp 数组中的每一个值朴素的做法需要 $O(n)$ 的时间，因此这样总的时间复杂度为 $O(k \times n^2)$ 。

我们考虑用线段树来优化状态的转移，转移方程中第 $k$ 行的值取决于第 $k-1$ 行的值，因此我们在算出第 $k-1$ 行以后，考虑建立该行的线段树，从而快速的求出第 $k$ 行的值。

但是我们发现，在求第 $k$ 行值的时候 $c[j][i]$ 会随着 $i$ 的变化而变化。

我们令树的叶子节点 $a[j]$ 表示 $dp[j-1][k-1]+c[j][i]$ ，则状态转移方程变为了 $dp[i][k]=\max_{1≤j≤i}a[j]$ ，此时 $dp[j-1][k-1]$ 是已知的，我们只需要考虑由 $i-1$ 到 $i$ 时 $c[j][i]$ 的变化。

设第 $i$ 个数字为 $y$ ，前一个出现 $y$ 的位置为 $pre[y]$ ，那么显然当前所增加的数字 $y$ 会对区间 $[pre[y]+1,i]$ 产生影响，因此 $c[s,i],(s\in[pre[y]+1,i])$ 需要加 $1$ ，这样便可以成功从 $i-1$ 转移到 $i$ 了。

时间复杂度： $O(k \times n \times \log(n))$



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
#define default_setv -1

using namespace std;
typedef long long LL;
const int maxn = 1e5+10;

int sumv[maxn<<2];  //四倍空间
int minv[maxn<<2];
int maxv[maxn<<2];
int addv[maxn<<2];
int setv[maxn<<2];  //初始值：-1
int a[maxn];
int pos[maxn];
int pre[maxn];
int dp[maxn][55];

void maintain(int o,int L,int R)
{
    int lc = o<<1,rc=o<<1|1;
    sumv[o] = minv[o] = maxv[o] = 0;
    if(setv[o] != default_setv)
    {
        sumv[o] = setv[o] * (R-L+1);
        minv[o] = maxv[o] = setv[o];
    }
    else if(R>L)
    {
        sumv[o] = sumv[lc] + sumv[rc];
        minv[o] = min(minv[lc],minv[rc]);
        maxv[o] = max(maxv[lc],maxv[rc]);
    }
    minv[o] += addv[o];
    maxv[o] += addv[o];
    sumv[o] += addv[o] * (R-L+1);
}

void pushdown(int o)
{
    int lc = o<<1,rc = o<<1|1;
    if(setv[o] != default_setv)
    {
        setv[lc] = setv[rc] = setv[o];
        addv[lc] = addv[rc] = 0;
        setv[o] = default_setv;
    }
    if(addv[o] != 0)
    {
        addv[lc] += addv[o];
        addv[rc] += addv[o];
        addv[o] = 0;
    }
}

/*
 * o: 当前节点(1)，修改区间：[y1,y2] ，添加值：v_add，总区间：[L,R] (这里的L,R必须是2的幂次)
 */
void update_add(int o,int L,int R,int y1,int y2,int v_add)
{
    int lc = o<<1,rc = o<<1|1;
    if(y1<=L&&y2>=R)
        addv[o] += v_add;
    else
    {
        pushdown(o);
        int M = L + (R-L)/2;
        if(y1<=M)
            update_add(lc,L,M,y1,y2,v_add);
        else
            maintain(lc,L,M);
        if(y2>M)
            update_add(rc,M+1,R,y1,y2,v_add);
        else
            maintain(rc,M+1,R);
    }
    maintain(o,L,R);
}

/*
 * o: 当前节点(1)，修改区间：[y1,y2] ，修改值：v_set，总区间：[L,R] (这里的L,R必须是2的幂次)
 */
void update_set(int o, int L, int R,int y1,int y2,int v_set)
{
    int lc = o<<1, rc = o<<1|1;
    if(y1 <= L && y2 >= R)
    {
        setv[o] = v_set;
        addv[o] = 0;
    }
    else
    {
        pushdown(o);
        int M = L + (R-L)/2;
        if(y1 <= M)
            update_set(lc, L, M,y1,y2,v_set);
        else
            maintain(lc, L, M);
        if(y2 > M)
            update_set(rc, M+1, R,y1,y2,v_set);
        else
            maintain(rc, M+1, R);
    }
    maintain(o, L, R);
}

/*
 * o: 当前节点(1)，查询区间：[y1,y2] ，初始累加(0)，总区间：[L,R] (这里的L,R必须是2的幂次)
 */
int _min, _max, _sum;
void query(int o, int L, int R, int y1,int y2, int add)
{
    if(setv[o] != default_setv)
    {
        _sum += (add+setv[o]+addv[o]) * (min(R, y2)-max(L, y1)+1);
        _min = min(_min, setv[o]+addv[o]+add);
        _max = max(_max, setv[o]+addv[o]+add);
    }
    else if(y1 <= L && y2 >= R)
    {
        _sum += sumv[o] + add * (R-L+1);
        _min = min(_min, minv[o]+add);
        _max = max(_max, maxv[o]+add);
    }
    else
    {
        int M = L + (R-L)/2;
        if(y1 <= M)
            query(o*2, L, M, y1, y2,add+addv[o]);
        if(y2 > M)
            query(o*2+1, M+1, R, y1, y2, add + addv[o]);
    }
}

/*
 * o: 当前节点(1)，总区间：[L,R] (这里的L,R必须是2的幂次)
 * 所有 setv 初始化为 -1，所有叶子节点 addv 为当前值
 */
void build(int o,int L,int R,int op)
{
    if(L==R)
    {
        setv[o] = default_setv;
        addv[o] = sumv[o] = maxv[o] = minv[o] = dp[L-1][op];
    }
    else
    {
        int M = L + (R-L)/2;
        int lc = o<<1,rc = o<<1|1;
        build(lc,L,M,op);
        build(rc,M+1,R,op);

        addv[o] = 0;
        setv[o] = default_setv;
        sumv[o] = sumv[lc] + sumv[rc];
        maxv[o] = max(maxv[lc],maxv[rc]);
        minv[o] = min(minv[lc],minv[rc]);
    }
}

/*
 * 测试函数，R 代表叶子节点个数
 */
void test(int R,int n)
{
    cout<<"----------"<<endl;
    auto init = [&]()
    {
        _sum = 0;
        _min = INT_MAX;
        _max = INT_MIN;
    };
    for(int i=1; i<=n; i++)
    {
        init();
        query(1,1,R,i,i,0);
        cout<<i<<" --> "<<_sum<<"\t "<<_min<<"\t "<<_max<<endl;
    }
    init();
    query(1,1,R,1,R,0);
    cout<<"total: "<<_sum<<endl;
    cout<<"----------"<<endl;
}

int main()
{
    IO;
    int n,k;
    cin>>n>>k;
    int R = 1;
    while(R<n)
        R<<=1;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
        pre[i] = pos[a[i]] + 1;
        pos[a[i]] = i;
    }
    for(int i=1; i<=k; i++)
    {
        build(1,1,R,i-1);
        for(int j=1; j<=n; j++)
        {
            update_add(1,1,R,pre[j],j,1);
            _max = 0;
            query(1,1,R,1,j,0);
            dp[j][i] = _max;
        }
    }
    cout<<dp[n][k]<<endl;
    return 0;
}
```

