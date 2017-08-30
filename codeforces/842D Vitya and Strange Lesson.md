# D. Vitya and Strange Lesson

## **Description**

> Today at the lesson Vitya learned a very interesting function — mex. Mex of a sequence of numbers is the minimum non-negative number that is not present in the sequence as element. For example, mex([4, 33, 0, 1, 1, 5]) = 2 and mex([1, 2, 3]) = 0.
>
> Vitya quickly understood all tasks of the teacher, but can you do the same?
>
> You are given an array consisting of n non-negative integers, and m queries. Each query is characterized by one number x and consists of the following consecutive steps:
>
> Perform the bitwise addition operation modulo 2 (xor) of each array element with the number x.
>
> Find mex of the resulting array.
>
> Note that after each query the array changes.



## **Input**

> First line contains two integer numbers n and m (1 ≤ n, m ≤ 3·10^5) — number of elements in array and number of queries.
>
> Next line contains n integer numbers ai (0 ≤ ai ≤ 3·10^5) — elements of then array.
>
> Each of next m lines contains query — one integer number x (0 ≤ x ≤ 3·10^5).



## **Output**

> For each query print the answer on a separate line.



## **Sample Input**

    5 4
    0 1 5 6 7
    1
    1
    4
    5



## **Sample Output**

    2
    2
    0
    2



## **题意**

给出长度为 n 的非负整数序列，求该序列异或 x 以后的 mex 值。



## **思路**

将所有的数字以二进制的方式插入到 trie 树中，然后我们便可以很方便的求出一个序列的 mex 值。

假如要全局异或一个数 x ，且 x 的二进制从高到低第 i 位是 1 ，则 trie 树中的第 i 层所有节点都要翻转左右孩子。



## **AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7+10;
const int maxm = 20;
int n,m,tot;
int a[maxn];

struct node
{
    int cnt,res;
    node *next[2];
} pn[maxn],*root;

void insert(int x)      //trie树构建
{
    node *p=root;
    p->cnt++;
    for(int i=maxm; ~i; i--)
    {
        int k=(x>>i)&1;
        if(!p->next[k])p->next[k]=&pn[tot++];
        p=p->next[k];
        p->cnt++;
    }
}

void push_down(node *p,int d)       //异或时反转左右孩子
{
    for(int i=0; i<2; i++)
        if(p->next[i])
            p->next[i]->res^=p->res;
    if((p->res>>d)&1)
        swap(p->next[0],p->next[1]);
    p->res=0;
}

void solve()
{
    int ans=0;
    node *p=root;
    for(int i=maxm; ~i; i--)
    {
        push_down(p,i);
        if((p->next[0]?p->next[0]->cnt:0)!=(1<<i))  //寻找mex
            p=p->next[0];
        else
            p=p->next[1],ans|=1<<i;
        if(!p)break;
    }
    cout<<ans<<endl;
}

int main()
{
    cin>>n>>m;
    for(int i=0; i<n; i++)
        cin>>a[i];
    sort(a,a+n);
    n = unique(a,a+n)-a;
    root = &pn[tot++];
    for(int i=0; i<n; i++)
        insert(a[i]);
    for(int i=0; i<m; i++)
    {
        int x;
        cin>>x;
        root->res^=x;
        solve();
    }
    return 0;
}
```

