/*
POJ 1706 References
*/

#include<iostream>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
using namespace std;
char refDes[1024][256];//旧文献边编号为i的文献的内容
int nmapo[1024];//新文献编号为i的文献，其旧文献编号为nmapo[i].
int omapn[1024];//旧文献编号为i的文献，其新文献编号为omapn[i].
int refNewNu;//当前文献的新文献编号.

//判断line是否为空行，即不包含任何字符或值包含空格.是返回true否则返回false.
bool EmptyLine(const char* line);

int main()
{
    cout.sync_with_stdio(false);
    char line[256];//当前行
    char digs[8];//临时存储数字字符串.
    int i, j, k;

    refNewNu=1;//初始化新文献编号为1
    while(cin.getline(line,256))
    {
        if(EmptyLine(line))
        {
            continue;
        }
        if(line[0]=='[') //当前行为文献段落首行
        {
            //得到旧文献编号
            i=1;
            while(isdigit(line[i]))
            {
                digs[i-1]=line[i];
                i++;
            }
            digs[i-1]='\0';
            j=atoi(digs);
            //得到文献内容
            strcpy(refDes[j],line+i+1);
            strcat(refDes[j],"\n");
            while(cin.getline(line,256))
            {
                if(EmptyLine(line))
                {
                    break;
                }
                strcat(refDes[j],line);
                strcat(refDes[j],"\n");
            }
        }
        else //当前行为段落首行
        {
            //读入并处理正文段落的第一行，并输出.
            while(!EmptyLine(line))
            {
                i=0;
                while(line[i]!='\0')
                {
                    if(line[i]=='[')
                    {
                        //得到文献的旧文献编号.
                        i++;
                        j=0;
                        while(isdigit(line[i]))
                        {
                            digs[j]=line[i];
                            i++;
                            j++;
                        }
                        digs[j]='\0';
                        k=atoi(digs);
                        //判断是否已对当前文献重新编号并进行相应处理.
                        if(omapn[k]==0)
                        {
                            omapn[k]=refNewNu;
                            nmapo[refNewNu]=k;
                            refNewNu++;
                        }
                        //输出文献的新文献编号.
                        cout<<'['<<omapn[k]<<']';
                    }
                    else
                    {
                        cout<<line[i];
                    }
                    i++;
                }
                cout<<endl;
                cin.getline(line,256);
            }
            cout<<endl;
        }
    }

    //对所有文献按新文献编号从小到大顺序输出.
    for(i=1; i<refNewNu; i++)
    {
        cout<<'['<<i<<']'<<refDes[nmapo[i]]<<endl;
    }
    return 0;
}

bool EmptyLine(const char* line)
{
    int i=0;
    while(line[i]!='\0')
    {
        if(line[i]!=' ')
            return false;
        i++;
    }
    return true;
}
