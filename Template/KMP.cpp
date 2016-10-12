// 求next数组以及t在s中出现的次数

void getnext(char* s,int next[])
{
    int j=0,k=-1;
    next[0]=-1;
    int sn=strlen(s);
    while(j<sn)
    {
        if(k==-1||s[j]==s[k])
            next[++j]=++k;
        else k=next[k];
    }
}

int kmp(char *s,char *t,int next[])
{
    int ans=0;
    int i=0,j=0,sn=strlen(s),tn=strlen(t);
    while(i<sn)
    {
        if(j==-1||s[i]==t[j])
        {
            i++,j++;
            if(j==tn)ans++,j=next[j];
        }
        else j=next[j];
    }
    return ans;
}