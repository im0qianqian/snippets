# The Cow Lexicon

## **Description**

> Few know that the cows have their own dictionary with W (1 ≤ W ≤ 600) words, each containing no more 25 of the characters 'a'..'z'. Their cowmunication system, based on mooing, is not very accurate; sometimes they hear words that do not make any sense. For instance, Bessie once received a message that said "browndcodw". As it turns out, the intended message was "browncow" and the two letter "d"s were noise from other parts of the barnyard.
>
> The cows want you to help them decipher a received message (also containing only characters in the range 'a'..'z') of length L (2 ≤ L ≤ 300) characters that is a bit garbled. In particular, they know that the message has some extra letters, and they want you to determine the smallest number of letters that must be removed to make the message a sequence of words from the dictionary.



## **Input**

> Line 1: Two space-separated integers, respectively: W and L 
>
> Line 2: L characters (followed by a newline, of course): the received message 
>
> Lines 3..W+2: The cows' dictionary, one word per line



## **Output**

> Line 1: a single integer that is the smallest number of characters that need to be removed to make the message a sequence of dictionary words.



## **Sample Input**

    6 10
    browndcodw
    cow
    milk
    white
    black
    brown
    farmer



## **Sample Output**

    2



## **题意**

给出一个原始序列，以及w个单词，问该序列至少需要去掉多少个字母之后，才能变成完全由已知单词构成的序列。



## **思路**

从题目可以分析出，我们需要找到该序列对于所有单词的最大不重合匹配数，然后需要删除的字母个数便是序列长度减去匹配数。

对于匹配这一动作，我们需要从前向后匹配单词的字母，但是状态数组中存储的结果，如果也是从前往后更新的话会造成提前更新或者其他操作，因此我们对于序列采取从后向前遍历的方法。

**dp[i]代表序列[i,n-1]中最少删除的字母个数。**

首先对于遍历到的每一位，先取最坏情况，此时 $dp[i]=dp[i+1]+1$ 

然后遍历字典，找出所有首字母和序列当前字母相同的单词，然后进行匹配，若成功匹配该单词后更新 $dp[i]$ 

其中： $dp[i]=min(dp[i],dp[si]+si-i-len)$ 

**si 为匹配单词结束后的序列游标，i为匹配前的序列游标，len为单词长度**



## **AC 代码**

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<vector>
#include<queue>

char data[650][50],str[350];
int w,l;
int dp[350];
int solve()
{
    dp[l]=0;
    for(int i=l-1; i>=0; i--)   //从后向前遍历
    {
        dp[i]=dp[i+1]+1;        //取最坏情况
        for(int j=0; j<w; j++)  //遍历字典
        {
            if(str[i]==data[j][0])  //第一位相同
            {
                int si=i,di=0,len=strlen(data[j]);
                for(; si<l&&di<len; si++)   //匹配字典中的单词
                    if(str[si]==data[j][di])
                        di++;
                if(di==len)     //匹配成功
                    dp[i]=min(dp[i],dp[si]+si-i-len);   //更新dp
            }
        }
    }
    return dp[0];
}
int main()
{
    while(~scanf("%d%d%*c",&w,&l))
    {
        gets(str);
        for(int i=0; i<w; i++)
            gets(data[i]);
        printf("%d\n",solve());
    }
    return 0;
}
```

