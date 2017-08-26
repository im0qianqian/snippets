# K-th Number

## **Description**

> You are working for Macrohard company in data structures department. After failing your previous task about key insertion you were asked to write a new data structure that would be able to return quickly k-th order statistics in the array segment. 
>
> That is, given an array a[1...n] of different integer numbers, your program must answer a series of questions Q(i, j, k) in the form: "What would be the k-th number in a[i...j] segment, if this segment was sorted?" 
>
> For example, consider the array a = (1, 5, 2, 6, 3, 7, 4). Let the question be Q(2, 5, 3). The segment a[2...5] is (5, 2, 6, 3). If we sort this segment, we get (2, 3, 5, 6), the third number is 5, and therefore the answer to the question is 5.



## **Input**

> The first line of the input file contains n --- the size of the array, and m --- the number of questions to answer (1 <= n <= 100 000, 1 <= m <= 5 000). 
>
> The second line contains n different integer numbers not exceeding 10^9 by their absolute values --- the array for which the answers should be given. 
>
> The following m lines contain question descriptions, each description consists of three numbers: i, j, and k (1 <= i <= j <= n, 1 <= k <= j - i + 1) and represents the question Q(i, j, k).



## **Output**

> For each question output the answer to it --- the k-th number in sorted a[i...j] segment.



## **Sample Input**

    7 3
    1 5 2 6 3 7 4
    2 5 3
    4 4 1
    1 7 3



## **Sample Output**

    5
    6
    3



## **题意**

静态查询区间第 k 小的数。



## **思路**

【划分树/主席树】 的基本应用，以下附模板。



## **AC 代码**

### **划分树**

```cpp
#include <iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef __int64 LL;
const int maxn=1e5+10;

int tree[20][maxn];     // 每层每个位置的值
int sorted[maxn];       // 已经排序好的数
int toleft[20][maxn];   // 第 i 层从 1-j 有多少个数被划分到了左边

void build(int l,int r,int dep)
{
    if(l==r)return;
    int mid = (l+r)>>1;
    int same = mid-l+1;     // 等于中间值且被划分到左边数的个数
    for(int i=l; i<=r; i++)
    {
        if(tree[dep][i]<sorted[mid])
            same--;
    }
    int lpos = l;
    int rpos = mid+1;
    for(int i=l; i<=r; i++)
    {
        if(tree[dep][i]<sorted[mid])
            tree[dep+1][lpos++]=tree[dep][i];
        else if(tree[dep][i]==sorted[mid]&&same>0)
            tree[dep+1][lpos++]=tree[dep][i],same--;
        else
            tree[dep+1][rpos++]=tree[dep][i];
        toleft[dep][i]=toleft[dep][l-1]+lpos-l;
    }
    build(l,mid,dep+1);
    build(mid+1,r,dep+1);
}

int query(int L,int R,int l,int r,int dep,int k)
{
    if(l==r)return tree[dep][l];
    int mid = (L+R)>>1;
    int cnt = toleft[dep][r]-toleft[dep][l-1];
    if(cnt>=k)
    {
        int newl = L+toleft[dep][l-1]-toleft[dep][L-1];
        int newr = newl+cnt-1;
        return query(L,mid,newl,newr,dep+1,k);
    }
    else
    {
        int newr = r +toleft[dep][R]-toleft[dep][r];
        int newl = newr-(r-l-cnt);
        return query(mid+1,R,newl,newr,dep+1,k-cnt);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int n,m;
    while(cin>>n>>m)
    {
        memset(tree,0,sizeof(tree));
        for(int i=1; i<=n; i++)
        {
            cin>>tree[0][i];
            sorted[i]=tree[0][i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        int s,t,k;
        while(m--)
        {
            cin>>s>>t>>k;
            cout<<query(1,n,s,t,0,k)<<endl;
        }
    }
    return 0;
}
```



### **主席树**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef __int64 LL;
const int maxn = 2000000;

int a[maxn],b[maxn];
int sum[maxn];
int ls[maxn];
int rs[maxn];
int rk[maxn];
int tot;

void build(int &o,int l,int r)
{
    o=++tot;
    sum[o]=0;
    if(l==r)return;
    int mid = (l+r)>>1;
    build(ls[o],l,mid);
    build(rs[o],mid+1,r);
}

void update(int &o,int l,int r,int last,int p)
{
    o = ++tot;
    ls[o]=ls[last];
    rs[o]=rs[last];
    sum[o]=sum[last]+1;
    if(l==r)return;
    int mid = (l+r)>>1;
    if(p<=mid)update(ls[o],l,mid,ls[last],p);
    else update(rs[o],mid+1,r,rs[last],p);
}

int query(int L,int R,int l,int r,int k)
{
    if(L==R)return L;
    int mid = (L+R)>>1;
    int cnt = sum[ls[r]]-sum[ls[l]];
    if(k<=cnt)return query(L,mid,ls[l],ls[r],k);
    else return query(mid+1,R,rs[l],rs[r],k-cnt);
}

int main()
{
    ios::sync_with_stdio(false);
    int n,m;
    while(cin>>n>>m)
    {
        tot=0;
        for(int i=1; i<=n; i++)
            cin>>a[i],b[i]=a[i];
        sort(b+1,b+n+1);
        int sz = unique(b+1,b+n+1)-(b+1);
        build(rk[0],1,sz);
        for(int i=1; i<=n; i++)
        {
            a[i] = lower_bound(b+1,b+n+1,a[i])-b;
            update(rk[i],1,sz,rk[i-1],a[i]);
        }
        while(m--)
        {
            int l,r,k;
            cin>>l>>r>>k;
            cout<<b[query(1,sz,rk[l-1],rk[r],k)]<<endl;
        }
    }
    return 0;
}
```

