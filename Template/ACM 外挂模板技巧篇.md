# ACM 外挂模板技巧篇

## **输入输出外挂**

### **普通版**

```cpp
namespace IO
{
    template <typename T>
    inline bool scan_d (T &ret)
    {
        char c;
        int sgn;
        if (c = getchar(), c == EOF)return false; //EOF
        while (c != '-' && (c < '0' || c > '9') )
            if((c = getchar()) == EOF) return false;
        sgn = (c == '-') ? -1 : 1;
        ret = (c == '-') ? 0 : (c - '0');
        while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
        ret *= sgn;
        return true;
    }

    template<typename T>
    void print(T x)
    {
        static char s[33], *s1;
        s1 = s;
        if (!x) *s1++ = '0';
        if (x < 0) putchar('-'), x = -x;
        while(x) *s1++ = (x % 10 + '0'), x /= 10;
        while(s1-- != s) putchar(*s1);
    }

    template<typename T>
    void println(T x)
    {
        print(x);
        putchar('\n');
    }
};
```



### **fread 加强版**

```cpp
namespace IO
{
    const int MT = 10 * 1024 * 1024;  /// 10MB 注意输入数据的大小！！！
    char IO_BUF[MT];
    int IO_PTR, IO_SZ;
    /// 输入前记得调用 begin ！！！
    void begin()
    {
        IO_PTR = 0;
        IO_SZ = fread (IO_BUF, 1, MT, stdin);
    }

    template<typename T>
    inline bool scan_d (T & t)
    {
        while (IO_PTR < IO_SZ && IO_BUF[IO_PTR] != '-' && (IO_BUF[IO_PTR] < '0' || IO_BUF[IO_PTR] > '9'))
            IO_PTR ++;
        if (IO_PTR >= IO_SZ) return false;
        bool sgn = false;
        if (IO_BUF[IO_PTR] == '-') sgn = true, IO_PTR ++;
        for (t = 0; IO_PTR < IO_SZ && '0' <= IO_BUF[IO_PTR] && IO_BUF[IO_PTR] <= '9'; IO_PTR ++)
            t = t * 10 + IO_BUF[IO_PTR] - '0';
        if (sgn) t = -t;
        return true;
    }

    inline bool scan_s (char s[])
    {
        while (IO_PTR < IO_SZ && (IO_BUF[IO_PTR] == ' ' || IO_BUF[IO_PTR] == '\n') ) IO_PTR ++;
        if (IO_PTR >= IO_SZ) return false;
        int len = 0;
        while (IO_PTR < IO_SZ && IO_BUF[IO_PTR] != ' ' && IO_BUF[IO_PTR] != '\n')
            s[len ++] = IO_BUF[IO_PTR], IO_PTR ++;
        s[len] = '\0';
        return true;
    }

    template<typename T>
    void print(T x)
    {
        static char s[33], *s1;
        s1 = s;
        if (!x) *s1++ = '0';
        if (x < 0) putchar('-'), x = -x;
        while(x) *s1++ = (x % 10 + '0'), x /= 10;
        while(s1-- != s) putchar(*s1);
    }

    template<typename T>
    void println(T x)
    {
        print(x);
        putchar('\n');
    }
};
```



## **strtok + sscanf**

```cpp
int ins_read(char *buf,int *a)	//返回整数个数，输入请用 gets
{
    int tot = 0;
    char *p = strtok(buf," ");
    while(p)
    {
        sscanf(p,"%d",a+tot++);
        p = strtok(NULL," ");
    }
    return tot;
}
```



## **手动加栈**

==PS: 旁门左道，谨慎使用！！！==



### **C++**

```cpp
#pragma comment(linker, "/STACK:1024000000,1024000000")		//放在第一行
```



### **G++**

```cpp
int __size__ = 256<<20;			// 和系统有关，不一定适用
char *__p__ = (char*)malloc(__size__) + __size__;
__asm__("movl %0,%%esp\n"::"r"(__p__));
```

