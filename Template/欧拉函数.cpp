//直接求解欧拉函数
int euler(int n)  //返回euler(n)
{
    int res=n,a=n;
    for(int i=2; i*i<=a; i++)
    {
        if(a%i==0)
        {
            res=res/i*(i-1);//先进行除法是为了防止中间数据的溢出
            while(a%i==0) a/=i;
        }
    }
    if(a>1) res=res/a*(a-1);
    return res;
}

//筛选法打欧拉函数表
#define Max 1000001
int euler[Max];
void Init()
{
    euler[1]=1;
    for(int i=2; i<Max; i++)
        euler[i]=i;
    for(int i=2; i<Max; i++)
        if(euler[i]==i)
            for(int j=i; j<Max; j+=i)
                euler[j]=euler[j]/i*(i-1);//先进行除法是为了防止中间数据的溢出
}
