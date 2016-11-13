/*
POJ 3080 Blue Jeans

题意：求多个字符串中的最长公共子串,如果长度小于3或没有，输出no significant commonalities

思路：题目中有说明最大有10个单词，每个单词长度为60。

利用字典树可以很快的解决这一问题

首先，我们知道，一个串的所有后缀的某个前缀如果存在于其他串中，那么这个前缀便是一个公共子串。
而把所有单词的后缀全部加入到一个树中，如果某一点被不同的n个单词访问过n次，那么这个点所代表单词也就是一个公共子串。

建立一颗字典树，插入前n-1个单词，然后用最后一个单词的后缀插入进行匹配，取得匹配长度并更新ans。

剪枝：因为公共子串一定是存在于第一个单词的所有后缀的前缀中，所以其他单词插入时新开辟空间便说明这部分一定不属于公共子串。
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MMAX 26

char s[1500],ans[1500],p[1500];
struct node
{
    int times;
    node* next[MMAX];
};

int insert(node *head,char *s,int x)
{
    int depth=0;
    node *p=head;
    for(int i=0; s[i]!=0; i++)
    {
        int k=s[i]-'A';
        if(p->next[k]==NULL)
        {
            if(x!=1)break;      //因为公共子串一定是存在于第一个单词所有后缀的前缀中，所以其他单词插入时新开辟空间便说明这部分一定不属于公共子串
            p->next[k]=new node();
        }
        p=p->next[k];
        if(p->times+1>=x)   //若此节点是本串已经访问过的或上一个节点访问过
        {
            p->times=x;
            depth++;
        }
        else break;
    }
    return depth;
}

void drop(node *head)   //销毁树 防止内存超限
{
    node *p=head;
    for(int i=0; i<MMAX; i++)
        if(p->next[i]!=NULL)
            drop(p->next[i]);
    free(p);
}

int main()
{
    int N,maxx,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        node *head=new node();
        memset(p,0,sizeof(p));
        maxx=0;
        for(int i=1; i<N; i++)
        {
            scanf("%s",s);
            for(int j=0; s[j]!=0; j++)  //插入这个单词的所有后缀
                insert(head,s+j,i);
        }
        scanf("%s",s);
        for(int j=0; s[j]!=0; j++)
        {
            int len=insert(head,s+j,N); //返回最长公共子串长度
            strncpy(p,s+j,len);
            if(maxx<len||(maxx==len&&strcmp(ans,p)>0))
                strcpy(ans,p),maxx=len;
        }
        printf(strlen(ans)<3?"no significant commonalities\n":"%s\n",ans);
        drop(head);
    }
    return 0;
}
