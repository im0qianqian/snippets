/*
hihocoder 1080 更为复杂的买卖房屋姿势

解题思路：首先利用给出的值构造一棵满二叉树，树中每个节点代表它所维护的区间各点的和。
那么此时，树的根节点便是这个街道中所有房屋的房价总和。

如果是房屋自发涨价或者降价(add)，便从根节点往下，找到刚好可以维护这个区间的一个或几个节点，标记它所维护区间[(add+x)(sum+=(r-l+1)*x)]
如果是房屋硬性调价(set)，同样，在这一个或几个根节点中标记[set(x) (sum=(r-l+1)*x)]

需要注意的一点是，如果当前需要set的节点已经存在add，那么这个add就会失效，而当前需要add的节点如果存在set的话并不会影响到结果
另外，如果从根节点向下查找维护区间时，中途遇到带有[set||add]的节点，可以想到，我们对它的子孙节点做修改的话，当前节点也会改变，所以简单的办法就是把当前节点的[add||set]属性转移到其子节点，然后重新计算这几个节点所维护的值。
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXX 110000
typedef long ll;
struct po
{
    ll add,set,sum;
    void init(int sum=0,int add=0,int set=-1)   //修改属性，当add为0时重置set为-1
    {
        this->add=add;
        this->sum=sum;
        if(!add)this->set=set;
    }
    void addmax(int sum=0,int add=0)            //属性累加
    {
        this->add+=add;
        this->sum+=sum;
    }
} data[MAXX<<2];

int LR=1;               //满二叉树的宽度-1
void init(int n)
{
    while(LR<n)LR<<=1;  //根据n计算满二叉树宽度
    for(int i=0; i<=2*LR; i++)  //初始化
        data[i].init();
    LR--;
}

void inse(int o,int k)  //更新满二叉树最底层第o个节点，并自底而上更新其父节点的值
{
    o+=LR;              //LR为满二叉树宽度-1，也是最底层第一个元素的下标
    data[o].sum=k;
    while(o>1)
    {
        o/=2;
        data[o].sum=data[o*2].sum+data[o*2+1].sum;
    }
}

void update(int isset,int s,int l,int r,int ls,int lr,int o)    //当前区间[l,r]，目标区间[ls,lr]，当前节点o，s为[add||set]的值
{
    if(l>lr||r<ls||r<l)return;      //如果两个区间交集为空
    if(r<=lr&&l>=ls)                //如果目标区间包含当前区间，执行[set||add]
    {
        if(isset)data[o].init(s*(r-l+1),0,s);
        else
        {
            data[o].addmax(s*(r-l+1),s);
//          data[o].init(data[o].sum+s*(r-l+1),data[o].add+s);    不能写成这样，有一个很小很小的BUG (当data[o].add+s==0时会重置set)
        }
        return;
    }
    int m=(l+r)/2,lc=o*2,rc=lc+1;
    if(l!=r&&(data[o].set!=-1||data[o].add!=0))     //如果不在叶子节点并且当前节点带有[set||add]属性
    {
        if(data[o].set!=-1)     //带有[set]属性
        {
            data[lc].init(data[o].set*(m-l+1),0,data[o].set);   //转移set到其两个子节点
            data[rc].init(data[o].set*(r-m),0,data[o].set);
            data[o].set=-1;     //重置当前节点set
        }
        if(data[o].add!=0)      //带有[add]属性
        {
            data[lc].addmax((m-l+1)*data[o].add,data[o].add);   //转移add到其两个子节点
            data[rc].addmax((r-m)*data[o].add,data[o].add);
            data[o].add=0;      //重置当前节点add
        }
    }
    update(isset,s,l,m,ls,lr,lc);   //递归子节点
    update(isset,s,m+1,r,ls,lr,rc);
    data[o].sum=data[lc].sum+data[rc].sum;  //递归结束返回时计算父节点的值
}
int main()
{
    int k,t,n;
    scanf("%d%d",&n,&t);
    ++n;
    init(n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d",&k);
        inse(i,k);
    }
    while(t--)
    {
        int a,b,c;
        scanf("%d%d%d%d",&k,&a,&b,&c);
        update(k,c,0,LR,a,b,1);
        printf("%ld\n",data[1].sum);
    }
    return 0;
}
