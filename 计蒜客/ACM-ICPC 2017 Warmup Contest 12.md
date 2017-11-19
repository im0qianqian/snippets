# ACM-ICPC 2017 Warmup Contest 12

因为等了很久计蒜客上都没有更新，所以目前找不到题目，只能凭借记忆写写咯~

全场不在状态抱着不仔细检查直接交让评测机来judge心情的我，最后居然取得了 rk2 ，一定是高手都没有来参加的缘故。



## A. Abandoned Animal

### **题意**

给定一些商品可以在第几家店买的，然后输入购买商品的顺序，问购买序列是否唯一（要求第几家序号不下降）。

若唯一，输出 `unique` ，不唯一输出 `ambiguous` ，不存在时输出 `impossible` 。



### **思路**

找一个序号尽可能小的合法序列与一个序号尽可能大的合法序列，若这两个序列相等则结果唯一，否则不唯一。

若无法找到这样的序列则结果不存在。

寻找下一个可行序号的过程可以用二分优化。



### **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e5+10;
const int mod = 1e9+7;

unordered_map<string,int > mp;
string fi[maxn];
vector<int> g[maxn];
vector<int> lef,rig;
int n,m,k,tot;
int solve()
{
    int now = 0;
    for(int i=0; i<m; i++)
    {
        vector<int>& tmp = g[mp[fi[i]]];
        auto s = lower_bound(tmp.begin(),tmp.end(),now) - tmp.begin();
        if(s>=(int)tmp.size())return 0;
        now = tmp[s];
        lef.push_back(now);
    }
    now = *g[mp[fi[m-1]]].rbegin();
    for(int i=m-1; i>=0; i--)
    {
        vector<int> &tmp = g[mp[fi[i]]];
        auto s = upper_bound(tmp.begin(),tmp.end(),now) - tmp.begin() - 1;
        if(s<0||s>=(int)tmp.size())return 0;
        now = tmp[s];
        rig.push_back(now);
    }
    for(int i=0; i<m; i++)
        if(lef[i]!=rig[m-i-1])
            return 2;
    return 1;
}

int main()
{
    IO;
    int id;
    string tmp;
    cin>>n>>k;
    for(int i=0; i<k; i++)
    {
        cin>>id>>tmp;
        if(!mp.count(tmp))
            mp[tmp] = tot++;
        g[mp[tmp]].push_back(id);
    }
    for(int i=0; i<tot; i++)
        sort(g[i].begin(),g[i].end());
    cin>>m;
    bool flag = false;
    for(int i=0; i<m; i++)
    {
        cin>>fi[i];
        if(!mp.count(fi[i]))
            flag = true;
    }
    int op = solve();
    if(op==0||flag)
        cout<<"impossible"<<endl;
    else if(op==1)
        cout<<"unique"<<endl;
    else
        cout<<"ambiguous"<<endl;
    return 0;
}
```



## C. Crowd Control

### **题意**

给定一张图，每条边都有它的流量，问从节点 0 到节点 n-1 最大流量的这条路径上需要剪掉哪些边才可以使得流不散失。



### **思路**

乍看可能是最大流的题目，但是没有想到与它有什么关联。

因为节点的数目只有 1000 ，所以我考虑直接 bfs ，寻找一条最大流的路径，然后遍历该条路径判断哪些边可剪。

奇怪的是如果一些边剪掉可以使得流从这里断掉，然后其他一些边可以不剪的情况应该怎么办，两个样例的结果让人费解。

我的代码最后返回的内存超限，一定是数组开太大的缘故，本来以外是 WA ，就没有再提交看看，先存一下代码，等找的题目以后再改。



### **内存超限 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e6+10;
struct node
{
public:
    int to;
    int next;
    int cap;
    int id;
    node() {}
    node(int t,int n,int c,int i):to(t),next(n),cap(c),id(i)
    {
    }
} edge[maxn];
int head[maxn],tot;
int n,m;

void init()
{
    memset(head,-1,sizeof(head));
    tot=0;
}

struct N
{
    int cap;
    int last;
    int now;
    N() {}
    N(int c,int l,int n)
    {
        cap = c;
        last = l;
        now = n;
    }
} tmp[maxn<<2];
int top;

void addedge(int u,int v,int cap,int id)
{
    edge[tot].to = v;
    edge[tot].cap = cap;
    edge[tot].id = id;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int vis[maxn];
void bfs()
{
    memset(vis,0,sizeof(vis));
    queue<int> sk;
    tmp[top] = N(500000,-1,0);
    sk.push(top++);
    int maxflow = 0,ans = 0;
    while(!sk.empty())
    {
        int p = sk.front();
        sk.pop();
        if(tmp[p].now==n-1)
        {
            if(maxflow<tmp[p].cap)
            {
                maxflow = tmp[p].cap;
                ans = p;
            }
            continue;
        }

        int u = tmp[p].now;
        if(vis[u])
        {
            if(tmp[p].cap>vis[u])
                vis[u] = tmp[p].cap;
            else
                continue;
        }
        vis[u] = tmp[p].cap;
//        cout<<p<<endl;
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            int to = edge[i].to;
            int cap = edge[i].cap;
            tmp[top++] = N(min(cap,tmp[p].cap),p,to);
            sk.push(top-1);
        }
    }
    vector<int> path;
    int now = ans;
    while(now!=-1)
    {
        path.push_back(tmp[now].now);
        now = tmp[now].last;
    }
    reverse(path.begin(),path.end());
    vector<int> ak;
    for(int i=0;i<(int)path.size()-1;i++)
    {
        for(int k=head[i];k!=-1;k=edge[k].next)
        {
            if(edge[k].to!=path[i+1])
            {
//                cout<<i<<" "<<edge[k].to<<" "<<edge[k].id<<endl;
                ak.push_back(edge[k].id);
            }
        }
    }
    sort(ak.begin(),ak.end());
    int len = unique(ak.begin(),ak.end()) - ak.begin();
    if(len==0)
        cout<<"none"<<endl;
    else
    {
        for(int i=0;i<len;i++)
            cout<<ak[i]<<(i!=len-1?" ":"\n");
    }
}

int main()
{
    IO;
    cin>>n>>m;
    init();
    for(int i=0; i<m; i++)
    {
        int u,v,cap;
        cin>>u>>v>>cap;
        addedge(u,v,cap,i);
        addedge(v,u,cap,i);
    }
    bfs();
    return 0;
}
```



## D. Disastrous Doubling

### **题意**

研究人员需要使用某种细菌进行实验，给定一个序列代表接下来每个小时所用的细菌数目，已知初始时细菌的数目为 1 ，其数目每小时会翻倍增长，并且等到第一个小时以后开始实验，问最后残余的细菌数目。



### **思路**

因为细菌的数目可能会呈指数级上升，所以首先要想到大数。

然后用 java 模拟一下即可，最后别忘了 mod 1e9+7 （所以因为这个 WA 了一次，果然不在状态）。



### **AC 代码**

```java
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	static BigInteger b[] = new BigInteger[110000];
	static BigInteger mo = new BigInteger("1000000007");
	private static Scanner cin;

	public static void main(String[] args) {
		cin = new Scanner(System.in);
		int n;
		n = cin.nextInt();
		BigInteger now = BigInteger.ONE;
		boolean flag = true;
		for (int i = 0; i < n; i++) {
			now = now.add(now);
			b[i] = cin.nextBigInteger();
			if (now.compareTo(b[i]) < 0) {
				flag = false;
			}
			now = now.subtract(b[i]);

		}
		if (!flag) {
			System.out.println("error");
		} else
			System.out.println(now.mod(mo));
	}
}
```



## E. Envious Exponents

### **题意**

给定两个数 n 与 k ，问比 n 大的最小的哪个数字其二进制 1 的个数为 k 。



### **思路**

我们设 $count$ 代表 $n$ 二进制中 $1$ 的个数。

- 假如 $count<k$ ，显然我们只要在 $n$ 的基础上从其最低位往高位二进制为 $0$ 的地方补 $k-count$ 个 $1$ 即可。
- 否则我们需要消除 $count-k+1$ 个 $1$ 然后在前面补充一个 $1$ ，消除的规则是从低往高位遍历，如果当前位为 $1$ 且还存在需要消除的部分，则消除当前位，如果当前二进制 $1$ 的个数刚好等于 $k$ ，则接下来将遇到的所有 $1$ 全部移到二进制的低位，直到填充第一个遇到的 $0$ 。



### **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 1e5+10;
const int mod = 1e9+7;

LL n,k;
bitset<100> ks;

int main()
{
    IO;
    cin>>n>>k;
    ks = n;
    if(ks.count()<k)
    {
        int now = 0;
        k-=ks.count();
        while(k)
        {
            if(!ks[now])
            {
                ks[now] = 1;
                k--;
            }
            now++;
        }
        cout<<ks.to_ullong()<<endl;
    }
    else
    {
        int fq = ks.count()-k;
        int last = 0;
        bool flag = false;
        for(int i=0; i<100; i++)
        {
            if(ks[i])
            {
                if(fq==0&&!flag)    //当前 1 的个数为 k，达到饱和，消除当前位，接下来遇到所有 1 置后
                {
                    flag = true;
                    ks.reset(i);
                    continue;
                }
                if(flag)            //当前 1 的个数为 k-1 ，将遇到的所有 1 全部置后
                {
                    ks.reset(i);
                    ks.set(last++);
                }
                if(!flag)           //存在可消除的 1，消除
                    fq--,ks.reset(i);
            }
            else
            {
                if(flag)    //1 的个数达到 k-1 填充第一个遇到的 0
                {
                    ks.set(i);
                    break;
                }
            }
        }
//        cout<<ks<<endl;
        cout<<ks.to_ullong()<<endl;
    }
    return 0;
}
```



## H. Horror Film Night

### **题意**

两个人想一起看电影，给出 A 和 B 分别喜欢看的电影所播放的时间，每天只有一场电影，并且每个人都不想连续两次看自己不喜欢的电影，问最多可以挑选多少场电影共同观看。



### **思路**

既然是挑选一个子序列的问题，那当然区间长度越大越好啦~

用数组做桶分别记录 A 和 B 喜欢电影的播放时间，从 0 开始枚举时间到最大，记录上一次看的是谁喜欢的电影。

若喜欢当前电影的人与上一次相同则跳过，否则 $ans+1$ （注意两个人共同喜欢一场电影的情况）。



### **AC 代码**

```cpp
#include<bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
using namespace std;
typedef long long LL;
const int maxn = 2e6 + 10;
const int mod = 1e9+7;

int a[maxn],b[maxn];
int main()
{
    IO;
    int n,m;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int x;
        cin>>x;
        a[x] = 1;
    }
    cin>>m;
    for(int i=0; i<m; i++)
    {
        int x;
        cin>>x;
        b[x] = 1;
    }
    int ans = 0,last = 0;
    for(int i=0; i<maxn; i++)
    {
        if(a[i]||b[i])
        {
            if(a[i]&&b[i])ans++,last = 0;
            else if(a[i])
            {
                if(last!=1)
                    ans++,last = 1;
            }
            else
            {
                if(last!=2)
                    ans++,last=2;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```



## K. Knight's Marathon

### **题意**

给出一个 $n \times m$ 的棋盘，问马从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 所需要跳的最少步数。 $(8<=n,m<=10^9)$



### **思路**

在 HDU 3766 Knight's Trip 我们做过一个马在无限大的棋盘上两点间跳跃所需要的最少步数，与这道题唯一的不同即地图的范围。

仔细想想可以知道，从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 保证最优跳跃下一定不会跳出矩形边界 2 以外的区域。

于是我们可以先让给定点向地图中心靠近一步，然后问题就等同于那道原题啦。



### **AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

LL solve(LL m,LL n)
{
    if(m>n)swap(m,n);
    if(2LL*m>=n)
    {
        if(m==n&&m==1)
            return 2;
        else if(m==n&&m==2)
            return 4;
        else
            return (m+n)/3+(m+n)%3;
    }
    else
    {
        LL ans=m;
        LL c=(n-2*m)%4;
        ans+=c;
        ans+=(n-2*m-c)/2;
        if(n==1&&m==0)
            ans=3;
        return ans;
    }
}
LL lx,ly;
LL xx1,xx2,yy1,yy2;
const int mv[8][2]= {{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};
typedef pair<LL,LL> P;
P a[100],b[100];
int tota,totb;
void init()
{
    for(int i=0; i<8; i++)
    {
        int xi = xx1+mv[i][0];
        int yi = yy1+mv[i][1];
        if(xi<0||yi<0||xi>=lx||yi>=ly)continue;
        a[tota++] = P(xi,yi);
    }
    for(int i=0; i<8; i++)
    {
        int xi = xx2+mv[i][0];
        int yi = yy2+mv[i][1];
        if(xi<0||yi<0||xi>=lx||yi>=ly)continue;
        b[totb++] = P(xi,yi);
    }
    if(xx1==xx2&&yy1==yy2)
    {
        cout<<0<<endl;
        return;
    }
    LL ans = LLONG_MAX;
    for(int i=0; i<tota; i++)
        for(int j=0; j<totb; j++)
        {
            int x = abs(a[i].first-b[j].first);
            int y = abs(a[i].second-b[j].second);
            ans = min(ans,solve(x,y)+2);
        }
    cout<<ans<<endl;
}

int main()
{
    cin>>lx>>ly;
    cin>>xx1>>yy1;
    cin>>xx2>>yy2;
    init();
    return 0;
}
```

