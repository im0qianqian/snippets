# Revolving Digits

## **Problem Description**

> One day Silence is interested in revolving the digits of a positive integer. In the revolving operation, he can put several last digits to the front of the integer. Of course, he can put all the digits to the front, so he will get the integer itself. For example, he can change 123 into 312, 231 and 123. Now he wanted to know how many different integers he can get that is less than the original integer, how many different integers he can get that is equal to the original integer and how many different integers he can get that is greater than the original integer. We will ensure that the original integer is positive and it has no leading zeros, but if we get an integer with some leading zeros by revolving the digits, we will regard the new integer as it has no leading zeros. For example, if the original integer is 104, we can get 410, 41 and 104.



## **Input**

> The first line of the input contains an integer T (1<=T<=50) which means the number of test cases. 
>
> For each test cases, there is only one line that is the original integer N. we will ensure that N is an positive integer without leading zeros and N is less than 10^100000.



## **Output**

> For each test case, please output a line which is "Case X: L E G", X means the number of the test case. And L means the number of integers is less than N that we can get by revolving digits. E means the number of integers is equal to N. G means the number of integers is greater than N.



## **Sample Input**

    1
    341



## **Sample Output**

    Case 1: 1 1 1



## **题意**

给一个数字，每一次把它的最后一位拿到最前面，一直那样下去，分别求形成的数字小于，等于和大于原来数的个数。

例如： `134` 可以形成 `134,341,413` 三个数，所以分别是 `1,1,1` 。



## **思路**

因为题目给出数的范围非常大 `[:10^100000]` 所以当然不能用整数处理啦~

采用字符串存储，然后我们可以把当前串复制两次构造出一个新串，利用扩展 KMP 求出 `s[i...n-1]` 与 `s[0...n-1]` 的最长公共前缀，然后遍历原串，如果 `next[i]>=n` 即说明遇到了一个与原串相同的子串，如果 `str[next[i]]>str[i+next[i]]` 说明找到一个小于原串的子串，否则大于原串。

需要注意的是可能存在相同的子串，如 `3131` 复制两遍变为 `31313131` ，而里面存在相同子串 `1313` 等。

所以我们要先求出原串的循环节个数，最终根据扩展 KMP 求解后除掉那部分即可。



## **AC 代码**

```cpp
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn = 110000;

void pre_ekmp(char *x,int m,int *nextt)
{
    nextt[0]=m;
    int j=0;
    while(j+1<m&&x[j]==x[j+1])j++;
    nextt[1]=j;
    int k=1;
    for(int i=2; i<m; i++)
    {
        int p=nextt[k]+k-1;
        int l=nextt[i-k];
        if(i+l<p+1)nextt[i]=l;
        else
        {
            j=max(0,p-i+1);
            while(i+j<m&&x[i+j]==x[j])j++;
            nextt[i]=j;
            k=i;
        }
    }
}

char str[maxn*2];
int nextt[maxn*2],nextval[maxn];

void get_next(char *T,int len)
{
    int i=0,j=-1;
    nextval[0]=-1;
    while(i<len)
    {
        if(j==-1||T[i]==T[j])
        {
            i++;
            j++;
            if(T[i]!=T[j]) nextval[i]=j;
            else  nextval[i]=nextval[j];
        }
        else j=nextval[j];
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1; ti<=T; ti++)
    {
        scanf("%s",str);
        int n=strlen(str);
        strcat(str,str);
        pre_ekmp(str,n*2,nextt);
        get_next(str,n);
        int mod=n-nextval[n];
        int temp=1;
        if(n%mod==0)temp=n/mod; // 循环节个数
        int ans1=0,ans2=0,ans3=0;
        for(int i=0; i<n; i++)
        {
            int no=nextt[i];
            if(no>=n)ans2++;
            else if(str[no]>str[i+no])
                ans1++;
            else ans3++;
        }
        printf("Case %d: %d %d %d\n",ti,ans1/temp,ans2/temp,ans3/temp);
    }
    return 0;
}
```

