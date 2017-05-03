# Reincarnation

## **Problem Description**

> Now you are back,and have a task to do:
>
> Given you a string s consist of lower-case English letters only,denote f(s) as the number of distinct sub-string of s.
>
> And you have some query,each time you should calculate f(s[l...r]), s[l...r] means the sub-string of s start from l end at r.



## **Input**

> The first line contains integer T(1<=T<=5), denote the number of the test cases.
>
> For each test cases,the first line contains a string s(1 <= length of s <= 2000).
>
> Denote the length of s by n.
>
> The second line contains an integer Q(1 <= Q <= 10000),denote the number of queries.
>
> Then Q lines follows,each lines contains two integer l, r(1 <= l <= r <= n), denote a query.



## **Output**

> For each test cases,for each query,print the answer in one line.



## **Sample Input**

    2
    bbaba
    5
    3 4
    2 2
    2 5
    2 4
    1 4
    baaba
    5
    3 3
    3 4
    1 4
    3 5
    5 5



## **Sample Output**

    3
    1
    7
    5
    8
    1
    3
    8
    5
    1



## **题意**

求区间不相同子串个数。



## **思路**

**模板题目，有好多种解法：**字符串哈希、后缀数组、后缀自动机...



## **AC 代码**

### **字符串哈希**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

const int HASH = 10007;
const int MAXN = 2100;

struct hashmap
{
    int head[HASH],next[MAXN],size;
    unsigned long long state[MAXN];
    int f[MAXN];
    void init()
    {
        size=0;
        memset(head,-1,sizeof(head));
    }
    int insert(unsigned long long val,int _id)
    {
        int h=val%HASH;
        for(int i=head[h]; i!=-1; i=next[i])
        {
            if(val==state[i])
            {
                int temp=f[i];
                f[i]=_id;
                return temp;
            }
        }
        f[size]=_id;
        state[size]=val;
        next[size]=head[h];
        head[h]=size++;
        return 0;
    }
} h;

const int seed = 13331;
unsigned long long P[MAXN];
unsigned long long S[MAXN];
char str[MAXN];
int ans[MAXN][MAXN];

int main()
{
    P[0]=1;
    for(int i=1; i<MAXN; i++)
        P[i]=P[i-1]*seed;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",str);
        int n=strlen(str);
        for(int i=1; i<=n; i++)
            S[i]=S[i-1]*seed+str[i-1];
        memset(ans,0,sizeof(ans));
        for(int L=1; L<=n; L++)
        {
            h.init();
            for(int i=1; i+L-1<=n; i++)
            {
                int l=h.insert(S[i+L-1]-S[i-1]*P[L],i);
                ans[i][i+L-1]++;
                ans[l][i+L-1]--;
            }
        }
        for(int i=n; i>=0; i--)
            for(int j=i; j<=n; j++)
                ans[i][j]+=ans[i+1][j]+ans[i][j-1]-ans[i+1][j-1];
        int Q;
        scanf("%d",&Q);
        while(Q--)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            printf("%d\n",ans[a][b]);
        }
    }
    return 0;
}
```



### **后缀数组**

```cpp
#include<algorithm>
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=2010;
typedef long long ll;
char txt[maxn];
int sa[maxn],T1[maxn],T2[maxn],ct[maxn],he[maxn],rk[maxn],n,m;
void getsa(char *st)
{
    int i,k,p,*x=T1,*y=T2;
    for(i=0; i<m; i++) ct[i]=0;
    for(i=0; i<n; i++) ct[x[i]=st[i]]++;
    for(i=1; i<m; i++) ct[i]+=ct[i-1];
    for(i=n-1; i>=0; i--)
        sa[--ct[x[i]]]=i;
    for(k=1,p=1; p<n; k<<=1,m=p)
    {
        for(p=0,i=n-k; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(i=0; i<m; i++) ct[i]=0;
        for(i=0; i<n; i++) ct[x[y[i]]]++;
        for(i=1; i<m; i++) ct[i]+=ct[i-1];
        for(i=n-1; i>=0; i--) sa[--ct[x[y[i]]]]=y[i];
        for(swap(x,y),p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
    }
}

void gethe(char *st)
{
    int i,j,k=0;
    for(i=0; i<n; i++) rk[sa[i]]=i;
    for(i=0; i<n-1; i++)
    {
        if(k) k--;
        j=sa[rk[i]-1];
        while(st[i+k]==st[j+k]) k++;
        he[rk[i]]=k;
    }
}

int main()
{
    int t,i,q,le,ri,lcp,ml,ans,tp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",txt);
        n=strlen(txt)+1;
        m=150;
        getsa(txt);
        gethe(txt);
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d",&le,&ri);
            le--,ri--;
            ans=lcp=ml=0;
            for(i=1; i<n; i++)
            {
                lcp=min(lcp,he[i]);
                ml=min(ml,lcp);
                if(sa[i]>=le&&sa[i]<=ri)
                {
                    ans+=ri-sa[i]+1-min(ri-sa[i]+1,ml);
                    lcp=he[i+1];
                    tp=min(lcp,ri-sa[i]+1);
                    ml=max(ml,tp);
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
```



### **后缀自动机**

```cpp
#include<algorithm>
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=2010<<1;
typedef long long ll;
struct node
{
    node *f,*ch[30];
    int len,way;
    void init()
    {
        way=0;
        memset(ch,0,sizeof ch);
    }
}*root,*tail,sam[maxn<<1];
int tot,dp[2010][2010];
char txt[maxn];
void init()
{
    tot=0;
    root=tail=&sam[tot++];
    root->f=NULL;
    root->len=0;
    root->init();
    root->way=1;
}
void Insert(int c)
{
    node *p=tail,*np=&sam[tot++];
    np->init(),np->len=p->len+1;
    while(p&&!p->ch[c])
    {
        np->way+=p->way;
        p->ch[c]=np,p=p->f;
    }
    tail=np;
    if(!p)
        np->f=root;
    else
    {
        if(p->ch[c]->len==p->len+1)
            np->f=p->ch[c];
        else
        {
            node *q=p->ch[c],*nq=&sam[tot++];
            *nq=*q;
            nq->len=p->len+1;
            nq->way=0;
            q->f=np->f=nq;
            while(p&&p->ch[c]==q)
            {
                p->ch[c]->way-=p->way;
                nq->way+=p->way;
                p->ch[c]=nq,p=p->f;
            }
        }
    }
}

int main()
{
    int i,j,t,len,q,le,ri;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",txt);
        len=strlen(txt);
        for(i=0; i<len; i++)
        {
            init();
            for(j=i; j<len; j++)
            {
                Insert(txt[j]-'a');
                dp[i][j]=tail->way;
            }
            for(j=i+1; j<len; j++)
                dp[i][j]+=dp[i][j-1];
        }
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d",&le,&ri);
            printf("%d\n",dp[le-1][ri-1]);
        }
    }
    return 0;
}
```

