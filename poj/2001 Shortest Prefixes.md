# Shortest Prefixes

## **Description**

> A prefix of a string is a substring starting at the beginning of the given string. The prefixes of "carbon" are: "c", "ca", "car", "carb", "carbo", and "carbon". Note that the empty string is not considered a prefix in this problem, but every non-empty string is considered to be a prefix of itself. In everyday language, we tend to abbreviate words by prefixes. For example, "carbohydrate" is commonly abbreviated by "carb". In this problem, given a set of words, you will find for each word the shortest prefix that uniquely identifies the word it represents.
>
> In the sample input below, "carbohydrate" can be abbreviated to "carboh", but it cannot be abbreviated to "carbo" (or anything shorter) because there are other words in the list that begin with "carbo".
>
> An exact match will override a prefix match. For example, the prefix "car" matches the given word "car" exactly. Therefore, it is understood without ambiguity that "car" is an abbreviation for "car" , not for "carriage" or any of the other words in the list that begins with "car".



## **Input**

> The input contains at least two, but no more than 1000 lines. Each line contains one word consisting of 1 to 20 lower case letters.



## **Output**

> The output contains the same number of lines as the input. Each line of the output contains the word from the corresponding line of the input, followed by one blank space, and the shortest prefix that uniquely (without ambiguity) identifies this word.



## **Sample Input**

    carbohydrate
    cart
    carburetor
    caramel
    caribou
    carbonic
    cartilage
    carbon
    carriage
    carton
    car
    carbonate



## **Sample Output**

    carbohydrate carboh
    cart cart
    carburetor carbu
    caramel cara
    caribou cari
    carbonic carboni
    cartilage carti
    carbon carbon
    carriage carr
    carton carto
    car car
    carbonate carbona



## **题意**

给出若干字符串，求把他们缩写到所能形成的最小程度。

**如：**

    abdef
    abcdefg
    ab

**其缩写最小程度为**

    abd
    abc
    ab



## **思路**

可以使用字典树求解，求出衍生边为 `num==1` 的各个单词，然后输出！



## **AC 代码**

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct tree
{
    char c;
    struct tree *next[27];
    int num;
};
void init(char *c,tree *T)
{
    tree *p;
    for(int i=0; i<(int)strlen(c); i++)
    {
        if(T->next[c[i]-'a']==NULL)
        {
            p=(tree*)malloc(sizeof(tree));
            T->next[c[i]-'a']=p;
            p->c=c[i];
            T=T->next[c[i]-'a'];
            memset(T->next,0,sizeof(T->next));
            T->num=1;
        }
        else
        {
            T=T->next[c[i]-'a'];
            T->num++;
        }
    }
}
void PR(char *c,tree *t)
{
    t=t->next[c[0]-'a'];
    for(int i=0; i<(int)strlen(c); i++)
    {
        if(t->num>1)
        {
            printf("%c",t->c);
            t=t->next[c[i+1]-'a'];
        }
        else
        {
            printf("%c",t->c);
            break;
        }
    }
}
int main()
{
    char c[1005][35]={{0}};
    int i;
    tree *T=(tree*)malloc(sizeof(tree));
    T->num=0;
    memset(T->next,0,sizeof(T->next));
    for(i=0; gets(c[i]); i++)
    {
        init(c[i],T);
    }
    for(int k=0; k<i; k++)
    {
        printf("%s ",c[k]);
        PR(c[k],T);
        printf("\n");
    }
    return 0;
}
```

