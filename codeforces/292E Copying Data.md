# E. Copying Data

## **Description**

> We often have to copy large volumes of information. Such operation can take up many computer resources. Therefore, in this problem you are advised to come up with a way to copy some part of a number array into another one, quickly.
>
> More formally, you've got two arrays of integers $a_1, a_2, ..., a_n$ and $b_1, b_2, ..., b_n$ of length $n$ . Also, you've got $m$ queries of two types:
>
> Copy the subsegment of array $a$ of length $k$, starting from position $x$, into array $b$, starting from position $y$, that is, execute $b_{y + q} = a_{x + q}$ for all integer $q$ $(0 ≤ q < k)$. The given operation is correct — both subsegments do not touch unexistent elements.
>
> Determine the value in position $x$ of array $b$, that is, find value $b_x$ .
>
> For each query of the second type print the result — the value of the corresponding element of array $b$.



## **Input**

> The first line contains two space-separated integers $n$ and $m$ $(1 ≤ n, m ≤ 10^5)$ — the number of elements in the arrays and the number of queries, correspondingly. The second line contains an array of integers $a_1, a_2, ..., a_n$ $(|a_i| ≤ 10^9)$. The third line contains an array of integers $b_1, b_2, ..., b_n$ $(|b_i| ≤ 10^9)$.
>
> Next $m$ lines contain the descriptions of the queries. The i-th line first contains integer $t_i$ — the type of the i-th query $(1 ≤ ti ≤ 2)$. If $t_i = 1$, then the i-th query means the copying operation. If $t_i = 2$, then the i-th query means taking the value in array $b$. If $t_i = 1$, then the query type is followed by three integers $x_i, y_i, k_i$ $(1 ≤ x_i, y_i, k_i ≤ n)$ — the parameters of the copying query. If $t_i = 2$, then the query type is followed by integer $x_i$ $(1 ≤ x_i ≤ n)$ — the position in array $b$.
>
> All numbers in the lines are separated with single spaces. It is guaranteed that all the queries are correct, that is, the copying borders fit into the borders of arrays $a$ and $b$.



## **Output**

> For each second type query print the result on a single line.



## **Examples input**

    5 10
    1 2 0 -1 3
    3 1 5 -2 0
    2 5
    1 3 3 3
    2 5
    2 4
    2 1
    1 2 1 4
    2 1
    2 4
    1 4 2 1
    2 2



## **Examples output**

    0
    3
    -1
    3
    2
    3
    -1



## **题意**

对于数组 $a$ 和数组 $b$ ，支持两种操作：

1. 用 $a$ 中从 $x$ 开始的连续 $k$ 个元素覆盖掉 $b$ 中从 $y$ 开始的连续 $k$ 个元素
2. 询问 $b$ 中下标为 $k$ 的元素是多少



## **思路**

我们知道，覆盖算是一种擦写不可逆式的操作，即当前元素的值只与该位置最后一次的覆盖有关

于是结合线段树区间 set 操作，我们在覆盖时将某个区间更新为该次操作的索引

对于每一次的查询，只需要找到其覆盖的索引，然后便可以用公式得出它的值是多少啦~

---

算是一道线段树的模板题吧~ 当然也有其他做法啦~



## **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
#define default_setv -1

using namespace std;
typedef long long LL;
const int maxn = 2e5+10;

int sumv[maxn<<2];  //四倍空间
int minv[maxn<<2];
int maxv[maxn<<2];
int addv[maxn<<2];
int setv[maxn<<2];  //初始值：-1
int a[maxn];
int A[maxn],B[maxn];

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
void build(int o,int L,int R)
{
    if(L==R)
    {
        setv[o] = default_setv;
        addv[o] = sumv[o] = maxv[o] = minv[o] = a[L];
    }
    else
    {
        int M = L + (R-L)/2;
        int lc = o<<1,rc = o<<1|1;
        build(lc,L,M);
        build(rc,M+1,R);

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

int x[maxn],y[maxn],k[maxn];
int main()
{
    IO;
    int n,m;
    cin>>n>>m;
    int R = 1;
    while(R<n)
        R<<=1;
    for(int i=1; i<=n; i++)
        cin>>A[i];
    for(int i=1; i<=n; i++)
        cin>>B[i];
    for(int i=1; i<=m; i++)
    {
        int op;
        cin>>op;
        if(op==2)
        {
            cin>>k[i];
            _sum = 0;
            query(1,1,R,k[i],k[i],0);
            if(_sum==0)
                cout<<B[k[i]]<<endl;
            else
                cout<<A[k[i]-y[_sum]+x[_sum]]<<endl;
        }
        else
        {
            cin>>x[i]>>y[i]>>k[i];
            update_set(1,1,R,y[i],y[i]+k[i]-1,i);
        }
    }
    return 0;
}
```

