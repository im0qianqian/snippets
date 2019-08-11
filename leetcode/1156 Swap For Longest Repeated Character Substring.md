# 1156 单字符重复子串的最大长度

## **Description**

> 如果字符串中的所有字符都相同，那么这个字符串是单字符重复的字符串。
>
> 给你一个字符串 `text`，你只能交换其中两个字符一次或者什么都不做，然后得到一些单字符重复的子串。返回其中最长的子串的长度。




## **Input**

    aaabbaaa



## **Output**

    4



## **思路**

从题意我们可以看出，每一种字母之间是相互独立的，即：我们可以对不同的字母使用相同的处理方法。

定义两个变量 `tmp1, tmp2` 分别表示当前可交换字符情况下字串的长度与不可交换情况下字串的长度。

对于一种简单的情况，即初始时该字母便是连续的我们可以直接特判处理。

而对于其他情况，即像 `aabaaa` 这样针对 `a` 来讲分成了两段（或者多段）的情况，我们都可以从其他段段首或段尾寻找一个相同的字母来替换掉空缺的位置，因此我们在意的便是哪个位置被弥补后才可以使得字串的长度增加。

显然，如果 `tmp1 == tmp2` 时代表目前并没有交换过字符，对中间空缺多个位置的情况，我们可以对上一段段尾增加一个相同字母，也可以向下一段段首增加一个相同字母。

需要注意的是，基于上述的方法我们可能会对 `aabaa` 这样的数据取第二段末尾的 `a` 与 `b` 交换后得到 `aaaab`，但实际算法中我们并没有抹除掉后一段中原先被交换位置的数据，因此这种情况下得到的 `a` 的长度为 5，一个简单的处理方法便是 `min(5, 4)` 其中 4 为 `a` 的个数。



## **AC 代码**

```cpp
class Solution {
public:
    int maxRepOpt1(string text) {
        vector<int> sk[26];
        int len = text.length();
        for (int i = 0; i < len; i++) {
            sk[text[i] - 'a'].push_back(i);
        }
        int ans = 1;
        for (int ch = 0; ch < 26; ch++) { // 处理每种字母
            int len = sk[ch].size();
            int tmp1 = 1, tmp2 = 1;
            int flag = 0;
            for (int i = 1; i < len; i++) {
                if (sk[ch][i] != sk[ch][i - 1] + 1) {
                    flag++;
                }
            }
            if (flag == 0) { // 如果成立则所有的字母都连续
                ans = max(ans, len);
                continue;
            }
            for (int i = 1; i < len; i++) {
                if (sk[ch][i] == sk[ch][i - 1] + 2) { // 填补 1 个，比如 aabaa
                    tmp1 = tmp2 + 2;
                    tmp2 = 1;
                } else if (sk[ch][i] ==
                           sk[ch][i - 1] + 1) { // 正好连续，比如 baaaab
                    tmp2++;
                    tmp1++;
                } else { // 填补 1 个以上，比如 aabbaa
                    if (tmp1 == tmp2) {
                        ans = max(ans,
                                  min(tmp1 + 1, len)); // 向上一段段尾添加一个
                    }
                    tmp1 = 2; // 向下一段段首添加一个
                    tmp2 = 1;
                }
                ans = max(ans, min(tmp1, len));
            }
        }
        return ans;
    }
};
```

