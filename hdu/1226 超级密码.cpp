/*
HDU 1226 超级密码

思路：用给定的m个数凑成n的倍数

比如给定 7 0 1 排序后为 0 1 7 ，n = 22 c = 10
1:1、7
2：10、11、17、70、71、77
3:100、101、107 …… 777

如果模n为0的话输出，直到数的长度大于500

因为取余的性质，模n余数相同的两个数没有必要重复计算，所以可以适当剪枝，因为[(mod*c+num)%n == ((mod*c)%n+num%n)%n]
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
struct point
{
    int mod,data,pre,step;
    void init(int mod,int data,int pre,int step)
    {
        this->mod=mod;
        this->data=data;
        this->pre=pre;
        this->step=step;
    }
} que[5001];

int n,c,m,num[20];
bool used[5010];

void echo(int x)
{
    if(que[x].pre==-1)return;
    echo(que[x].pre);
    if(que[x].data>=0&&que[x].data<=9)printf("%c",que[x].data+'0');
    else printf("%c",que[x].data+'A'-10);
}
void bfs()
{
    memset(used,0,sizeof(used));    //余数相同时会重复
    int front=0,rear=1;
    que[0]= {0,0,-1};   //首元素入队
    while(front!=rear)
    {
        point e=que[front++];
        for(int i=0; i<m; i++)
        {
            int mod=(e.mod*c+num[i])%n; //左移增加一位
            if(used[mod]||(e.pre==-1&&num[i]==0)||e.step>=500)continue;
            else used[mod]=true;
            que[rear++].init(mod,num[i],front-1,e.step+1);
            if(mod==0)
            {
                echo(rear-1);   //递归输出
                printf("\n");
                return;
            }
        }
    }
    printf("give me the bomb please\n");
}
int main()
{
    int t;
    char str;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%*c",&n,&c,&m);
        for(int i=0; i<m; i++)
        {
            scanf("%c%*c",&str);
            if(str>='0'&&str<='9')num[i]=str-'0';
            else num[i]=10+str-'A';
        }
        sort(num,num+m);
        if(n==0)    //如果需要组成的数为0
        {
            if(num[0]==0) printf("0\n");
            else printf("give me the bomb please\n");
        }
        else bfs();
    }
    return 0;
}
