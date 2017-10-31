## I Hate It

## **Description**

> 很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。
>
> 这让很多学生很反感。
>
> 不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。



## **Input**

> 本题目包含多组测试，请处理到文件结束。
>
> 在每个测试的第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，分别代表学生的数目和操作的数目。
>
> 学生ID编号分别从1编到N。
>
> 第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。
>
> 接下来有M行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数A，B。
>
> 当C为'Q'的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。
>
> 当C为'U'的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。



## **Output**

> 对于每一次询问操作，在一行里面输出最高成绩。



## **Sample Input**

    5 6
    1 2 3 4 5
    Q 1 5
    U 3 6
    Q 3 4
    Q 4 5
    U 2 9
    Q 1 5



## **Sample Output**

    5
    6
    5
    9



## **思路**

线段树模板题，附 [点/区间] 修改模板如下。



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

int main()
{
    IO;
    int n,m;
    while(cin>>n>>m)
    {
        int R = 1;
        while(R<n)R<<=1;
        for(int i=1; i<=n; i++)
            cin>>a[i];
        build(1,1,R);
        while(m--)
        {
            char c;
            int l,r;
            cin>>c>>l>>r;
            if(c=='Q')
            {
                _max = 0;
                query(1,1,R,l,r,0);
                cout<<_max<<endl;
            }
            else
                update_set(1,1,R,l,l,r);
        }
    }
    return 0;
}
```

