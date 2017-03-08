# Surprising Strings

## **Description**

> The D-pairs of a string of letters are the ordered pairs of letters that are distance D from each other. A string is D-unique if all of its D-pairs are different. A string is surprising if it is D-unique for every possible distance D.
>
> Consider the string ZGBG. Its 0-pairs are ZG, GB, and BG. Since these three pairs are all different, ZGBG is 0-unique. Similarly, the 1-pairs of ZGBG are ZB and GG, and since these two pairs are different, ZGBG is 1-unique. Finally, the only 2-pair of ZGBG is ZG, so ZGBG is 2-unique. Thus ZGBG is surprising. (Note that the fact that ZG is both a 0-pair and a 2-pair of ZGBG is irrelevant, because 0 and 2 are different distances.)
>
> Acknowledgement: This problem is inspired by the "Puzzling Adventures" column in the December 2003 issue of Scientific American.



## **Input**

> The input consists of one or more nonempty strings of at most 79 uppercase letters, each string on a line by itself, followed by a line containing only an asterisk that signals the end of the input.



## **Output**

> For each string of letters, output whether or not it is surprising using the exact output format shown below.



## **Sample Input**

    ZGBG
    X
    EE
    AAB
    AABA
    AABB
    BCBABCC
    *



## **Sample Output**

    ZGBG is surprising.
    X is surprising.
    EE is surprising.
    AAB is surprising.
    AABA is surprising.
    AABB is NOT surprising.
    BCBABCC is NOT surprising.


## **题意**

给出一个字符串，问同样间隔下挑选两个字符组成的字符串是否重复，若是，则 `NOT surprising` ，否则为 `surprising` 。

比如以 `AABB` 为例

间距为0有： `AA、AB、BB`

间距为1有： `AB、AB` （重复）

间距为2有： `AB`



## **思路**

字符串长度并不是很长，因此直接暴力组合出这样所有的字符串，利用STL中的map判断即可。



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<queue>
#include<map>
#define INF (1<<25)

int main()
{
    char str[105];
    while(gets(str))
    {
        if(strcmp(str,"*")==0)break;
        int len=strlen(str);
        bool flag=true;
        for(int li=1; li<len; li++) //间距
        {
            map<string,bool>sk;
            for(int i=0; i+li<len; i++)
            {
                string no="";   //组合字符串
                no+=str[i],no+=str[i+li];
                if(sk[no])
                {
                    flag=false;
                    break;
                }
                sk[no]=true;
            }
            if(!flag)break;
        }
        printf("%s is ",str);
        if(!flag)printf("NOT ");
        printf("surprising.\n");
    }
    return 0;
}
```

